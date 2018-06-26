#ifndef RECTANGLELIGHT_H
#define RECTANGLELIGHT_H

#include "Core/Light/light.h"
#include "Core/Objects/obj.h"
#include <vector>

using namespace std;

class RectangleLight : public Light, public Obj
{
public:
    RectangleLight( const Point3D &_position, Coordinate _length, Coordinate _width, Spectrum _illuminance, Material &_material, int _samples = 32 );

    virtual Spectrum GetIlluminance( RayTracer &rayTracer, const Point3D &point, const Vector3D &normal, const Vector3D &view, const Material &material );
    virtual Spectrum GetIlluminanceSurfacePoint( const Point3D &point, const Vector3D &direction );

    virtual LightRay GetRandomRay();

private:
    Vector3D direction;
    Point3D position;
    Coordinate length;
    Coordinate width;
    Spectrum illuminance;
    Material material;
    int samples;
    vector<Point3D> samplePoints;


    Coordinate GetFormFactor(const Point3D &point );
    void GenerateSamplePoints();
};

#endif // RECTANGLELIGHT_H
