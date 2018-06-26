#include "rectanglelight.h"

#include "Core/math3d.h"
#include "Core/constants.h"
#include "Core/RayTracer/raytracer.h"
#include "Core/constants.h"
#include "Core/func.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

RectangleLight::RectangleLight( const Point3D &_position, Coordinate _length, Coordinate _width, Spectrum _illuminance, Material &_material, int _samples )
    : position(_position), length(_length), width(_width), illuminance(_illuminance), material(_material), samples(_samples)
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

Spectrum RectangleLight::GetIlluminance( RayTracer &rayTracer, const Point3D &point, const Vector3D &normal, const Vector3D &view, const Material &material)
{
    Coordinate xx = Vector3D::Dot( normal, this->direction );
    if ( xx > Constants::Eps || point.Z > this->position.Z )
        return Spectrum( 0 );

    Coordinate formFactor = this->GetFormFactor( point );

    if ( this->samplePoints.size() == 0 )
        this->GenerateSamplePoints();

    Spectrum result(0);
    //int raysHited = 0;
    for( int i = 0; i < this->samples; i++ )
    {
        Point3D toLight = this->samplePoints[i] - point;
        Vector3D toLightVector = toLight.ToVector3D(true);

        if ( !rayTracer.Occluded( point, toLightVector, Constants::Eps, toLight.Length() - Constants::Eps ) )
        {
            // источник косинусный
            Coordinate cosR = -Vector3D::Dot( toLightVector, this->direction );
            result += material.reflectance->BRDF( toLightVector, normal, view ) * cosR;
            //raysHited++;
        }
    }

    //if ( raysHited == 0 )
    //    return Spectrum(0);

    result *= formFactor / (float)( this->samples );
    result *= this->illuminance;

    //result = result / (float)raysHited;

    //Spectrum s = this->illuminance * result;

    //result = this->illuminance * result * ( formFactor * (float)raysHited / (float)( this->samples ) );

    return result;
}

Spectrum RectangleLight::GetIlluminanceSurfacePoint(const Point3D &point, const Vector3D &direction)
{
    return this->illuminance;
}

LightRay RectangleLight::GetRandomRay()
{
    float xx = func::randf();
    float yy = func::randf();

    // get random point on light
    float dx = ( 0.5 - xx ) * this->length;
    float dy = ( 0.5 - yy ) * this->width;
    float x = this->position.X + dx;
    float y = this->position.Y + dy;
    float z = this->position.Z;

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

    // get light ray
    Point3D point( x, y, z );
    Vector3D direction( -( sPhi * cTheta ), -( sPhi * sTheta ), -cPhi );

    LightRay result( point, direction, this->GetIlluminanceSurfacePoint( point, direction ) );

    return result;
}

Coordinate RectangleLight::GetFormFactor(const Point3D &point)
{
    Face *face0 = this->Faces[0];
    Face *face1 = this->Faces[1];
    Coordinate sa1 = Math3D::SolidAngle( this->Vertexes[face0->VertexIndexes[0]], this->Vertexes[face0->VertexIndexes[1]], this->Vertexes[face0->VertexIndexes[2]], point );
    Coordinate sa2 = Math3D::SolidAngle( this->Vertexes[face1->VertexIndexes[0]], this->Vertexes[face1->VertexIndexes[1]], this->Vertexes[face1->VertexIndexes[2]], point );

    // косинус угла на источник от точки
    Coordinate cosa = fabs( Vector3D::Dot( this->direction, Vector3D( this->position, point, true ) ) );

    return ( sa1 + sa2 ) * cosa;
}

void RectangleLight::GenerateSamplePoints()
{
    for ( int i = 0; i < this->samples; i++ )
    {
        float r1 = func::randf(); //static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
        float r2 = func::randf(); //static_cast <float> (rand()) / static_cast <float> (RAND_MAX);

        Coordinate dl = (Coordinate)( this->length / 2 - this->length * r1 );
        Coordinate dw = (Coordinate)( this->width / 2 - this->width * r2 );
        this->samplePoints.push_back( Point3D( this->position.X + dl, this->position.Y + dw, this->position.Z ) );
    }
}
