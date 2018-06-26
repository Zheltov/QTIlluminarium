#ifndef RENDERSCREENPOINT_H
#define RENDERSCREENPOINT_H

#include "renderpoint.h"

class RenderScreenPoint
{
public:
    Spectrum illuminanceDirect;
    Spectrum illuminanceIndirect;

    RenderScreenPoint(int _x, int _y, RenderPoint &_renderPoint );

    int getX();
    int getY();
    RenderPoint &getRenderPoint();

private:
    int x;
    int y;
    RenderPoint &renderPoint;
};

#endif // RENDERSCREENPOINT_H
