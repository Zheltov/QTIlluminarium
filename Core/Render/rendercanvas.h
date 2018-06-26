#ifndef RENDERCANVAS_H
#define RENDERCANVAS_H

#include "Core/Render/renderpoint.h"

#include <vector>

using namespace std;

class RenderCanvas
{
public:
    RenderCanvas();

    void x();

    void AddRenderPoint( const RenderPoint &renderPoint );

private:
    //vector<const RenderPoint*> renderPoints;
};

#endif // RENDERCANVAS_H
