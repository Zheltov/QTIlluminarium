#ifndef MIRRORMATERIAL_H
#define MIRRORMATERIAL_H

#include "Core/types.h"

class MirrorMaterial
{
public:
    Spectrum reflectance;

    MirrorMaterial( Spectrum _reflectance );
    virtual ~MirrorMaterial() {}
};

#endif // MIRRORMATERIAL_H
