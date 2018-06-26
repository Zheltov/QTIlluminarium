#ifndef FACE_H
#define FACE_H

#include "Core/types.h"
#include "Core/Material/material.h"

// Forward declaration
class Obj;

class Face
{
public:

    int VertexIndexes[3];
    Vector3D normal;
    Material *material;
    Obj* obj;

    Face( Obj* _obj, int index1, int index2, int index3, Material *_material );


};

#endif // FACE_H
