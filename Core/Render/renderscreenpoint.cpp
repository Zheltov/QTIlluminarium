#include "renderscreenpoint.h"

RenderScreenPoint::RenderScreenPoint(int _x, int _y, RenderPoint &_renderPoint) : x(_x), y(_y), renderPoint(_renderPoint), illuminanceDirect(0), illuminanceIndirect(0)
{
}

int RenderScreenPoint::getX()
{
    return this->x;
}

int RenderScreenPoint::getY()
{
    return this->y;
}

RenderPoint &RenderScreenPoint::getRenderPoint()
{
    return this->renderPoint;
}
