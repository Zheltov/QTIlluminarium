#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "Core/Objects/scene.h"
#include "Core/Camera/camera.h"
#include "Core/Render/render.h"

Q_DECLARE_METATYPE(std::string)

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    Scene* scene;
    Camera* camera;
    Render* renderer;
    RenderViewFrame *renderFrame;

    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:


private:
    Ui::MainWindow *ui;

private slots:
    void on_actionRender_triggered();
    void on_actionTraceCameraRays_triggered();
    void on_actionStopRender_triggered();
    void on_actionSH_Test_triggered();
};

#endif // MAINWINDOW_H
