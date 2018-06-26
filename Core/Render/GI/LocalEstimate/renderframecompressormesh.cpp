#include "renderframecompressormesh.h"
#include "core/func.h"
#include <cmath>
#include <vector>
#include <algorithm>

RenderFrameCompressorMesh::RenderFrameCompressorMesh()
{
}

RenderFrameCompressed *RenderFrameCompressorMesh::Compress(RenderFrame &frame)
{
    RenderFrameCompressed *result = new RenderFrameCompressed( frame );

    for( unsigned int iObj = 0; iObj < frame.scene.Objects.size(); iObj++ )
    {
        Obj &obj = *frame.scene.Objects[iObj];
        for( unsigned int iFace = 0; iFace < obj.Faces.size(); iFace++ )
        {
            Face *face = obj.Faces[iFace];

            if ( face->material->reflectance == NULL )
                continue;

            vector<RenderPoint*> *renderPointsFace = frame.faceRenderPoints[face];
            if ( renderPointsFace == NULL )
                continue;

            FaceLocalEstimate *f = FaceLocalEstimate::FromFace( *face, renderPointsFace );
            this->GenerateFrameFromFace( *f, *result );

        }
    }

    // Формирование центральной расчетной точки внутри грани
    for( unsigned int i = 0; i < result->renderPointsFaces.size(); i++ )
    {
        FaceLocalEstimate &face = *result->renderPointsFaces[i];

        face.vertices[0]->facesLocalEstimate.push_back( &face );
        face.vertices[1]->facesLocalEstimate.push_back( &face );
        face.vertices[2]->facesLocalEstimate.push_back( &face );

        Point3D center = ( face.vertices[0]->renderPoint.position + face.vertices[1]->renderPoint.position + face.vertices[2]->renderPoint.position ) / 3;
        Vector3D direction = ( face.vertices[0]->renderPoint.direction + face.vertices[1]->renderPoint.direction + face.vertices[2]->renderPoint.direction ) / 3;
        direction.Normalize();

        VertexLocalEstimate *vertexCenter = new VertexLocalEstimate( center, direction, face.face );
        face.center = vertexCenter;
        result->renderPoints.push_back( vertexCenter );
    }

    return result;
}

