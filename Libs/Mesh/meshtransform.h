#ifndef MESHTRANSFORM_H
#define MESHTRANSFORM_H

#include "Libs/SphericalHarmonics/sphericalharmonics.h"
#include "boost/multi_array.hpp"
#include "Core/RayTracer/raytracer.h"

class MeshTransform
{
public:
    static vector<double> &GetUniformTheta( unsigned int n );
    static vector<double> &GetUniformPhi( unsigned int n );

    static DoubleArray &MeshToAngleFunction( RayTracer &rayTracer, Point3D center, vector<double> &theta, vector<double> &phi );

    MeshTransform();
};

#endif // MESHTRANSFORM_H
