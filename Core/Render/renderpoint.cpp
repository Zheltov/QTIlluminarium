#include "renderpoint.h"


RenderPoint::RenderPoint(const Point3D _position, const Vector3D _direction, Face &_face )
    : position(_position),
      direction(_direction),
      face(_face),
      illuminanceDirect(0),
      illuminanceIndirect(0),
      mirrorRenderPoint(NULL)
{
}
