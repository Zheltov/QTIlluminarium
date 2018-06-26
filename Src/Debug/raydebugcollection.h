#ifndef RAYDEBUGCOLLECTION_H
#define RAYDEBUGCOLLECTION_H

#include <vector>

#include "Core/Objects/ray.h"

using namespace std;

class RayDebugCollection
{
public:
    static vector<Ray *> Rays;
};

#endif // RAYDEBUGCOLLECTION_H
