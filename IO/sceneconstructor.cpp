#include "sceneconstructor.h"

void SceneConstructor::setMaterial(Obj *o, Material *m)
{
    for( unsigned int i = 0; i < o->Faces.size(); i++ )
        o->Faces[i]->material = m;
}
