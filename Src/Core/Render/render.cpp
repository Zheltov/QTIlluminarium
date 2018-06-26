#include "render.h"

#include "Core/func.h"
#include "Core/constants.h"

Render::Render(RayTracer &rt , GlobalIllumination &gi, Log &lg) : rayTracer( rt ), globalIllumination( gi ), log( lg )
{
}

RenderViewFrame *Render::GetRenderFrame( const Camera &camera )
{
    int width = camera.getClientWidth();
    int height = camera.getClientHeight();

    this->log.AddMessage("Start generate frame");
    RenderViewFrame *frame = new RenderViewFrame( rayTracer.scene, width, height );

    for( int x = 0; x < width; x++ )
        for( int y = 0; y < height; y++ )
        {
            Vector3D direction = camera.GetTracingDirection( x, y );

            Intersection *intersection = rayTracer.Intersect( camera.getPosition(), direction );
            if ( intersection != NULL )
            {
                RenderPoint *rp = new RenderPoint( intersection->getPosition(), direction * -1, intersection->getFace() );
                RenderScreenPoint *rsp = new RenderScreenPoint( x, y, *rp );
                //frame->AddRenderPoint( rp, rsp );
                this->AddRenderPointRecursive( frame, rp, rsp );



                delete intersection;
            }
        }

    this->log.AddMessage("End generate frame. Total render points " + func::to_string( frame->renderPoints.size() ) );
    return frame;
}

void Render::RenderDirectLight(RenderFrame &frame)
{
    this->log.AddMessage("Start render");

    Scene &scene = this->rayTracer.scene;
    int lightsCount = scene.Lights.size();

    unsigned int renderPointsSize = frame.renderPoints.size();
    for( unsigned int i = 0; i < renderPointsSize; i++ )
    {
        if ( i % 100000 == 0 && i > 0 )
            log.AddMessage("Render " + func::to_string(i) + " of " + func::to_string(renderPointsSize) + " points" );

        RenderPoint &renderPoint = *frame.renderPoints[i];
        Light *l = dynamic_cast<Light*>( renderPoint.face.obj );
        if ( l != NULL )
        {
            renderPoint.illuminanceDirect = l->GetIlluminanceSurfacePoint( renderPoint.position, renderPoint.direction );
        }
        else
        {
            Material &material = *renderPoint.face.material;

            if ( material.reflectance != NULL )
            {

                for( int iLight = 0; iLight < lightsCount; iLight++ )
                {
                    Light &light = *scene.Lights[iLight];

                    renderPoint.illuminanceDirect += light.GetIlluminance( this->rayTracer, renderPoint.position, renderPoint.face.normal, renderPoint.direction, *renderPoint.face.material );

                }
            }
        }

        /*
        if ( i % 50000 == 0 )
        {
            this->log.AddMessage("Render " + func::to_string(i) + " points of " + func::to_string(frame.renderPoints.size()) );
        }
        */


    }

    this->log.AddMessage("End render");
}

void Render::RenderGlobalIllumination(RenderFrame &frame)
{
    this->globalIllumination.Render( frame );
}

void Render::RenderFull(RenderFrame &frame)
{
    this->RenderDirectLight( frame );
    this->RenderGlobalIllumination( frame );
}

void Render::StopRender()
{
    this->globalIllumination.Stop();
}

void Render::AddRenderPointRecursive( RenderViewFrame *frame, RenderPoint *renderPoint, RenderScreenPoint *renderScreenPoint )
{
    if ( renderScreenPoint != NULL )
        frame->AddRenderScreenPoint( renderScreenPoint );
    else
        frame->AddRenderPoint( renderPoint );


    if ( renderPoint->face.material->mirror != NULL )
    {
        Vector3D dir1 = renderPoint->direction * -1;
        Vector3D mirrorDirection = dir1.Reflect( renderPoint->face.normal );

        Intersection *intersection = rayTracer.Intersect( renderPoint->position, mirrorDirection, Constants::Eps );

        if ( intersection != NULL )
        {
            RenderPoint *mirrorRenderPoint = new RenderPoint( intersection->getPosition(), mirrorDirection * -1, intersection->getFace() );

            renderPoint->mirrorRenderPoint = mirrorRenderPoint;

            delete intersection;

            this->AddRenderPointRecursive( frame, mirrorRenderPoint );

        }

        // Generate mirror points
    }
}
