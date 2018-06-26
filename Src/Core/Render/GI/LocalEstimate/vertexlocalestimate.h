#ifndef VERTEXLOCALESTIMATE_H
#define VERTEXLOCALESTIMATE_H

#include "Core/Render/renderpoint.h"
#include "renderpointlocalestimate.h"
//#include "facelocalestimate.h"

// forward declaration
class FaceLocalEstimate;

class VertexLocalEstimate : public RenderPointLocalEstimate
{
public:
    vector<FaceLocalEstimate*> facesLocalEstimate;

    VertexLocalEstimate(const Point3D _position, const Vector3D _direction, Face &_face );
    virtual ~VertexLocalEstimate();
};

#endif // VERTEXLOCALESTIMATE_H
