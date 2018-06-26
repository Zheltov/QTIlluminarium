#ifndef SCENECREATORCONFERENCEROOM_H
#define SCENECREATORCONFERENCEROOM_H

#include "IO/sceneconstructor.h"

class SceneCreatorConferenceRoom : public SceneConstructor
{
public:
    SceneCreatorConferenceRoom();

    virtual Scene *CreateScene();
    virtual void SetDefaultCameraParameters( Camera &camera );

};

#endif // SCENECREATORCONFERENCEROOM_H
