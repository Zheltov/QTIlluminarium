#ifndef RENDERPOINTLOCALESTIMATE_H
#define RENDERPOINTLOCALESTIMATE_H

#include "Core/Render/renderpoint.h"

class RenderPointLocalEstimate
{
public:
    RenderPoint &renderPoint;

    int counterRaysCos1Zero;
    Spectrum illuminance;

    RenderPointLocalEstimate( RenderPoint &_renderPoint );
    virtual ~RenderPointLocalEstimate() {}
};

#endif // RENDERPOINTLOCALESTIMATE_H
