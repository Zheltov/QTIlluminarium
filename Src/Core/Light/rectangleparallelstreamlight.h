#ifndef RECTANGLEPARALLELSTEAMLIGHT_H
#define RECTANGLEPARALLELSTEAMLIGHT_H

#include "Core/Light/light.h"
#include "Core/Objects/obj.h"
#include <vector>

using namespace std;

class RectangleParallelStreamLight : public Light, public Obj
{
public:
    RectangleParallelStreamLight( const Point3D &_position, Coordinate _length, Coordinate _width, Spectrum _illuminance, Material &_material, Vector3D _directionLight );

    virtual Spectrum GetIlluminance( RayTracer &rayTracer, const Point3D &point, const Vector3D &normal, const Vector3D &view, const Material &material );
    virtual Spectrum GetIlluminanceSurfacePoint( const Point3D &point, const Vector3D &direction );

    virtual LightRay GetRandomRay();

private:
    Vector3D direction;
    Vector3D directionLight;

    Point3D position;
    Coordinate length;
    Coordinate width;
    Spectrum illuminance;
    Material material;

};

#endif // RECTANGLEPARALLELSTEAMLIGHT_H
