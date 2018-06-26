#include "camera.h"
#include <math.h>

Camera::Camera()
    : scene( NULL ), position( Point3D(1, 0, 0) ), target( Point3D(0, 0, 0) ), up( Vector3D(0, 0, 1, true) ), fov( M_PI_2 )
{
    this->recalcAngle();
}

Camera::Camera(Scene* sc)
    : scene( sc ), position( Point3D(1, 0, 0) ), target( Point3D(0, 0, 0) ), up( Vector3D(0, 0, 1, true) ), fov( M_PI_2 )
{
    this->recalcAngle();
}

Camera::~Camera()
{

}

Coordinate Camera::getFov() const
{
    return this->fov;
}

Coordinate Camera::getPhi() const
{
    return this->phi;
}

Coordinate Camera::getTheta() const
{
    return this->theta;
}

Point3D Camera::getPosition() const
{
    return this->position;
}

Point3D Camera::getTarget() const
{
    return this->target;
}

Vector3D Camera::getUp() const
{
    return this->up;
}

void Camera::setFov(Coordinate f)
{
    this->fov = f;
}

void Camera::setTheta(Coordinate t)
{
    this->theta = t;
    this->recalcPosition();
}

void Camera::setPhi(Coordinate p)
{
    this->phi = p;
    this->recalcPosition();
}

void Camera::setR(Coordinate _r)
{
    this->r = _r;
    this->recalcPosition();
}

void Camera::setPosition(Point3D p)
{
    this->position = p;
    this->recalcAngle();
}

void Camera::setTarget(Point3D t)
{
    this->target = t;
    this->recalcAngle();
}

/*
const Vector3D Camera::GetTracingDirection( Coordinate pixel_x_coord, Coordinate pixel_y_coord, int clientWidth, int clientHeight ) const
{
    double width = 2 * ( sin( this->fov / 2 ) );



    //double width = this->getFov();// * 180.0 / M_PI;
    double height = ( (double)clientHeight / (double)clientWidth ) * width;

    Vector3D direction( this->position, this->target );

    Vector3D right = direction * this->up;

    pixel_y_coord = clientHeight - pixel_y_coord;

    float x = ( pixel_x_coord - clientWidth / 2 );
    float y = ( pixel_y_coord - clientHeight / 2 );

    Vector3D target = right * (float)( width * x / ( clientWidth - 1 ) )
                            + this->up * (float)( height * y / ( clientHeight - 1 ) );

    //target.Normalize();

    target += direction;

    target.Normalize();

    return target;

}
*/

void Camera::recalcPosition()
{
    this->position = Point3D(
            ( -r * cos( phi ) * cos( theta ) + target.X ),
            ( -r * cos( phi ) * sin( theta ) + target.Y ),
            ( -r * sin( phi ) + target.Z )
        );
}

void Camera::recalcAngle()
{
    Coordinate x = target.X - position.X;
    Coordinate y = target.Y - position.Y;
    Coordinate z = target.Z - position.Z;

    this->theta = atan2( y, z );
    phi = atan2( z, sqrt( x * x + y * y ) );
    r = sqrt( x * x + y * y + z * z );
}
