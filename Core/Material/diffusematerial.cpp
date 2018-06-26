#include "diffusematerial.h"
#include "Core/func.h"
#include "Core/constants.h"

#include <cmath>

DiffuseMaterial::DiffuseMaterial(Spectrum _reflectance)
{
    this->reflectance = _reflectance;
}

Spectrum DiffuseMaterial::BRDF(const Vector3D &, const Vector3D &, const Vector3D &)
{
    return this->reflectance;
}

Vector3D DiffuseMaterial::GetRandomReflectedDirection(const Vector3D &, const Vector3D &normal)
{
    // get random direction
    float d = 2;
    float u = 0;
    float v = 0;
    while ( d > 1 )
    {
        u = 1 - 2 * func::randf();
        v = 1 - 2 * func::randf();
        d = u * u + v * v;
    }

    float sqrtD = sqrt( d );
    float cTheta = u / sqrtD;
    float sTheta = v / sqrtD;
    float sPhi = sqrt( func::randf() );
    float cPhi = sqrt( 1 - sPhi * sPhi );

    // to normal system coordinate
    if ( fabs( normal.Z ) > ( 1 - Constants::Eps ) )
    {
        if ( normal.Z > 0 )
            return Vector3D( (float)( sPhi * cTheta ), (float)( sPhi * sTheta ), (float)cPhi );
        else
            return Vector3D( -(float)( sPhi * cTheta ), -(float)( sPhi * sTheta ), -(float)cPhi );
    }

    float sqrtNcPhi = sqrt( ( 1 - cPhi * cPhi ) / ( 1 - normal.Z * normal.Z ) );

    return Vector3D(
                (float)( cPhi * normal.X - ( normal.Y * sTheta + normal.X * normal.Z * cTheta ) * sqrtNcPhi ),
                (float)( cPhi * normal.Y + ( normal.X * sTheta - normal.Y * normal.Z * cTheta ) * sqrtNcPhi ),
                (float)( cPhi * normal.Z + ( 1 - normal.Z * normal.Z ) * cTheta * sqrtNcPhi ) );
}
