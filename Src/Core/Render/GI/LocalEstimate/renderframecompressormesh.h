#ifndef RENDERFRAMECOMPRESSORMESH_H
#define RENDERFRAMECOMPRESSORMESH_H

#include "Core/Render/renderframe.h"
#include "renderframecompressed.h"
#include "renderframelocalestimate.h"

class RenderFrameCompressorMesh
{
public:
    RenderFrameCompressorMesh();

    RenderFrameCompressed *Compress( RenderFrame &frame );
    void UncompressIlluminance( RenderFrameCompressed &compressedFrame );

private:    
    void BugsCorrection( RenderFrameCompressed &compressedFrame );
    void GenerateFrameFromFace( FaceLocalEstimate &face, RenderFrameCompressed &frame );
};

#endif // RENDERFRAMECOMPRESSORMESH_H
