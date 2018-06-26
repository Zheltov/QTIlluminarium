#include "light.h"

Light::Light()
{
}

Light::~Light()
{

}


LightRay::LightRay(Point3D _from, Point3D _to, Spectrum _illuminance)
    : Ray( _from, _to ),
      illuminance( _illuminance )
{

}

LightRay::LightRay(Point3D _from, Vector3D _dir, Spectrum _illuminance)
    : Ray( _from, _dir ),
      illuminance( _illuminance )
{

}
