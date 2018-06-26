#ifndef SCENECREATORDUBROVNIKSPONZA_H
#define SCENECREATORDUBROVNIKSPONZA_H

#include "IO/sceneconstructor.h"

class SceneCreatorDubrovnikSponza : public SceneConstructor
{
public:
    SceneCreatorDubrovnikSponza();

    virtual Scene *CreateScene();
    virtual void SetDefaultCameraParameters( Camera &camera );
};

#endif // SCENECREATORDUBROVNIKSPONZA_H
