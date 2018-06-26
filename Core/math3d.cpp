#include "math3d.h"

#include <math.h>



Coordinate Math3D::SolidAngle(const Point3D &p1, const Point3D &p2, const Point3D &p3)
{
    Coordinate result = 0;

    // numerator
    Point3D crossp2p3 = p2 * p3;
    Coordinate numerator = Point3D::Dot( p1, crossp2p3 );

    // denominator
    Coordinate p1Length = p1.Length();
    Coordinate p2Length = p2.Length();
    Coordinate p3Length = p3.Length();

    Coordinate denominator = p1Length * p2Length * p3Length + Point3D::Dot( p1, p2 ) * p3Length + Point3D::Dot( p2, p3 ) * p1Length + Point3D::Dot( p3, p1 ) * p2Length;

    return 2 * fabs( atanf( numerator / denominator ) );
}


Coordinate Math3D::SolidAngle(const Point3D &p1, const Point3D &p2, const Point3D &p3, const Point3D &viewPoint)
{
    Point3D r1 = p1 - viewPoint;
    Point3D r2 = p2 - viewPoint;
    Point3D r3 = p3 - viewPoint;

    return Math3D::SolidAngle( r1, r2, r3 );
}

Coordinate Math3D::TriangleAreaByGeron( Coordinate a, Coordinate b, Coordinate c )
{
    Coordinate p = ( a + b + c ) / 2;

    return sqrt( fabs( p*(p - a)*(p - b)*(p - c) ) );
}
