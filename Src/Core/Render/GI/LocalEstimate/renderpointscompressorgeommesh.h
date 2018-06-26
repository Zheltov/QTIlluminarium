#ifndef RENDERPOINTSCOMPRESSORGEOMMESH_H
#define RENDERPOINTSCOMPRESSORGEOMMESH_H

#include "Core/Render/renderframe.h"

class RenderPointsCompressorGeomMesh
{
public:
    RenderPointsCompressorGeomMesh();

    vector<RenderPoint> GenerateCalculatedStructure( RenderFrame &frame );
};

#endif // RENDERPOINTSCOMPRESSORGEOMMESH_H
