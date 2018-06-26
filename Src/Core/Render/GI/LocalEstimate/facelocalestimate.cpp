#include "facelocalestimate.h"
#include "Core/constants.h"
#include "Core/math3d.h"
#include <limits>
#include <cmath>

RenderPoint *FaceLocalEstimate::GetNearestRenderPoint( vector<RenderPoint *> *renderPoints, const Point3D position)
{
    RenderPoint* result = NULL;
    Coordinate length2 = std::numeric_limits<float>::max();
    for( unsigned int i = 0; i < renderPoints->size(); i++ )
    {
        RenderPoint *renderPoint = (*renderPoints)[i];
        Coordinate tmp = ( renderPoint->position - position ).Length2();
        if ( tmp < length2 )
        {
            length2 = tmp;
            result = renderPoint;
        }
    }

    return result;
}

FaceLocalEstimate *FaceLocalEstimate::FromFace(Face &face, vector<RenderPoint *> *renderPoints )
{
    RenderPoint* p0 = FaceLocalEstimate::GetNearestRenderPoint( renderPoints, face.obj->Vertexes[face.VertexIndexes[0]] );
    RenderPoint* p1 = FaceLocalEstimate::GetNearestRenderPoint( renderPoints, face.obj->Vertexes[face.VertexIndexes[1]] );
    RenderPoint* p2 = FaceLocalEstimate::GetNearestRenderPoint( renderPoints, face.obj->Vertexes[face.VertexIndexes[2]] );

    VertexLocalEstimate *v0 = new VertexLocalEstimate( face.obj->Vertexes[face.VertexIndexes[0]], p0->direction, face );
    VertexLocalEstimate *v1 = new VertexLocalEstimate( face.obj->Vertexes[face.VertexIndexes[1]], p1->direction, face );
    VertexLocalEstimate *v2 = new VertexLocalEstimate( face.obj->Vertexes[face.VertexIndexes[2]], p2->direction, face );

    FaceLocalEstimate *result = new FaceLocalEstimate( face, v0, v1, v2, renderPoints );

    return result;
}

double FaceLocalEstimate::Square( double ax1, double ay1, double ax2, double ay2, double ax3, double ay3 )
{
    return fabs( ax2 * ay3 - ax3 * ay2 - ax1 * ay3 + ax3 * ay1 + ax1 * ay2 - ax2 * ay1 );
}

FaceLocalEstimate::FaceLocalEstimate(Face &_face, VertexLocalEstimate *v0, VertexLocalEstimate *v1, VertexLocalEstimate *v2 )
    : face( _face ), renderPoints( new vector<RenderPoint *> ), divideDeep(0), center( NULL )
{
    this->vertices[0] = v0;
    this->vertices[1] = v1;
    this->vertices[2] = v2;
}

FaceLocalEstimate::FaceLocalEstimate(Face &_face, VertexLocalEstimate *v0, VertexLocalEstimate *v1, VertexLocalEstimate *v2, vector<RenderPoint *> *_renderPoints )
    : face( _face ), renderPoints( new vector<RenderPoint *> ), divideDeep(0), center( NULL )
{
    this->vertices[0] = v0;
    this->vertices[1] = v1;
    this->vertices[2] = v2;

    for( unsigned int i = 0; i < _renderPoints->size(); i++ )
        this->renderPoints->push_back( (*_renderPoints)[i] );
}

FaceLocalEstimate::~FaceLocalEstimate()
{
    delete this->renderPoints;
}

bool FaceLocalEstimate::IsPointInTriangleFace( const RenderPoint &point )
{
    Point3D &v0 = this->vertices[0]->renderPoint.position;
    Point3D &v1 = this->vertices[1]->renderPoint.position;
    Point3D &v2 = this->vertices[2]->renderPoint.position;

    if ( fabs( this->face.normal.Z ) > Constants::Eps )
    {
        double s = Square( point.position.X, point.position.Y, v0.X, v0.Y, v1.X, v1.Y ) +
                   Square( point.position.X, point.position.Y, v1.X, v1.Y, v2.X, v2.Y ) +
                   Square( point.position.X, point.position.Y, v2.X, v2.Y, v0.X, v0.Y );
        return fabs( Square( v0.X, v0.Y, v1.X, v1.Y, v2.X, v2.Y ) - s ) <= Constants::Eps2;
    }
    else if ( fabs( this->face.normal.X ) > Constants::Eps )
    {
        double s = Square( point.position.Z, point.position.Y, v0.Z, v0.Y, v1.Z, v1.Y ) +
                   Square( point.position.Z, point.position.Y, v1.Z, v1.Y, v2.Z, v2.Y ) +
                   Square( point.position.Z, point.position.Y, v2.Z, v2.Y, v0.Z, v0.Y );
        return fabs( Square( v0.Z, v0.Y, v1.Z, v1.Y, v2.Z, v2.Y ) - s ) <= Constants::Eps2;
    }
    else
    {
        double s = Square( point.position.X, point.position.Z, v0.X, v0.Z, v1.X, v1.Z ) +
                   Square( point.position.X, point.position.Z, v1.X, v1.Z, v2.X, v2.Z ) +
                   Square( point.position.X, point.position.Z, v2.X, v2.Z, v0.X, v0.Z );
        return fabs( Square( v0.X, v0.Z, v1.X, v1.Z, v2.X, v2.Z ) - s ) <= Constants::Eps2;
    }
}

void FaceLocalEstimate::FillBarycentricCoordinates( const Point3D &point, Coordinate coordinates[] )
{
    Point3D p0 = this->vertices[0]->renderPoint.position;
    Point3D p1 = this->vertices[1]->renderPoint.position;
    Point3D p2 = this->vertices[2]->renderPoint.position;

    Coordinate l01 = ( p0 - p1 ).Length();
    Coordinate l12 = ( p1 - p2 ).Length();
    Coordinate l20 = ( p2 - p0 ).Length();

    Coordinate lp0 = ( point - p0 ).Length();
    Coordinate lp1 = ( point - p1 ).Length();
    Coordinate lp2 = ( point - p2 ).Length();

    Coordinate area = Math3D::TriangleAreaByGeron( l01, l12, l20 );

    Coordinate a01 = Math3D::TriangleAreaByGeron( l01, lp0, lp1 ) / area;
    Coordinate a12 = Math3D::TriangleAreaByGeron( l12, lp1, lp2 ) / area;

    coordinates[0] = a01;
    coordinates[1] = a12;
    coordinates[2] = 1 - a01 - a12;
    //return new double[] { a01, a12, 1 - a01 - a12 };
}
