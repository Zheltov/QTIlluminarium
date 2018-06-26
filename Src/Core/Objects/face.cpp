#include "face.h"

Face::Face(Obj *_obj, int index1, int index2, int index3, Material *_material) : material(_material), obj(_obj)
{
    VertexIndexes[0] = index1;
    VertexIndexes[1] = index2;
    VertexIndexes[2] = index3;
}
