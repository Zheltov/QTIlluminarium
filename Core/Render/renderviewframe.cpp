#include "renderviewframe.h"

RenderViewFrame::RenderViewFrame( Scene &_scene, int w, int h )
    : RenderFrame( _scene ),
      width(w), height(h)
{
}

RenderViewFrame::~RenderViewFrame()
{
    for( unsigned int i = 0; i < this->renderScreenPoints.size(); i++ )
    {
        RenderScreenPoint *p = this->renderScreenPoints[i];
        delete p;
    }
}

void RenderViewFrame::AddRenderScreenPoint(RenderScreenPoint *renderScreenPoint)
{
    this->renderScreenPoints.push_back( renderScreenPoint );
    this->AddRenderPoint( &renderScreenPoint->getRenderPoint() );
}

void RenderViewFrame::FinalGathering()
{
    for( unsigned int i = 0; i < this->renderScreenPoints.size(); i++ )
    {
        RenderScreenPoint &renderScreenPoint = *this->renderScreenPoints[i];
        RenderPoint &renderPoint = renderScreenPoint.getRenderPoint();


        renderScreenPoint.illuminanceDirect = renderPoint.illuminanceDirect;
        renderScreenPoint.illuminanceIndirect = renderPoint.illuminanceIndirect;

        // Сбор дополнительной яркости с цепочки зеркальных точек
        RenderPoint *currentPoint = &renderPoint;
        RenderPoint *mirrorPoint = renderPoint.mirrorRenderPoint;
        while( mirrorPoint != NULL )
        {
            renderScreenPoint.illuminanceDirect += currentPoint->face.material->mirror->reflectance * mirrorPoint->illuminanceDirect;
            renderScreenPoint.illuminanceIndirect += currentPoint->face.material->mirror->reflectance * mirrorPoint->illuminanceIndirect;
            currentPoint = mirrorPoint;
            mirrorPoint = mirrorPoint->mirrorRenderPoint;
        }


    }
}
