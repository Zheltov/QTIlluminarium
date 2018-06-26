#include "mainwindow.h"
#include "ui_mainwindow.h"



#include "IO/Imports/loader3ds.h"
#include "Debug/raydebugcollection.h"
#include "Core/Light/light.h"
#include "Core/Light/rectanglelight.h"
#include "Core/RayTracer/raytracer.h"

#include "Core/Material/material.h"
#include "Core/Material/diffusematerial.h"
#include "Core/Render/GI/globalillumination.h"
#include "Core/Render/GI/localestimate.h"
#include "Core/Render/GI/localestimatecompressedmesh.h"
#include "Core/Render/GI/localestimategeomcompressed.h"
#include "Core/Render/GI/LocalEstimate/renderpointscompressorgeommesh.h"
#include "IO/SceneConstructor/cornellboxsceneconstructor.h"
#include "IO/SceneConstructor/scenecreatordubrovniksponza.h"
#include "IO/SceneConstructor/scenecreatorconferenceroom.h"
#include "Core/func.h"


#include "renderviewframeimagewindow.h"
#include "renderviewdialog.h"
#include "logdialog.h"
#include "sceneviewdialog.h"

// Spherical Harmonics
#include "Libs/SphericalHarmonics/sphericalharmonics.h"
#include "Libs/Mesh/meshtransform.h"


#include <embree2/rtcore.h>
#include <embree2/rtcore_scene.h>
#include <embree2/rtcore_ray.h>

#include <iostream>
#include <memory>
#include <memory.h>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    qRegisterMetaType<std::string>();

    this->renderer = NULL;
    this->camera = this->ui->SceneGLWidget;

    //CornellBoxSceneConstructor sceneConstructor;
    SceneCreatorDubrovnikSponza sceneConstructor;
    //SceneCreatorConferenceRoom sceneConstructor;
    this->scene = sceneConstructor.CreateScene();

    this->ui->SceneGLWidget->scene = this->scene;

    sceneConstructor.SetDefaultCameraParameters( *this->camera );

    for( uint i = 0; i < this->scene->Objects.size(); i++ )
    {
        Obj* o = this->scene->Objects[i];
        for( uint j = 0; j < o->Faces.size(); j++ )
        {
            Face *f = o->Faces[j];

            Point3D center = ( o->Vertexes[f->VertexIndexes[0]] + o->Vertexes[f->VertexIndexes[1]] + o->Vertexes[f->VertexIndexes[2]] ) / 3;

            //RayDebugCollection::Rays.push_back( new Ray( center, center + f->normal / 3 ) );


        }
    }

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionRender_triggered()
{

    LogDialog* logDlg = new LogDialog(this);
    connect(logDlg, SIGNAL(finished(int)), logDlg, SLOT(deleteLater()));
    logDlg->show();

    RayTracer *rayTracer = new RayTracer( *this->scene );


    /*
    RenderFrameCompressorMesh *compressor = new RenderFrameCompressorMesh();
    GlobalIllumination *gi = new LocalEstimateCompressedMesh( *rayTracer, *logDlg, compressor );
    */

    GlobalIllumination *gi = new LocalEstimate( *rayTracer, *logDlg );


    this->renderer = new Render( *rayTracer, *gi, *logDlg );

    this->renderFrame = renderer->GetRenderFrame( *this->camera );

    for( uint i = 0; i < this->scene->Objects.size(); i++ )
    {
        Obj* o = this->scene->Objects[i];
        logDlg->AddMessage( func::to_string(i) + " " + o->Name );
    }

    //gi->Render( *renderFrame );

    renderer->RenderDirectLight( *renderFrame );
    renderer->RenderGlobalIllumination( *renderFrame );

    /*
    renderFrame->FinalGathering();

    RenderViewFrameImageWindow *imageViewWindow = new RenderViewFrameImageWindow( this );
    imageViewWindow->setRenderViewFrame( renderFrame );
    connect(imageViewWindow, SIGNAL(finished(int)), imageViewWindow, SLOT(deleteLater()));
    imageViewWindow->show();


    RenderViewDialog* dlg = new RenderViewDialog(this);
    dlg->setRenderViewFrame( *renderFrame );
    connect(dlg, SIGNAL(finished(int)), dlg, SLOT(deleteLater()));
    dlg->show();
    */

    /*
    delete renderFrame;
    delete renderer;
    delete rayTracer;
    delete gi;
    delete compressor;
*/
    //auto sp = std::make_shared<int>(42);

    //shared_ptr<int> p(new int(5));
    //boost::shared_ptr<int> q( new int(5) );

    //(&q) = 10;
    //boost::weak_ptr<int> p = boost::weak_ptr<int>(42);

    //Render r()

}

void MainWindow::on_actionTraceCameraRays_triggered()
{
    RayTracer *rayTracer = new RayTracer( *this->scene );

    QSize sSize = this->size();
    int width = sSize.width();
    int height = sSize.height();



    for( int x = 0; x < width; x = x + 50)
    {
        for( int y = 0; y < height; y = y + 50 )
        {
            Vector3D direction = this->camera->GetTracingDirection(x, y );
            //Vector3D direction = this->ui->SceneGLWidget->GetTracingDirection(x, y);

            //Point3D pos = this->camera->getPosition() + direction * 10;

            Intersection *intersection = rayTracer->Intersect(this->camera->getPosition(), direction);
            if ( intersection != NULL )
            {
                RayDebugCollection::Rays.push_back( new Ray( this->camera->getPosition(), intersection->getPosition() ) );
            }

            delete intersection;
        }
    }

    delete rayTracer;
}

void MainWindow::on_actionStopRender_triggered()
{
    if ( this->renderer == NULL )
        return;

    this->renderer->StopRender();

    this->renderFrame->FinalGathering();

    RenderViewFrameImageWindow *imageViewWindow = new RenderViewFrameImageWindow( this );
    imageViewWindow->setRenderViewFrame( renderFrame );
    connect(imageViewWindow, SIGNAL(finished(int)), imageViewWindow, SLOT(deleteLater()));
    imageViewWindow->show();
}

void MainWindow::on_actionSH_Test_triggered()
{
    // SphericalHarmonics *sh = new SphericalHarmonics();

    Loader3ds loader;

    Material *material = new Material( new DiffuseMaterial( Spectrum(0.5) ) );
    Scene *scene = loader.Load( "d:/Qt/Illuminarium/Illuminarium/Content/Scenes/cube.3ds", material, 1 );
    RayTracer *rayTracer = new RayTracer( *scene );

    SceneViewDialog* sceneViewDialog = new SceneViewDialog(this);
    connect(sceneViewDialog, SIGNAL(finished(int)), sceneViewDialog, SLOT(deleteLater()));

    //SphericalHarmonics::Legzo( 16 );

    //SphericalHarmonics::Schmidt(0.2, 8);

    vector<double> &phis = MeshTransform::GetUniformPhi( 16 );
    vector<double> &thetas = MeshTransform::GetUniformTheta( 16 );

    DoubleArray &r = MeshTransform::MeshToAngleFunction( *rayTracer, Point3D(0, 0, 0), thetas, phis );
    //SphericalHarmonics::AngleFuncToSHCoefficients(r, thetas, phis, 8);


    sceneViewDialog->setAF(r, thetas, phis);

    sceneViewDialog->setScene( *scene );
    sceneViewDialog->show();

    delete rayTracer;

    return;
}
