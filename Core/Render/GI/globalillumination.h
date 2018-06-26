#ifndef GLOBALILLUMINATION_H
#define GLOBALILLUMINATION_H

#include "../renderframe.h"

class GlobalIllumination
{
public:
    GlobalIllumination();

    virtual void Render( RenderFrame &frame ) = 0;
    virtual void Stop() {}
};

#endif // GLOBALILLUMINATION_H