void RenderFrameCompressorMesh::BugsCorrection(RenderFrameCompressed &compressedFrame)
{
    const float threshold = 0.3;
    const float coeff = 0.85;

    vector<VertexLocalEstimate*> correctedVertexes;

    for( unsigned int i = 0; i < compressedFrame.renderPointsFaces.size(); i++ )
    {
        FaceLocalEstimate &face = *compressedFrame.renderPointsFaces[i];

        float counterRaysCos1Contrasts[3];
        counterRaysCos1Contrasts[0] = (float)( face.vertices[0]->counterRaysCos1Zero - face.vertices[1]->counterRaysCos1Zero ) / (float)( face.vertices[0]->counterRaysCos1Zero + face.vertices[1]->counterRaysCos1Zero );
        counterRaysCos1Contrasts[1] = (float)( face.vertices[1]->counterRaysCos1Zero - face.vertices[2]->counterRaysCos1Zero ) / (float)( face.vertices[1]->counterRaysCos1Zero + face.vertices[2]->counterRaysCos1Zero );
        counterRaysCos1Contrasts[2] = (float)( face.vertices[2]->counterRaysCos1Zero - face.vertices[0]->counterRaysCos1Zero ) / (float)( face.vertices[2]->counterRaysCos1Zero + face.vertices[0]->counterRaysCos1Zero );

        for ( int i = 0; i < 3; i++ )
            if ( isnan( counterRaysCos1Contrasts[i] ) )
                counterRaysCos1Contrasts[i] = 0;


        vector<VertexLocalEstimate*> correctionVertexes;

        // на основе контраста определяем корректируемые точки в треугольнике
        if ( counterRaysCos1Contrasts[0] > threshold || counterRaysCos1Contrasts[2] < -threshold )
            correctionVertexes.push_back( face.vertices[0] );
        if ( counterRaysCos1Contrasts[0] < -threshold || counterRaysCos1Contrasts[1] > threshold )
            correctionVertexes.push_back( face.vertices[1] );
        if ( counterRaysCos1Contrasts[1] < -threshold || counterRaysCos1Contrasts[2] > threshold )
            correctionVertexes.push_back( face.vertices[2] );

        for( unsigned int j = 0; j < correctionVertexes.size(); j++  )
        {
            VertexLocalEstimate *vertex = correctionVertexes[j];


            if ( std::find( correctedVertexes.begin(), correctedVertexes.end(), vertex) != correctedVertexes.end() )
            {
                // Вершина уже была откорректирована
                continue;
            }


            // рассчитываем результирующую яркость для корректируемой точки
            Spectrum centeredIll(0);

            Coordinate fullLength = 0;
            for( unsigned int k = 0; k < vertex->facesLocalEstimate.size(); k++ )
            {
                FaceLocalEstimate *ff = vertex->facesLocalEstimate[k];
                //if ( ff->center == NULL )
                //    continue;

                RenderPoint &rp = ff->center->renderPoint;
                fullLength += ( rp.position - vertex->renderPoint.position ).Length();
            }

            for( unsigned int k = 0; k < vertex->facesLocalEstimate.size(); k++ )
            {
                FaceLocalEstimate *ff = vertex->facesLocalEstimate[k];
                RenderPoint &rp = ff->center->renderPoint;
                //if ( ff->center == NULL )
                //    continue;

                Coordinate l1 = ( rp.position - vertex->renderPoint.position ).Length();
                centeredIll += ff->center->illuminance * ( l1 / fullLength );
            }

            //face.center->illuminance;// Spectrum(1, 0, 0);  //
            vertex->illuminance = vertex->illuminance * ( 1 - coeff ) + centeredIll * coeff;
            vertex->renderPoint.illuminanceIndirect = vertex->illuminance;
            correctedVertexes.push_back( vertex );

        }
    }
}

void RenderFrameCompressorMesh::UncompressIlluminance(RenderFrameCompressed &compressedFrame)
{
    this->BugsCorrection( compressedFrame );

    for( unsigned int i = 0; i < compressedFrame.renderPointsFaces.size(); i++ )
    {
        FaceLocalEstimate &face = *compressedFrame.renderPointsFaces[i];
        Spectrum e[3];
        e[0] = face.vertices[0]->renderPoint.illuminanceIndirect;
        e[1] = face.vertices[1]->renderPoint.illuminanceIndirect;
        e[2] = face.vertices[2]->renderPoint.illuminanceIndirect;

        float bc[3];
        for( unsigned int k = 0; k < face.renderPoints->size(); k++ )
        {
            RenderPoint *renderPoint = (*face.renderPoints)[k];
            face.FillBarycentricCoordinates( renderPoint->position, bc );

            Spectrum x = ( e[0] * bc[1] ) + ( e[1] * bc[2] ) + ( e[2] * bc[0] );

            renderPoint->illuminanceIndirect = x;
        }
    }
}

