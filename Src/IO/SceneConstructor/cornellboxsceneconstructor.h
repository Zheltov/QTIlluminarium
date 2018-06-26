#ifndef CORNELLBOXSCENECONSTRUCTOR_H
#define CORNELLBOXSCENECONSTRUCTOR_H

#include "IO/sceneconstructor.h"

class CornellBoxSceneConstructor : public SceneConstructor
{
public:
    CornellBoxSceneConstructor();

    virtual Scene *CreateScene();
    virtual void SetDefaultCameraParameters( Camera &camera );
};

#endif // CORNELLBOXSCENECONSTRUCTOR_H
