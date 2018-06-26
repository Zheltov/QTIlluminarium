#ifndef MATERIAL_H
#define MATERIAL_H

#include "reflectancematerial.h"
#include "mirrormaterial.h"

class Material
{
public:
    ReflectanceMaterial *reflectance;
    MirrorMaterial *mirror;

    Material();
    Material( ReflectanceMaterial *_reflectance );
    Material( MirrorMaterial *_mirror );
    Material( ReflectanceMaterial *_reflectance, MirrorMaterial *_mirror );
    virtual ~Material() {}
};

#endif // MATERIAL_H
