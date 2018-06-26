#include "intersection.h"

Intersection::Intersection( Point3D pos, Obj &_obj, Face &_face ) : position( pos ), obj( _obj ), face( _face )
{
}

Point3D Intersection::getPosition()
{
    return this->position;
}

Obj &Intersection::getObj()
{
    return this->obj;
}

Face &Intersection::getFace()
{
    return this->face;
}
