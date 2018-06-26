#ifndef RENDERFRAME_H
#define RENDERFRAME_H

#include <vector>
#include <map>
//#include <boost/shared_ptr.hpp>

#include "Core/Objects/scene.h"
#include "renderpoint.h"
#include "renderscreenpoint.h"

using namespace std;


typedef map<Face*, vector<RenderPoint*>* > FaceRenderPointMap;
typedef FaceRenderPointMap::iterator FaceRenderPointMapIterator;


class RenderFrame
{
public:
    vector<RenderPoint*> renderPoints;
    FaceRenderPointMap faceRenderPoints;
    Scene &scene;
    //FaceRenderPointMap faceRenderPoints;


    RenderFrame( Scene &_scene );
    virtual ~RenderFrame();

    virtual void AddRenderPoint( RenderPoint *renderPoint );

private:

};

#endif // RENDERFRAME_H
