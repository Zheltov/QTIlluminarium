#ifndef RAYTRACER_H
#define RAYTRACER_H

#include <embree2/rtcore.h>
#include <embree2/rtcore_scene.h>
#include <map>

#include "Core/types.h"
#include "Core/Objects/intersection.h"
#include "Core/Objects/scene.h"
#include "Core/Light/light.h"

using namespace std;

struct EmbreeVertex   { float x, y, z, r; };
struct EmbreeTriangle { int v0, v1, v2; };

class RayTracer
{
private:
    __RTCScene* RTCScene;

    map<unsigned int, Light*> lightGeomIndexes;


    void CheckLastError();
    void Init();
    unsigned int AddObject(Obj* obj);

public:
    Scene &scene;

    RayTracer( Scene &sc );
    virtual ~RayTracer();


    Intersection* Intersect( const Point3D &from, const Vector3D &dir, Coordinate near = 0, Coordinate far = 9999999 );
    bool Occluded(const Point3D &from, const Vector3D &dir, Coordinate near = 0, Coordinate far = 9999999 );
};

#endif // RAYTRACER_H
