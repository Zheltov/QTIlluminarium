#ifndef REFLECTANCEMATERIAL_H
#define REFLECTANCEMATERIAL_H

#include "Core/types.h"

class ReflectanceMaterial
{
public:
    ReflectanceMaterial();
    virtual ~ReflectanceMaterial();

    virtual Spectrum BRDF(const Vector3D &fall, const Vector3D &normal, const Vector3D &view ) = 0;
    virtual Vector3D GetRandomReflectedDirection( const Vector3D &fall, const Vector3D &normal ) = 0;
};

#endif // REFLECTANCEMATERIAL_H
