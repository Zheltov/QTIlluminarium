#include "material.h"


Material::Material() : reflectance(0), mirror(0)
{

}

Material::Material(ReflectanceMaterial *_reflectance)
    : reflectance( _reflectance ), mirror( 0 )
{
}

Material::Material(MirrorMaterial *_mirror)
    : reflectance( 0 ), mirror( _mirror )
{
}

Material::Material(ReflectanceMaterial *_reflectance, MirrorMaterial *_mirror)
    : reflectance( _reflectance ), mirror( _mirror )
{

}
