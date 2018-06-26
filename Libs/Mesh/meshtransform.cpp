#include "meshtransform.h"

#include "debug/raydebugcollection.h"
#include <cmath>

vector<double> &MeshTransform::GetUniformTheta(unsigned int n)
{
    vector<double> &result = (*new vector<double>());
    for( unsigned int i = 0; i < n; i++ )
        result.push_back( i * M_PI / (n - 1) );
    return result;
}

vector<double> &MeshTransform::GetUniformPhi(unsigned int n)
{
    vector<double> &result = (*new vector<double>());
    for( unsigned int i = 0; i < n; i++ )
        result.push_back( i * 2*M_PI / (n - 1) );
    return result;
}

DoubleArray &MeshTransform::MeshToAngleFunction(RayTracer &rayTracer, Point3D center, vector<double> &theta, vector<double> &phi)
{
    DoubleArray &result = (*new DoubleArray(boost::extents[theta.size()][phi.size()]));

    for( unsigned int it = 0; it < theta.size(); it++ )
        for( unsigned int ip = 0; ip < phi.size(); ip++ )
        {
            Vector3D direction = Vector3D( M_PI_2 - theta[it], phi[ip] );

            Intersection *intersection = rayTracer.Intersect( center, direction, 0.0001 );

            float r = 0;
            if ( intersection != NULL )
            {
                Point3D d = intersection->getPosition() - center;
                r = d.Length();

                RayDebugCollection::Rays.push_back( new Ray(center, d) );
            }

            result[it][ip] = r;

            delete intersection;
        }

    return result;
}

MeshTransform::MeshTransform()
{
}
