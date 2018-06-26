#include "renderframe.h"

RenderFrame::RenderFrame(Scene &_scene) : scene( _scene )
{
}

RenderFrame::~RenderFrame()
{
    for( unsigned int i = 0; i < this->renderPoints.size(); i++ )
    {
        RenderPoint *p = this->renderPoints[i];

        delete p;
    }
    this->renderPoints.clear();

    for( FaceRenderPointMapIterator iterator = this->faceRenderPoints.begin(); iterator != this->faceRenderPoints.end(); iterator++) {
        delete iterator->second;
    }
    this->faceRenderPoints.clear();
}


void RenderFrame::AddRenderPoint(RenderPoint *renderPoint)
{
    //this->renderPoints.push_back( boost::shared_ptr<RenderPoint>( renderPoint ) );
    this->renderPoints.push_back( renderPoint );

    vector<RenderPoint*> *frp = this->faceRenderPoints[&renderPoint->face];
    if ( frp == NULL )
    {
        frp = new vector<RenderPoint*>();
        this->faceRenderPoints[&renderPoint->face] = frp;
    }
    frp->push_back( renderPoint );

}
