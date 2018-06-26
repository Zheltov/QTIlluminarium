#ifndef RENDERVIEWFRAME_H
#define RENDERVIEWFRAME_H

#include "renderframe.h"

#include <vector>

using namespace std;

class RenderViewFrame : public RenderFrame
{
public:
    int width;
    int height;
    vector<RenderScreenPoint*> renderScreenPoints;

    RenderViewFrame( Scene &_scene, int w, int h);
    virtual ~RenderViewFrame();

    void AddRenderScreenPoint( RenderScreenPoint *renderScreenPoint );
    void FinalGathering();

};

#endif // RENDERVIEWFRAME_H
