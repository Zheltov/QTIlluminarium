#ifndef INTERSECTION_H
#define INTERSECTION_H

#include "Core/types.h"
#include "Core/Objects/obj.h"
#include "Core/Objects/face.h"

class Intersection
{
public:

    Intersection( Point3D pos, Obj &_obj, Face &_face );

    Point3D getPosition();
    Obj &getObj();
    Face &getFace();

private:
    Point3D position;
    Obj &obj;
    Face &face;
};

#endif // INTERSECTION_H
