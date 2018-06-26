#ifndef DIFFUSEMATERIAL_H
#define DIFFUSEMATERIAL_H

#include "reflectancematerial.h"

class DiffuseMaterial : public ReflectanceMaterial
{
public:
    Spectrum reflectance;

    DiffuseMaterial( Spectrum _reflectance );
    virtual ~DiffuseMaterial() {}

    virtual Spectrum BRDF(const Vector3D &, const Vector3D &, const Vector3D &);
    virtual Vector3D GetRandomReflectedDirection( const Vector3D &, const Vector3D &normal );
};

#endif // DIFFUSEMATERIAL_H
