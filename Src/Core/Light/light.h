#ifndef LIGHT_H
#define LIGHT_H

#include "Core/types.h"
#include "Core/Material/material.h"
//#include "Core/RayTracer/raytracer.h"

// forward declaration
class RayTracer;

struct LightRay : public Ray
{
public:
    Spectrum illuminance;

    LightRay( Point3D _from, Point3D _to, Spectrum _illuminance );
    LightRay( Point3D _from, Vector3D _dir, Spectrum _illuminance );

};

class Light
{
public:
    Light();
    virtual ~Light();

    virtual Spectrum GetIlluminance( RayTracer &rayTracer, const Point3D &point, const Vector3D &normal, const Vector3D &view, const Material &material ) = 0;
    virtual Spectrum GetIlluminanceSurfacePoint( const Point3D &point, const Vector3D &direction ) = 0;

    virtual LightRay GetRandomRay() = 0;
};



#endif // LIGHT_H
