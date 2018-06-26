#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include "obj.h"
#include "Core/Light/light.h"


class Scene
{
public:
    vector<Obj*> Objects;
    vector<Light*> Lights;

    Scene();
    virtual ~Scene();

};

#endif // SCENE_H
