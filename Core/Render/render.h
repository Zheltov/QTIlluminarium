#ifndef RENDER_H
#define RENDER_H

#include "Core/Log.h"
#include "Core/RayTracer/raytracer.h"
#include "Core/Camera/camera.h"
#include "renderviewframe.h"
#include "renderpoint.h"
#include "Core/Render/GI/globalillumination.h"

class Render
{
public:
    Render( RayTracer &rt, GlobalIllumination &gi, Log &lg );

    RenderViewFrame *GetRenderFrame( const Camera &camera );

    void RenderDirectLight( RenderFrame &frame );
    void RenderGlobalIllumination( RenderFrame &frame );
    void RenderFull( RenderFrame &frame );

    void StopRender();

private:
    RayTracer &rayTracer;
    Log &log;
    GlobalIllumination &globalIllumination;

    void AddRenderPointRecursive( RenderViewFrame *frame, RenderPoint *renderPoint, RenderScreenPoint *renderScreenPoint = NULL );
};

#endif // RENDER_H
