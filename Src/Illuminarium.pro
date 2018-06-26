#-------------------------------------------------
#
# Project created by QtCreator 2015-02-06T15:29:35
#
#-------------------------------------------------

QT       += core gui opengl

#QMAKE_CXXFLAGS_DEBUG += -pg
#QMAKE_LFLAGS_DEBUG += -pg

QMAKE_CXXFLAGS_WARN_ON += -Wno-reorder

CONFIG+=build_all


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Illuminarium
TEMPLATE = app

SOURCES += main.cpp\
    mainwindow.cpp \
    WidgetsUI/qsceneglwidget.cpp \
    IO/Imports/c3ds/3DCamera.cpp \
    IO/Imports/c3ds/3DFace.cpp \
    IO/Imports/c3ds/3DModel.cpp \
    IO/Imports/c3ds/3DObject.cpp \
    IO/Imports/c3ds/3dsFileFormat.cpp \
    IO/Imports/c3ds/3dsFileLoader.cpp \
    IO/Imports/c3ds/matrix.cpp \
    IO/Imports/c3ds/vector.cpp \
    IO/Imports/loader3ds.cpp \
    Core/Objects/face.cpp \
    Core/Objects/obj.cpp \
    Core/Objects/scene.cpp \
    Core/RayTracer/raytracer.cpp \
    Core/Camera/camera.cpp \
    Core/constants.cpp \
    Debug/raydebugcollection.cpp \
    Core/types.cpp \
    Core/Objects/intersection.cpp \
    Core/Render/render.cpp \
    Core/Render/renderpoint.cpp \
    Core/Render/renderframe.cpp \
    Core/Light/light.cpp \
    Core/Light/rectanglelight.cpp \
    Core/Material/material.cpp \
    Core/Render/renderviewframe.cpp \
    Core/Material/diffusematerial.cpp \
    Core/math3d.cpp \
    Core/Material/reflectancematerial.cpp \
    logdialog.cpp \
    Core/func.cpp \
    Core/Material/mirrormaterial.cpp \
    Core/Render/renderscreenpoint.cpp \
    Core/Render/GI/localestimate.cpp \
    Core/Render/GI/LocalEstimate/localestimatecalculator.cpp \
    Core/Render/GI/LocalEstimate/renderpointlocalestimate.cpp \
    WidgetsUI/renderviewframeimagewidget.cpp \
    renderviewframeimagewindow.cpp \
    Core/Render/GI/LocalEstimate/facelocalestimate.cpp \
    Core/Render/GI/LocalEstimate/renderpointscompressorgeommesh.cpp \
    Core/Render/GI/LocalEstimate/renderframecompressed.cpp \
    Core/Render/GI/LocalEstimate/renderframecompressormesh.cpp \
    Core/Render/GI/LocalEstimate/vertexlocalestimate.cpp \
    Core/Render/GI/LocalEstimate/renderframelocalestimate.cpp \
    IO/sceneconstructor.cpp \
    IO/SceneConstructor/cornellboxsceneconstructor.cpp \
    IO/SceneConstructor/scenecreatordubrovniksponza.cpp \
    Core/Render/GI/localestimatecompressedmesh.cpp \
    Core/Render/GI/globalillumination.cpp \
    IO/SceneConstructor/scenecreatorconferenceroom.cpp \
    Core/Light/rectangleparallelstreamlight.cpp \
    Libs/SphericalHarmonics/sphericalharmonics.cpp \
    Libs/Mesh/meshtransform.cpp \
    sceneviewdialog.cpp

HEADERS  += mainwindow.h \
    WidgetsUI/qsceneglwidget.h \
    IO/Imports/c3ds/3DCamera.h \
    IO/Imports/c3ds/3DFace.h \
    IO/Imports/c3ds/3DModel.h \
    IO/Imports/c3ds/3DObject.h \
    IO/Imports/c3ds/3dsFileFormat.h \
    IO/Imports/c3ds/3dsFileLoader.h \
    IO/Imports/c3ds/matrix.h \
    IO/Imports/c3ds/vector.h \
    IO/Imports/loader3ds.h \
    Core/Objects/face.h \
    Core/Objects/obj.h \
    Core/Objects/scene.h \
    Core/RayTracer/raytracer.h \
    Core/Camera/camera.h \
    Core/constants.h \
    Debug/raydebugcollection.h \
    Core/types.h \
    Core/Objects/intersection.h \
    Core/Render/render.h \
    Core/Render/renderpoint.h \
    Core/Render/renderframe.h \
    Core/Light/light.h \
    Core/Light/rectanglelight.h \
    Core/Material/material.h \
    Core/Render/renderviewframe.h \
    Core/Material/diffusematerial.h \
    Core/math3d.h \
    Core/Material/reflectancematerial.h \
    logdialog.h \
    Core/Log.h \
    Core/func.h \
    Core/Material/mirrormaterial.h \
    Core/Render/renderscreenpoint.h \
    Core/Render/GI/localestimate.h \
    Core/Render/GI/LocalEstimate/localestimatecalculator.h \
    Core/Render/GI/LocalEstimate/renderpointlocalestimate.h \
    WidgetsUI/renderviewframeimagewidget.h \
    renderviewframeimagewindow.h \
    Core/Render/GI/LocalEstimate/facelocalestimate.h \
    Core/Render/GI/LocalEstimate/renderframecompressed.h \
    Core/Render/GI/LocalEstimate/renderframecompressormesh.h \
    Core/Render/GI/LocalEstimate/vertexlocalestimate.h \
    Core/Render/GI/LocalEstimate/renderframelocalestimate.h \
    IO/sceneconstructor.h \
    IO/SceneConstructor/cornellboxsceneconstructor.h \
    IO/SceneConstructor/scenecreatordubrovniksponza.h \
    Core/Render/GI/localestimatecompressedmesh.h \
    Core/Render/GI/globalillumination.h \
    IO/SceneConstructor/scenecreatorconferenceroom.h \
    Core/Light/rectangleparallelstreamlight.h \
    Libs/SphericalHarmonics/sphericalharmonics.h \
    Libs/Mesh/meshtransform.h \
    sceneviewdialog.h

FORMS    += mainwindow.ui \
    WidgetsUI/qsceneglwidget.ui \
    logdialog.ui \
    WidgetsUI/renderviewframeimagewidget.ui \
    renderviewframeimagewindow.ui \
    sceneviewdialog.ui



LIBS += -L$$PWD/../../Libs/Embree/lib/win32/ -lembree

INCLUDEPATH += $$PWD/../../Libs/Embree/include
DEPENDPATH += $$PWD/../../Libs/Embree/include

#LIBS += -L$$PWD/../../Libs/boost/stage/lib/ -lboost_atomic-mgw48-mt-1_57
#LIBS += -L$$PWD/../../Libs/boost/stage/lib/ -lboost_iostreams-mgw48-mt-1_57

INCLUDEPATH += $$PWD/../../Libs/boost
DEPENDPATH += $$PWD/../../Libs/boost

#INCLUDEPATH += $$PWD/../../Libs/alglib/include
#DEPENDPATH += $$PWD/../../Libs/alglib/include
