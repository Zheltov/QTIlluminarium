#include "scenecreatordubrovniksponza.h"

#include "IO/Imports/loader3ds.h"
#include "Core/Material/diffusematerial.h"
#include "Core/Light/rectanglelight.h"
#include "Core/Light/rectangleparallelstreamlight.h"


SceneCreatorDubrovnikSponza::SceneCreatorDubrovnikSponza()
{
}

Scene *SceneCreatorDubrovnikSponza::CreateScene()
{
    Material *material = new Material( new DiffuseMaterial( Spectrum(0.5) ) );

    Loader3ds loader;

    Scene *scene = loader.Load( "Content/Scenes/sponza.3ds", material, 1 );

    // ADD LIGHT
    Material *lightMaterial = new Material();
    scene->Lights.push_back( new RectangleParallelStreamLight( Point3D( 0, 0, 15 ), 21, 4.9, Spectrum( 1 ), *lightMaterial, Vector3D(0.25, 0.25, -1, true) ) );

    // MATERIALS

    // Арки
    Material *arcsMaterial = new Material( new DiffuseMaterial( Spectrum(0.9, 0.9, 0.9) ) );
    this->setMaterial( scene->Objects[2], arcsMaterial );
    this->setMaterial( scene->Objects[3], arcsMaterial );
    this->setMaterial( scene->Objects[12], arcsMaterial );
    this->setMaterial( scene->Objects[18], arcsMaterial );
    this->setMaterial( scene->Objects[21], arcsMaterial );
    this->setMaterial( scene->Objects[25], arcsMaterial );
    this->setMaterial( scene->Objects[30], arcsMaterial );
    this->setMaterial( scene->Objects[31], arcsMaterial );

    // Потолок
    Material *ceilingMaterial = new Material( new DiffuseMaterial( Spectrum(0.75, 0.75, 0.75) ) );
    this->setMaterial( scene->Objects[24], ceilingMaterial );

    // Двери
    Material *doorsMaterial = new Material( new DiffuseMaterial( Spectrum(0.75, 0.5, 0.25) ) );
    this->setMaterial( scene->Objects[34], doorsMaterial );

    // Мелкие окошки наверху (holes)
    Material *holesMaterial = new Material( new DiffuseMaterial( Spectrum(0.7, 0.7, 0.7) ) );
    this->setMaterial( scene->Objects[19], holesMaterial );
    this->setMaterial( scene->Objects[23], holesMaterial );
    this->setMaterial( scene->Objects[33], holesMaterial );


    // Колонны
    Material *pilarMaterial = new Material( new DiffuseMaterial( Spectrum(0.85, 0.85, 0.85) ) );
    this->setMaterial( scene->Objects[6], pilarMaterial );
    this->setMaterial( scene->Objects[7], pilarMaterial );
    this->setMaterial( scene->Objects[10], pilarMaterial );
    this->setMaterial( scene->Objects[11], pilarMaterial );
    this->setMaterial( scene->Objects[15], pilarMaterial );

    // all objects (части колонн)
    this->setMaterial( scene->Objects[4], pilarMaterial );
    this->setMaterial( scene->Objects[5], pilarMaterial );
    this->setMaterial( scene->Objects[8], pilarMaterial );
    this->setMaterial( scene->Objects[9], pilarMaterial );
    this->setMaterial( scene->Objects[13], pilarMaterial );
    this->setMaterial( scene->Objects[14], pilarMaterial );
    this->setMaterial( scene->Objects[16], pilarMaterial );
    this->setMaterial( scene->Objects[26], pilarMaterial );
    this->setMaterial( scene->Objects[27], pilarMaterial );
    this->setMaterial( scene->Objects[28], pilarMaterial );
    this->setMaterial( scene->Objects[29], pilarMaterial );

    // parapet
    this->setMaterial( scene->Objects[22], pilarMaterial );

    // Relief
    Material *relifMaterial = new Material( new DiffuseMaterial( Spectrum(0.7, 0.0, 0.0) ) );
    this->setMaterial( scene->Objects[17], relifMaterial );

    // Walls
    Material *wallMaterial = new Material( new DiffuseMaterial( Spectrum(0.95, 0.9, 0.8) ) );
    this->setMaterial( scene->Objects[32], wallMaterial );

    // Floor
    // Material *floorMaterial = new Material( new DiffuseMaterial( Spectrum(0.8, 0.7, 0.6) ), new MirrorMaterial( Spectrum(0.2, 0.2, 0.2) ) );
    Material *floorMaterial = new Material( new DiffuseMaterial( Spectrum(0.8, 0.7, 0.6) ) );
    for( unsigned int i = 0; i < scene->Objects[32]->Faces.size(); i++ )
    {
        Face *face = scene->Objects[32]->Faces[i];

        if ( face->normal.Z > 0.9 )
            face->material = floorMaterial;
    }

    return scene;
}

void SceneCreatorDubrovnikSponza::SetDefaultCameraParameters(Camera &camera)
{
    camera.setPosition( Point3D(10.5, 0, 2) );
    camera.setTarget( Point3D(0, 0, 3) );
}
