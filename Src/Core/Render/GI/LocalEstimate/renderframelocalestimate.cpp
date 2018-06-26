#include "renderframelocalestimate.h"

RenderFrameLocalEstimate::RenderFrameLocalEstimate()
{
}

RenderFrameLocalEstimate::~RenderFrameLocalEstimate()
{
    for( unsigned int i = 0; i < this->renderPoints.size(); i++ )
        delete this->renderPoints[i];
}

void RenderFrameLocalEstimate::AddRenderPoint( RenderPointLocalEstimate &renderPoint )
{
    this->renderPoints.push_back( &renderPoint );
}
