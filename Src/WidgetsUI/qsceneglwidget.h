#ifndef QSCENEGLWIDGET_H
#define QSCENEGLWIDGET_H

#include <QWidget>
#include <QGLWidget>
#include <QMouseEvent>
#include "Core/Objects/scene.h"
#include "Core/Camera/camera.h"

#include "boost/multi_array.hpp"
#include <vector>

using namespace std;



namespace Ui {
class QSceneGLWidget;
}

class QSceneGLWidget : public QGLWidget, public Camera
{
    Q_OBJECT
public:
    explicit QSceneGLWidget(QWidget *parent = 0);
    ~QSceneGLWidget();

    virtual int getClientWidth() const;
    virtual int getClientHeight() const;

    boost::multi_array<double, 2> *AF;
    vector<double> *AFTheta;
    vector<double> *AFPhi;

    virtual const Vector3D GetTracingDirection( Coordinate pixel_x_coord, Coordinate pixel_y_coord ) const;

protected:
    void initializeGL();
    void resizeGL(int nWidth, int nHeight);
    void paintGL();

    void mousePressEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent* event);
    void wheelEvent(QWheelEvent *);

    /* Camera methods */
    virtual void recalcPosition();
    virtual void recalcAngle();

private:
    int oldX;
    int oldY;
    bool mouseRightButtonPressed;

    void reloadView();


    Ui::QSceneGLWidget *ui;
};

#endif // QSCENEGLWIDGET_H
