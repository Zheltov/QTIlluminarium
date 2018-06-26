#include "vertexlocalestimate.h"

VertexLocalEstimate::VertexLocalEstimate(const Point3D _position, const Vector3D _direction, Face &_face)
    : RenderPointLocalEstimate( *(new RenderPoint( _position, _direction, _face ) ) )
{

}

VertexLocalEstimate::~VertexLocalEstimate()
{
    delete &this->renderPoint;
}
