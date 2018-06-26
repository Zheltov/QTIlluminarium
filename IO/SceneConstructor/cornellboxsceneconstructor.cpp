#include "cornellboxsceneconstructor.h"
#include "IO/Imports/loader3ds.h"
#include "Core/Material/diffusematerial.h"
#include "Core/Light/rectanglelight.h"

CornellBoxSceneConstructor::CornellBoxSceneConstructor()
{
}

Scene *CornellBoxSceneConstructor::CreateScene()
{
    Material *material = new Material( new DiffuseMaterial( Spectrum(0.9, 0.9, 0.9) ) );

    Loader3ds loader;

    Scene *scene = loader.Load( "Content/Scenes/cornellbox.3ds", material, 1 );

    // ADD LIGHT
    Material *lightMaterial = new Material();
    scene->Lights.push_back( new RectangleLight( Point3D( 0, 0, 4.99 ), 1, 1, Spectrum( 1 ), *lightMaterial, 256 ) );

    Obj &o = *scene->Objects[0];
    o.Faces.erase(o.Faces.begin() + 4 );
    o.Faces.erase(o.Faces.begin() + 4 );

    // FLOOR
    Material *floor = new Material( new DiffuseMaterial( Spectrum(0.54, 0.54, 0.54) ) );
    o.Faces[0]->material = floor;
    o.Faces[1]->material = floor;

    // CEILING
    Material *ceiling = new Material( new DiffuseMaterial( Spectrum(0.84, 0.84, 0.84) ) );
    o.Faces[2]->material = ceiling;
    o.Faces[3]->material = ceiling;

    // RIGHT WALL
    Material *rightWall = new Material( new DiffuseMaterial( Spectrum(1.0, 0.0, 0.0) ) );
    o.Faces[4]->material = rightWall;
    o.Faces[5]->material = rightWall;

    // BACK WALL
    Material *backWall = new Material( new DiffuseMaterial( Spectrum(0.84, 0.84, 0.84) ) );
    o.Faces[6]->material = backWall;
    o.Faces[7]->material = backWall;

    // LEFT WALL
    Material *leftWall = new Material( new DiffuseMaterial( Spectrum(0.0, 1.0, 0.0) ) );
    o.Faces[8]->material = leftWall;
    o.Faces[9]->material = leftWall;

    // BOX 1
    Material *box1 = new Material( new MirrorMaterial( Spectrum( 0.95, 0.95, 0.95 ) ) );
    Obj *obj = scene->Objects[1];
    for( unsigned int i = 0; i < obj->Faces.size(); i++ )
        obj->Faces[i]->material = box1;

    // BOX 2
    Material *box2 = new Material( new MirrorMaterial( Spectrum( 0.95, 0.95, 0.95 ) ) );
    obj = scene->Objects[2];
    for( unsigned int i = 0; i < obj->Faces.size(); i++ )
        obj->Faces[i]->material = box2;

    return scene;
}

void CornellBoxSceneConstructor::SetDefaultCameraParameters(Camera &camera)
{
    camera.setPosition( Point3D(0, -5, 2.5) );
    camera.setTarget( Point3D(0, 0, 2.5) );
}
