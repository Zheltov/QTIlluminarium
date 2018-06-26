#include "scenecreatorconferenceroom.h"

#include "IO/Imports/loader3ds.h"
#include "Core/Material/diffusematerial.h"
#include "Core/Light/rectanglelight.h"


SceneCreatorConferenceRoom::SceneCreatorConferenceRoom()
{
}


Scene *SceneCreatorConferenceRoom::CreateScene()
{
    Material *material = new Material( new DiffuseMaterial( Spectrum(0.5) ) );

    Loader3ds loader;

    Scene *scene = loader.Load( "Content/Scenes/conference.3ds", material, 0.0254 );

    // ADD LIGHT
    Material *lightMaterial = new Material();
    scene->Lights.push_back( new RectangleLight( Point3D( 5, 0, 15 ), 14, 2.5, Spectrum( 1 ), *lightMaterial, 16 ) );

    // Materials

    // стены
    this->setMaterial( scene->Objects[3], new Material( new DiffuseMaterial( Spectrum(0.9, 0.0, 0.0) ) ) );
    this->setMaterial( scene->Objects[3], new Material( new DiffuseMaterial( Spectrum(0.0, 0.9, 0.0) ) ) );

    // floor
    this->setMaterial( scene->Objects[3], new Material( new DiffuseMaterial( Spectrum(0.5, 0.25, 0.25) ) ) );

    // огнетушители
    this->setMaterial( scene->Objects[21], new Material( new DiffuseMaterial( Spectrum(0.9, 0.0, 0.0) ) ) );
    this->setMaterial( scene->Objects[22], new Material( new DiffuseMaterial( Spectrum(0.9, 0.0, 0.0) ) ) );
    this->setMaterial( scene->Objects[23], new Material( new DiffuseMaterial( Spectrum(0.9, 0.0, 0.0) ) ) );

    // столешница
    this->setMaterial( scene->Objects[25], new Material( new DiffuseMaterial( Spectrum(0.5, 0.25, 0.0) ) ) );

    // стул
    this->setMaterial( scene->Objects[35], new Material( new DiffuseMaterial( Spectrum(0.95, 0.8, 0.7) ) ) );



    return scene;
}

void SceneCreatorConferenceRoom::SetDefaultCameraParameters(Camera &camera)
{
    camera.setPosition( Point3D(12, 2, 2) );
    camera.setTarget( Point3D(0, 0, 3) );
}



