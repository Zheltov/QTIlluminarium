#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>
#include <typeinfo>

#include "qsceneglwidget.h"
#include "ui_qsceneglwidget.h"

#include "Core/constants.h"
#include "Debug/raydebugcollection.h"


QSceneGLWidget::QSceneGLWidget(QWidget *parent) :
    QGLWidget(parent),
    ui(new Ui::QSceneGLWidget)
{
    ui->setupUi(this);

    this->AF = NULL;

    this->setMouseTracking(true);
    this->mouseRightButtonPressed = false;
}

QSceneGLWidget::~QSceneGLWidget()
{
    delete ui;
}

int QSceneGLWidget::getClientWidth() const
{
    return this->size().width();
}

int QSceneGLWidget::getClientHeight() const
{
    return this->size().height();
}

const Vector3D QSceneGLWidget::GetTracingDirection(Coordinate pixel_x_coord, Coordinate pixel_y_coord) const
{
    GLint viewport[4];
    GLdouble modelview[16];
    GLdouble projection[16];
    GLfloat winX, winY;
    GLdouble posX1, posY1, posZ1;
    GLdouble posX2, posY2, posZ2;

    glGetDoublev( GL_MODELVIEW_MATRIX, modelview );
    glGetDoublev( GL_PROJECTION_MATRIX, projection );
    glGetIntegerv( GL_VIEWPORT, viewport );

    winX = pixel_x_coord;
    winY = this->getClientHeight() - pixel_y_coord;

    gluUnProject( winX, winY, 0, modelview, projection, viewport, &posX1, &posY1, &posZ1);
    gluUnProject( winX, winY, 1, modelview, projection, viewport, &posX2, &posY2, &posZ2);

    return Vector3D( posX2 - posX1, posY2 - posY1, posZ2 - posZ1, true );
}

void QSceneGLWidget::initializeGL()
{
   qglClearColor(Qt::white);
   glEnable(GL_DEPTH_TEST);
   glShadeModel(GL_FLAT);
   glEnable(GL_CULL_FACE);
   glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
}

void QSceneGLWidget::resizeGL(int nWidth, int nHeight)
{
    this->reloadView();
}

void QSceneGLWidget::paintGL() // рисование
{
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    if ( this->scene == NULL )
        return;

    Scene* scene = this->scene;
    for ( unsigned i = 0; i < scene->Objects.size(); i++ )
    {
        Obj* obj = scene->Objects[i];
        for ( unsigned j = 0; j < obj->Faces.size(); j++ )
        {
            Face* face = obj->Faces[j];

            glBegin( GL_TRIANGLES );

            for ( int k = 0; k < 3; k++ )
            {
                Point3D p = obj->Vertexes[face->VertexIndexes[k]];
                glColor3f( 1, 1, 1 );
                glVertex3f( p.X, p.Y, p.Z );
            }

            glEnd();

        }
    }

    for ( unsigned i = 0; i < scene->Lights.size(); i++ )
    {
        Light *l = scene->Lights[i];
        Obj *obj = dynamic_cast<Obj*>(l);
        if ( obj != NULL )
        {
            for ( unsigned j = 0; j < obj->Faces.size(); j++ )
            {
                Face* face = obj->Faces[j];

                glBegin( GL_TRIANGLES );

                for ( int k = 0; k < 3; k++ )
                {
                    Point3D p = obj->Vertexes[face->VertexIndexes[k]];
                    glColor3f( 1, 1, 0 );
                    glVertex3f( p.X, p.Y, p.Z );
                }

                glEnd();
            }
        }
    }

    for ( unsigned i = 0; i < RayDebugCollection::Rays.size(); i++ )
    {
        Ray* ray = RayDebugCollection::Rays[i];

        glBegin( GL_LINES );
        glColor3f( 1, 0, 0 );
        glVertex3f( ray->from.X, ray->from.Y, ray->from.Z );
        glVertex3f( ray->to.X, ray->to.Y, ray->to.Z );
        glEnd();
    }



    // AF
    if ( this->AF != NULL )
    {

        boost::multi_array<double, 2> &af = *this->AF;
        vector<double> &theta = *this->AFTheta;
        vector<double> &phi = *this->AFPhi;
        for( unsigned int it = 0; it < this->AFTheta->size() - 1; it++ )
            for( unsigned int ip = 0; ip < this->AFPhi->size() - 1; ip++ )
            {
                Vector3D direction1 = Vector3D( M_PI_2 - theta[it], phi[ip] ) * af[it][ip];
                Vector3D direction2 = Vector3D( M_PI_2 - theta[it+1], phi[ip] ) * af[it+1][ip];
                Vector3D direction3 = Vector3D( M_PI_2 - theta[it+1], phi[ip+1] ) * af[it+1][ip+1];
                Vector3D direction4 = Vector3D( M_PI_2 - theta[it], phi[ip+1] ) * af[it][ip+1];

                glBegin( GL_QUADS );
                glColor3f( 0, 1, 0 );
                glVertex3f( direction1.X, direction1.Y, direction1.Z );
                glColor3f( 0, 1, 0 );
                glVertex3f( direction2.X, direction2.Y, direction2.Z );
                glColor3f( 0, 1, 0 );
                glVertex3f( direction3.X, direction3.Y, direction3.Z );
                glColor3f( 0, 1, 0 );
                glVertex3f( direction4.X, direction4.Y, direction4.Z );

                glEnd();

            }


/*
        for( unsigned int it = 0; it < this->AFTheta->size(); it++ )
            for( unsigned int ip = 0; ip < this->AFPhi->size(); ip++ )
            {
                double t = (*this->AFTheta)[it];
                double p = (*this->AFPhi)[ip];
                double r = (*this->AF)[it][ip];
                Vector3D direction = Vector3D( M_PI_2 - t, p );
                direction = direction * r;

                glBegin( GL_LINES );
                glColor3f( 0, 1, 0 );
                glVertex3f( 0, 0, 0 );
                glVertex3f( direction.X, direction.Y, direction.Z );
                glEnd();

            }
*/
    }
}

