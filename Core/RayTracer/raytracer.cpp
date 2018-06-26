#include <embree2/rtcore.h>
#include <embree2/rtcore_scene.h>
#include <embree2/rtcore_ray.h>

#include "raytracer.h"
#include "Core/Light/light.h"

void RayTracer::CheckLastError()
{
    RTCError error = rtcGetError();

    switch( error )
    {
        case RTC_UNKNOWN_ERROR:
            throw new string("An unknown error has occured.");
            break;
        case  RTC_INVALID_ARGUMENT:
            throw new string("An invalid argument is specified");
            break;
        case  RTC_INVALID_OPERATION:
            throw new string("The operation is not allowed for the specified object.");
            break;
        case  RTC_OUT_OF_MEMORY:
            throw new string("There is not enough memory left to execute the command.");
            break;
        case  RTC_UNSUPPORTED_CPU:
            throw new string("The CPU is not supported as it does not support SSE2.");
            break;
    }
}

RayTracer::RayTracer(Scene &sc ) : scene( sc )
{
    //this->scene = sc;

    rtcInit();
    this->CheckLastError();

    this->Init();
}

RayTracer::~RayTracer()
{
    rtcDeleteScene( this->RTCScene );
    rtcExit();
}

void RayTracer::Init()
{
    this->RTCScene = rtcNewScene( RTC_SCENE_STATIC | RTC_SCENE_COHERENT | RTC_SCENE_INCOHERENT | RTC_SCENE_ROBUST, RTC_INTERSECT1 | RTC_INTERSECT4 );
    this->CheckLastError();

    for( unsigned int i = 0; i < this->scene.Objects.size(); i++ )
    {
        Obj *obj = this->scene.Objects[i];
        this->AddObject( obj );
    }

    for( unsigned int i = 0; i < this->scene.Lights.size(); i++ )
    {
        Light *l = this->scene.Lights[i];
        Obj *obj = dynamic_cast<Obj*>(l);
        if ( obj != NULL )
        {
            unsigned int index = this->AddObject( obj );
            lightGeomIndexes[index] = l;
        }
    }

    rtcCommit( this->RTCScene );
    this->CheckLastError();
}

unsigned int RayTracer::AddObject(Obj *obj)
{
    int facesCount = obj->Faces.size();
    int vertexesCount = obj->Vertexes.size();

    unsigned int geomId = rtcNewTriangleMesh ( this->RTCScene, RTC_GEOMETRY_STATIC, facesCount, vertexesCount );

    EmbreeVertex* vertexes = (EmbreeVertex*)rtcMapBuffer( this->RTCScene, geomId, RTC_VERTEX_BUFFER );
    for( int j = 0; j < vertexesCount; j++ )
    {
        vertexes->x = obj->Vertexes[j].X;
        vertexes->y = obj->Vertexes[j].Y;
        vertexes->z = obj->Vertexes[j].Z;
        vertexes++;
    }
    rtcUnmapBuffer( this->RTCScene, geomId, RTC_VERTEX_BUFFER );

    EmbreeTriangle* triangles = (EmbreeTriangle*) rtcMapBuffer( this->RTCScene, geomId, RTC_INDEX_BUFFER );
    for( int j = 0; j < facesCount; j++ )
    {
        triangles->v0 = obj->Faces[j]->VertexIndexes[0];
        triangles->v1 = obj->Faces[j]->VertexIndexes[1];
        triangles->v2 = obj->Faces[j]->VertexIndexes[2];
        triangles++;
    }
    rtcUnmapBuffer( this->RTCScene, geomId, RTC_INDEX_BUFFER );

    return geomId;
}

Intersection *RayTracer::Intersect(const Point3D &from, const Vector3D &dir, Coordinate near, Coordinate far)
{
    RTCRay ray;
    ray.org[0] = from.X;
    ray.org[1] = from.Y;
    ray.org[2] = from.Z;
    ray.dir[0] = dir.X;
    ray.dir[1] = dir.Y;
    ray.dir[2] = dir.Z;
    ray.tnear = near;
    ray.tfar = far;
    ray.geomID = RTC_INVALID_GEOMETRY_ID;
    ray.primID = RTC_INVALID_GEOMETRY_ID;
    ray.mask = -1;
    ray.time = 0;

    rtcIntersect( this->RTCScene, ray );

    if ( ray.geomID != RTC_INVALID_GEOMETRY_ID )
    {
        float distance = ray.tfar;

        Vector3D delta = dir * distance;
        Point3D position = from + delta;

        Obj* obj;
        if ( ray.geomID < this->scene.Objects.size() )
            obj = this->scene.Objects[ray.geomID];
        else
        {
            Light *light = this->lightGeomIndexes[ray.geomID];
            obj = dynamic_cast<Obj*>(light);
        }

        Face* face = obj->Faces[ray.primID];

        Intersection *result = new Intersection( position, *obj, *face );

        return result;
    }
    else
        return NULL;

}

bool RayTracer::Occluded(const Point3D &from, const Vector3D &dir, Coordinate near, Coordinate far)
{
    RTCRay ray;
    ray.org[0] = from.X;
    ray.org[1] = from.Y;
    ray.org[2] = from.Z;
    ray.dir[0] = dir.X;
    ray.dir[1] = dir.Y;
    ray.dir[2] = dir.Z;
    ray.tnear = near;
    ray.tfar = far;
    ray.geomID = RTC_INVALID_GEOMETRY_ID;
    ray.primID = RTC_INVALID_GEOMETRY_ID;
    ray.mask = -1;
    ray.time = 0;

    rtcOccluded( this->RTCScene, ray );

    return ray.geomID == 0;
}
