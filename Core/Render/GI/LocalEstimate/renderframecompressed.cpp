#include "renderframecompressed.h"

RenderFrameCompressed::RenderFrameCompressed(RenderFrame &_renderFrame) : renderFrame( _renderFrame )
{

}

RenderFrameCompressed::~RenderFrameCompressed()
{
    for( unsigned int i = 0; i < this->renderPoints.size(); i++ )
        delete this->renderPoints[i];

    for( unsigned int i = 0; i < this->renderPointsFaces.size(); i++ )
        delete this->renderPointsFaces[i];
}
