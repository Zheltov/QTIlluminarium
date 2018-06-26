#ifndef RENDERFRAMELOCALESTIMATE_H
#define RENDERFRAMELOCALESTIMATE_H

#include "renderpointlocalestimate.h"

class RenderFrameLocalEstimate
{
public:
    vector<RenderPointLocalEstimate*> renderPoints;

    RenderFrameLocalEstimate();
    virtual ~RenderFrameLocalEstimate();

    void AddRenderPoint( RenderPointLocalEstimate &renderPoint );
};

#endif // RENDERFRAMELOCALESTIMATE_H
