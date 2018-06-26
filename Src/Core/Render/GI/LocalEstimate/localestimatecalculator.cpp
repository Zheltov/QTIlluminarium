#include "localestimatecalculator.h"
#include "Core/constants.h"

#include "Core/func.h"

#include "Debug/raydebugcollection.h"

#include <exception>
#include <stdexcept>
#include <cmath>
#include <ctime>

#include <QTime>

LocalEstimateCalculator::LocalEstimateCalculator(uint _threadIndex,RayTracer &rt, Log &lg)
    : threadIndex(_threadIndex), rayTracer( rt ), log( lg ), frame( NULL ), m_stop( false )
{

}

LocalEstimateCalculator::LocalEstimateCalculator(uint _threadIndex, RayTracer &rt, Log &lg, RenderFrameLocalEstimate &_frame)
    : threadIndex(_threadIndex), rayTracer( rt ), log( lg ), frame( &_frame ), m_stop( false )
{

}

LocalEstimateCalculator::~LocalEstimateCalculator()
{

}

RenderFrameLocalEstimate *LocalEstimateCalculator::getRenderFrame()
{
    return this->frame;
}

void LocalEstimateCalculator::setRenderFrame(RenderFrameLocalEstimate &_frame)
{
    this->frame = &_frame;
}

void LocalEstimateCalculator::Render()
{
    /*
    const float XXXXX = 100;

    const float correctionRMax = Constants::Eps * 500;
    const float correctionRMin = correctionRMax / 10;
    const float correctiondRMinMax = correctionRMin - correctionRMax;
    */

    const float boundedKernel = .1;


    // Затравка для рандомизатора
    func::randSetFuse( this->threadIndex );
    //func::randSetFuse( (uint)currentThreadId() );

    // emit messageInfo( func::to_string( func::randf(), 6 ) );
    // emit messageInfo( func::to_string( func::randf(), 6 ) );
    // emit messageInfo( func::to_string( func::randf(), 6 ) );

    const unsigned int nRays = 10000000000;
    const unsigned int maxIterations = 10;
    const float wMin = 0.01;

    //for( unsigned int nRay = 0; nRay < nRays; nRay++ )
    int nRay = 0;
    int dnRay = 0;
    bool f = true;
    while ( f )
    {

        //this->log.AddMessage( "nRay: " + func::to_string(nRay) );

        Light* light = this->RouletteLight();

        LightRay ray = light->GetRandomRay();


        //ray = LightRay( ray.from, Vector3D(0.075, -0.323, -1, true), Spectrum(1) );
        //ray = LightRay( Point3D(4, -2.3, 15), Vector3D(0.25, 0.25, -1, true), Spectrum(1) );

        //emit messageInfo(  "X = " + func::to_string( ray.from.X, 6 ) );

        float wMinActual = ray.illuminance.MaxValue() * wMin;

        unsigned int iteration = 0;

        if ( nRay % 100 == 0 && nRay > 0 )
        {
            emit raysCalculated( (int)currentThreadId(), nRay, nRay - dnRay );
            dnRay = nRay;
            //emit raysCalculated( dynamic_cast<long>(currentThreadId()) );
            //this->log.AddMessage( "nRay: " + func::to_string(nRay) );
        }

        Intersection *intersection = NULL;
        while ( ray.illuminance.MaxValue() > wMinActual && iteration < maxIterations )
        {
            intersection = this->rayTracer.Intersect(ray.from, ray.direction, Constants::Eps);
            // здесь блок выбора дальнейшего движения первичного луча

            if ( intersection == NULL )
                break;

            //RayDebugCollection::Rays.push_back( new Ray(ray.from, intersection->getPosition() ) );
            /*
            RayDebugCollection::Rays.push_back( new Ray(ray.from, intersection->getPosition() ) );

            std::string s = "Ray ("
                    + func::to_string( ray.from.X ) + ", "
                    + func::to_string( ray.from.Y ) + ", "
                    + func::to_string( ray.from.Z ) + ") - ("
                    + func::to_string( ray.to.X ) + ", "
                    + func::to_string( ray.to.Y ) + ", "
                    + func::to_string( ray.to.Z ) + ")";
            emit messageInfo( s );
            */
            //emit raysCalculated( (int)currentThreadId(), 0, ( ray.from.X + ray.from.Y + ray.from.Z ) * 10000 );

            // TODO !!!
            if ( intersection->getFace().material->reflectance == NULL )
            {
                ray.illuminance = Spectrum(0);
                delete intersection;
                continue;
            }

            Vector3D intersectionNormal = intersection->getFace().normal;

            float x = Constants::Eps;
            Point3D intesectionPointOcclude = intersection->getPosition() + ( intersectionNormal * x );


            for( uint i = 0; i < frame->renderPoints.size(); i++ )
            {
                RenderPointLocalEstimate &renderPointLocalEstimate = *frame->renderPoints[i];
                RenderPoint &renderPoint = renderPointLocalEstimate.renderPoint;

                Vector3D renderPointNormal = renderPoint.face.normal;

                if ( renderPoint.face.material->reflectance == NULL )
                    continue;


                /*
                Coordinate dot = Vector3D::Dot( intersectionNormal, renderPointNormal );
                if ( dot > Constants::Eps && dot < Constants::Eps * 10 )
                {
                    renderPointLocalEstimate.illuminance += Spectrum(1, 0, 0);
                    continue;
                }
                if ( dot > Constants::Eps * 10 )
                    continue;
                */

                // направление от точки до точки рендеринга
                Coordinate r = Point3D::Length( intesectionPointOcclude, renderPoint.position );
                Coordinate r2 = r * r;

                /*
                if ( r2 < Constants::Eps * 500 )
                    continue;
                */

                Vector3D coreDirection( intesectionPointOcclude, renderPoint.position, true );
                Coordinate occludeRayLength = sqrtf( r2 ) - Constants::Eps;

                if ( fabs( intersectionNormal.X - renderPointNormal.X ) + fabs( intersectionNormal.Y - renderPointNormal.Y ) + fabs( intersectionNormal.Z - renderPointNormal.Z ) < Constants::Eps )
                    continue;

                if ( this->rayTracer.Occluded( intesectionPointOcclude, coreDirection, 0, occludeRayLength ) )
                    continue;


                Coordinate cos1 = Vector3D::Dot( coreDirection, intersectionNormal );
                Coordinate cos2 = fabs( Vector3D::Dot( coreDirection, renderPointNormal ) );

                if ( cos1 < Constants::Eps2 )
                    renderPointLocalEstimate.counterRaysCos1Zero++;

                cos1 = fabs( cos1 );

                Spectrum sigma1 = intersection->getFace().material->reflectance->BRDF( ray.direction, intersectionNormal, coreDirection );

                /*
                if ( r < correctionRMax  )
                    continue;
                */

                /*
                if ( r < correctionRMax )
                {
                    //continue;
                    //Coordinate r = r + correctionRMin * ( r - correctionRMax ) / correctiondRMinMax;
                    //r = correctionRMax;
                    //r2 = r*r;
                    //r2 = r2 + fabs( dr2 );
                }
                */
                float b = ( cos1 * cos2 / r2 );
                if ( b > boundedKernel )
                    b = boundedKernel;

                Spectrum kernel1 = sigma1 * b;



                // Ядро 2. Переход из суб. точки в искомое направление
                Spectrum kernel2 = renderPoint.face.material->reflectance->BRDF( coreDirection, renderPointNormal, renderPoint.direction );

                //renderPoint.illuminanceIndirect += ray.illuminance * ( kernel1 * kernel2 );
                renderPointLocalEstimate.illuminance += ray.illuminance * ( kernel1 * kernel2 );
            }

            Vector3D newDirection = intersection->getFace().material->reflectance->GetRandomReflectedDirection( ray.direction, intersectionNormal );

            Spectrum brdf = intersection->getFace().material->reflectance->BRDF( ray.direction, intersectionNormal, newDirection );

            ray.from = intersection->getPosition();
            ray.direction = newDirection;
            ray.to = ray.from + ray.direction;
            ray.illuminance *= brdf;

            /*
            if ( iteration == 0 )
            {
                ray.direction = Vector3D( .6, 0.1, 0.75, true);
                ray.to = ray.from + ray.direction;

            }
            else if ( iteration == 1 )
            {
                ray.direction = Vector3D( 0, -1, .67, true);
                ray.to = ray.from + ray.direction;
            }
            */


            iteration++;
            delete intersection;
        }

        nRay++;

        QMutexLocker locker( &m_mutex );
        if ( m_stop || nRay >= nRays )
        {
            f = false;
        }
    }


    // Norm
    const float XXXXX = 2;
    const float norm = 4 * Constants::PI * XXXXX;
    for( uint i = 0; i < frame->renderPoints.size(); i++ )
    {
        RenderPointLocalEstimate *renderPoint = frame->renderPoints[i];

        renderPoint->illuminance *= ( norm / ( nRay * Constants::PI * Constants::PI ) );
    }

}

void LocalEstimateCalculator::stop()
{
    QMutexLocker locker( &m_mutex );
    m_stop = true;
}

Light *LocalEstimateCalculator::RouletteLight()
{
    if ( this->rayTracer.scene.Lights.size() != 1 )
        throw new std::runtime_error( "lights count is not 1" );
    else
        return this->rayTracer.scene.Lights[0];
}

void LocalEstimateCalculator::run()
{
    this->Render();
}
