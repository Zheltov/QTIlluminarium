#ifndef CAMERA_H
#define CAMERA_H

#include "Core/Objects/scene.h"
#include "Core/Objects/point3d.h"

// Forward declaration
class Scene;


class Camera
{
public:
    Scene* scene;

    Camera();
    Camera(Scene* sc);
    virtual ~Camera();

    Coordinate getFov() const;
    Coordinate getPhi() const;
    Coordinate getTheta() const;
    Point3D getPosition() const;
    Point3D getTarget() const;
    Vector3D getUp() const;

    virtual int getClientWidth() const = 0;
    virtual int getClientHeight() const = 0;

    void setFov( Coordinate f );

    void setTheta( Coordinate t );
    void setPhi( Coordinate p );
    void setR( Coordinate _r );

    void setPosition( Point3D p );
    void setTarget( Point3D t );

    virtual const Vector3D GetTracingDirection( Coordinate pixel_x_coord, Coordinate pixel_y_coord ) const = 0;

protected:
    Coordinate theta;
    Coordinate phi;
    Coordinate r;
    Coordinate fov;

    Point3D position;
    Point3D target;
    Vector3D up;

    virtual void recalcPosition();
    virtual void recalcAngle();


};

#endif // CAMERA_H
