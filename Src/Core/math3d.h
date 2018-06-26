#ifndef MATH3D_H
#define MATH3D_H

#include "types.h"

namespace Math3D {

Coordinate SolidAngle(const Point3D &p1, const Point3D &p2, const Point3D &p3 );

Coordinate SolidAngle(const Point3D &p1, const Point3D &p2, const Point3D &p3, const Point3D &viewPoint );

Coordinate TriangleAreaByGeron( Coordinate a, Coordinate b, Coordinate c );

}

#endif // MATH3D_H
