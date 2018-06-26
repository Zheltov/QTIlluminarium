#ifndef FACELOCALESTIMATE_H
#define FACELOCALESTIMATE_H

#include "Core/Render/renderpoint.h"
#include "vertexlocalestimate.h"

// forward declaration
//class FaceLocalEstimate;

class FaceLocalEstimate
{
public:
    Face &face;
    vector<RenderPoint *> *renderPoints;
    VertexLocalEstimate *vertices[3];
    VertexLocalEstimate *center;
    unsigned int divideDeep;

    FaceLocalEstimate( Face &_face, VertexLocalEstimate *v0, VertexLocalEstimate *v1, VertexLocalEstimate *v2 );
    FaceLocalEstimate(Face &_face, VertexLocalEstimate *v0, VertexLocalEstimate *v1, VertexLocalEstimate *v2, vector<RenderPoint *> *_renderPoints );
    virtual ~FaceLocalEstimate();


    bool IsPointInTriangleFace( const RenderPoint &point );
    void FillBarycentricCoordinates( const Point3D &point, Coordinate coordinates[] );


    static RenderPoint *GetNearestRenderPoint(vector<RenderPoint *> *renderPoints, const Point3D position );
    static FaceLocalEstimate *FromFace(Face &face, vector<RenderPoint *> *renderPoints);
    static double Square( double ax1, double ay1, double ax2, double ay2, double ax3, double ay3 );
};

#endif // FACELOCALESTIMATE_H
