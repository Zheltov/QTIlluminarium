#include "localestimategeomcompressed.h"

#include "Core/func.h"

LocalEstimateGeomCompressed::LocalEstimateGeomCompressed(RayTracer &rt, Log &lg)
    : GlobalIllumination( rt, lg ),
      calculator( new LocalEstimateCalculator( rt, lg) )
{

}

LocalEstimateGeomCompressed::~LocalEstimateGeomCompressed()
{

}

void LocalEstimateGeomCompressed::Render(RenderFrame &frame)
{
    this->GenerateCalculatedStructure( frame );
}

void LocalEstimateGeomCompressed::GenerateCalculatedStructure(RenderFrame &frame)
{
    for( unsigned int iObj = 0; iObj < this->rayTracer.scene.Objects.size(); iObj++ )
    {
        Obj &obj = *this->rayTracer.scene.Objects[iObj];
        for( unsigned int iFace = 0; iFace < obj.Faces.size(); iFace++ )
        {
            Face &face = *obj.Faces[iFace];

            if ( face.material->reflectance == NULL )
                continue;

            vector<RenderPoint*> *renderPointsFace = frame.faceRenderPoints[&face];
            if ( renderPointsFace == NULL )
                continue;

            //FaceLocalEstimate *f = new FaceLocalEstimate( face, *renderPointsFace );


            // Создаем новую расчетную грань
            //FaceRenderPointLocalEstimate *face = new FaceRenderPointLocalEstimate();

            //vector<RenderPoint*> rp =

            //func::multimapToVector( NULL, NULL );

            //FaceRenderPointMapIterator it = frame.faceRenderPoints.find(  );
            //it.
            //std::pair <FaceRenderPointMapIterator, FaceRenderPointMapIterator> range;
            //range = frame.faceRenderPoints.equal_range( &face );

            //int x = 0;
            //for( FaceRenderPointMapIterator it = range.first; it != range.second; ++it )
            //{
            //    x++;
                  //std::cout << ' ' << it->second;
            //}

        }
    }
}
