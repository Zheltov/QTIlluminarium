#ifndef SCENECONSTRUCTOR_H
#define SCENECONSTRUCTOR_H

#include <Core/Objects/scene.h>
#include <Core/Camera/camera.h>

class SceneConstructor
{
public:
    SceneConstructor() {}

    virtual ~SceneConstructor() {}

    virtual Scene *CreateScene( ) = 0;
    virtual void SetDefaultCameraParameters( Camera &camera ) = 0;

protected:
    void setMaterial(Obj *o, Material *m);

};

#endif // SCENECONSTRUCTOR_H