void QSceneGLWidget::mousePressEvent(QMouseEvent* e)
{
    this->mouseRightButtonPressed = e->button() == Qt::LeftButton;
}

void QSceneGLWidget::mouseReleaseEvent(QMouseEvent* e)
{
    this->mouseRightButtonPressed = e->button() != Qt::LeftButton;
}

void QSceneGLWidget::mouseMoveEvent(QMouseEvent* e)
{
    if ( this->mouseRightButtonPressed )
    {
        if ( this->oldX > e->x() )
            this->setTheta( this->getTheta() + 0.02 );
        else if ( this->oldX < e->x() )
            this->setTheta( this->getTheta() - 0.02 );

        if ( this->oldY > e->y() )
            this->setPhi( this->getPhi() + 0.02 );
        else if ( this->oldY < e->y() )
            this->setPhi( this->getPhi() - 0.02 );


        this->oldX = e->x();
        this->oldY = e->y();

        this->reloadView();
    }
}

void QSceneGLWidget::wheelEvent(QWheelEvent *event)
{
    float sensivity = 0.1;

    //this->reloadView();
    // Направляющие вектор
    Vector3D v = ( Camera::getPosition() - Camera::getTarget() ).ToVector3D(true);
    Point3D p = ( v * sensivity ).ToPoint3D();

    if ( event->angleDelta().y() > 0 )
        Camera::setPosition( Camera::getPosition() + p );
    else
        Camera::setPosition( Camera::getPosition() - p );

    this->recalcAngle();

    this->reloadView();

}

void QSceneGLWidget::recalcPosition()
{
    // Base class method call
    Camera::recalcPosition();
}

void QSceneGLWidget::recalcAngle()
{
    // Base class method call
    Camera::recalcAngle();
}

void QSceneGLWidget::reloadView()
{
    int nWidth = this->width();
    int nHeight = this->height();

    glClearColor(0.5, 0.5, 0.75, 1.0);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glEnable(GL_DEPTH_TEST);

    if ( this->scene != 0 )
    {
        glViewport( 0, 0, nWidth, nHeight);
        glMatrixMode( GL_PROJECTION );
        glLoadIdentity();
        float x = this->getFov() * 180.0 / M_PI;
        float z = (float)nWidth / nHeight;
        gluPerspective( x, z, Constants::Eps, 62 );

        Point3D pos = this->getPosition();
        Point3D target = this->getTarget();
        Vector3D up = this->getUp();

        gluLookAt(  pos.X, pos.Y, pos.Z, target.X, target.Y, target.Z, up.X, up.Y, up.Z );
        glMatrixMode( GL_MODELVIEW );
    }



    this->updateGL();
}

