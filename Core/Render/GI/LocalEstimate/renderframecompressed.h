#ifndef RENDERFRAMECOMPRESSED_H
#define RENDERFRAMECOMPRESSED_H

#include "Core/Render/renderframe.h"
#include "facelocalestimate.h"
#include "renderpointlocalestimate.h"

class RenderFrameCompressed
{
public:
    RenderFrameCompressed( RenderFrame &_renderFrame );
    virtual ~RenderFrameCompressed();

    RenderFrame &renderFrame;
    vector<VertexLocalEstimate*> renderPoints;
    vector<FaceLocalEstimate*> renderPointsFaces;
};

#endif // RENDERFRAMECOMPRESSED_H