void RenderFrameCompressorMesh::GenerateFrameFromFace(FaceLocalEstimate &face, RenderFrameCompressed &frame)
{
    vector<FaceLocalEstimate *> facesList;
    facesList.push_back( &face );
    frame.renderPoints.push_back( face.vertices[0] );
    frame.renderPoints.push_back( face.vertices[1] );
    frame.renderPoints.push_back( face.vertices[2] );
    frame.renderPointsFaces.push_back( &face );

    //for( unsigned int i = 0; i < facesList.size(); i++ )
    unsigned int i = 0;
    while( i < facesList.size() )
    {
        FaceLocalEstimate &currentFace = *facesList[i];

        while ( currentFace.renderPoints->size() > 16 )
        //while ( currentFace.DivideDeep < 10 /*&& currentFace.renderPoints->size() > 128*/ )
        {
            // Ищем самую длинную сторону
            Coordinate v12l = ( currentFace.vertices[0]->renderPoint.position - currentFace.vertices[1]->renderPoint.position ).Length2();
            Coordinate v23l = ( currentFace.vertices[1]->renderPoint.position - currentFace.vertices[2]->renderPoint.position ).Length2();
            Coordinate v31l = ( currentFace.vertices[2]->renderPoint.position - currentFace.vertices[0]->renderPoint.position ).Length2();

            int k[3];
            if ( v12l > v23l && v12l > v31l )
            { k[0] = 0; k[1] = 1; k[2] = 2; }
            else if ( v23l > v12l && v23l > v31l )
            { k[0] = 1; k[1] = 2; k[2] = 0; }
            else
            { k[0] = 2; k[1] = 0; k[2] = 1; }


            // Вычисляю координату новой вершины - центра гиппотренузы
            Point3D p = ( currentFace.vertices[k[0]]->renderPoint.position - currentFace.vertices[k[1]]->renderPoint.position ) / (float)2
                    + currentFace.vertices[k[1]]->renderPoint.position;

            Vector3D newVertexDirection = currentFace.vertices[0]->renderPoint.direction;
                    //FaceLocalEstimate::GetNearestRenderPoint( currentFace.renderPoints, p )->direction;
            VertexLocalEstimate *newVertex = new VertexLocalEstimate( p, newVertexDirection, currentFace.face );

            VertexLocalEstimate *newPoints[3];
            newPoints[k[1]] = currentFace.vertices[k[2]];
            newPoints[k[2]] = currentFace.vertices[k[0]];
            newPoints[k[0]] = newVertex;

            // changed vertex
            //VertexLocalEstimate *changedVertex = currentFace.vertices[k[0]];

            // ----------------------------------------------------------------
            // TODO: Видимо этот блок можно вовсе удалить
            // remove current face from changedVertex
            /*
            vector<FaceLocalEstimate*> v = changedVertex->facesLocalEstimate;
            for( std::vector<FaceLocalEstimate*>::iterator iter = v.begin(); iter != v.end(); ++iter )
            {
                if( *iter == &currentFace )
                {
                    v.erase( iter );
                    break;
                }
                else
                {
                    int a = 10;
                }
            }
            // ----------------------------------------------------------------
            */
            currentFace.vertices[k[0]] = newVertex;

            FaceLocalEstimate *newFace = new FaceLocalEstimate( currentFace.face, newPoints[0], newPoints[1], newPoints[2] );

            currentFace.divideDeep++;
            newFace->divideDeep = currentFace.divideDeep;

            //newPoints[0]->facesLocalEstimate.push_back( newFace );
            //newPoints[1]->facesLocalEstimate.push_back( newFace );
            //newPoints[2]->facesLocalEstimate.push_back( newFace );


            // Resorting render points from current and new face
            vector<RenderPoint*> *oldPoints = new vector<RenderPoint*>();
            for( unsigned int k = 0; k < currentFace.renderPoints->size(); k++ )
            {
                RenderPoint *renderPoint = (*currentFace.renderPoints)[k];

                if ( !currentFace.IsPointInTriangleFace( *renderPoint ) )
                    newFace->renderPoints->push_back( renderPoint );
                else
                    oldPoints->push_back( renderPoint );
            }

            // change render points from current face
            delete currentFace.renderPoints;
            currentFace.renderPoints = oldPoints;

            if ( newFace->renderPoints->size() > 0 )
            {
                // новая грань пригодна для расчетов, так как в ней есть расчетные точки
                facesList.push_back( newFace );
                frame.renderPointsFaces.push_back( newFace );
            }

            frame.renderPoints.push_back( newVertex );

        }

        i++;
    }
}
