#include "RectangleParallelStreamLight.h"

#include "Core/math3d.h"
#include "Core/constants.h"
#include "Core/RayTracer/raytracer.h"
#include "Core/constants.h"
#include "Core/func.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

RectangleParallelStreamLight::RectangleParallelStreamLight( const Point3D &_position, Coordinate _length, Coordinate _width, Spectrum _illuminance, Material &_material, Vector3D _directionLight )
    : position(_position), length(_length), width(_width), illuminance(_illuminance), material(_material), directionLight(_directionLight)
{

    // Create geometry
    this->Vertexes.push_back( Point3D( this->position.X - this->length / 2, this->position.Y + this->width / 2, this->position.Z ) );
    this->Vertexes.push_back( Point3D( this->position.X + this->length / 2, this->position.Y + this->width / 2, this->position.Z ) );
    this->Vertexes.push_back( Point3D( this->position.X - this->length / 2, this->position.Y - this->width / 2, this->position.Z ) );
    this->Vertexes.push_back( Point3D( this->position.X + this->length / 2, this->position.Y - this->width / 2, this->position.Z ) );

    this->Faces.push_back( new Face( this, 0, 1, 2, &_material ) );
    this->Faces.push_back( new Face( this, 2, 1, 3, &_material ) );

    this->direction = Vector3D(0, 0, -1);
}

Spectrum RectangleParallelStreamLight::GetIlluminance( RayTracer &rayTracer, const Point3D &point, const Vector3D &normal, const Vector3D &view, const Material &material)
{
    const Vector3D toLightDir = this->directionLight * -1;
    const float eps = Constants::Eps1;
    const Point3D tmp = point + normal * eps;

    Intersection *intersection = rayTracer.Intersect( tmp, toLightDir );

    if ( intersection == NULL )
        return Spectrum(0);

    if ( this != &intersection->getObj() )
        return Spectrum(0);

    if ( material.reflectance == NULL )
        return Spectrum(0);

    Spectrum result = this->illuminance * material.reflectance->BRDF(this->directionLight, normal, view);

    return result;
}

Spectrum RectangleParallelStreamLight::GetIlluminanceSurfacePoint(const Point3D &point, const Vector3D &direction)
{
    return this->illuminance;
}

LightRay RectangleParallelStreamLight::GetRandomRay()
{
    float xx = func::randf();
    float yy = func::randf();

    // get random point on light
    float dx = ( 0.5 - xx ) * this->length;
    float dy = ( 0.5 - yy ) * this->width;
    float x = this->position.X + dx;
    float y = this->position.Y + dy;
    float z = this->position.Z;

    /*
    // get random direction
    float d = 2;
    float u = 0;
    float v = 0;
    while ( d > 1 )
    {
        u = 1 - 2 * func::randf();
        v = 1 - 2 * func::randf();
        d = u * u + v * v;
    }

    float Sqrt_d = sqrtf( d );
    float cTheta = u / Sqrt_d;
    float sTheta = v / Sqrt_d;
    float sPhi = sqrt( func::randf() );
    float cPhi = sqrt( 1 - sPhi * sPhi );

    */
    // get light ray
    Point3D point( x, y, z );
    //Vector3D direction( -( sPhi * cTheta ), -( sPhi * sTheta ), -cPhi );

    LightRay result( point, this->directionLight, this->GetIlluminanceSurfacePoint( point, direction ) );

    return result;
}
