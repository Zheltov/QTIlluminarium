#ifndef RENDERPOINT_H
#define RENDERPOINT_H

#include "Core/types.h"
#include "Core/Objects/obj.h"
#include "Core/Objects/face.h"


class RenderPoint;

class RenderPoint
{

public:
    Spectrum illuminanceDirect;
    Spectrum illuminanceIndirect;
    Face &face;
    Vector3D direction;
    Point3D position;

    RenderPoint *mirrorRenderPoint;


    RenderPoint(const Point3D _position, const Vector3D _direction, Face &_face );

private:



};

#endif // RENDERPOINT_H
