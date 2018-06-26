#include "sphericalharmonics.h"

#include "boost/multi_array.hpp"
#include "boost/array.hpp"
/*
#include "alglib/ap.h"
#include "alglib/alglibinternal.h"
#include "alglib/alglibmisc.h"
#include "alglib/linalg.h"
#include "alglib/solvers.h"
#include "alglib/optimization.h"
#include "alglib/specialfunctions.h"
#include "alglib/integration.h"

#include "alglib/ap.cpp"
#include "alglib/alglibinternal.cpp"
#include "alglib/alglibmisc.cpp"
#include "alglib/linalg.cpp"
#include "alglib/solvers.cpp"
#include "alglib/optimization.cpp"
#include "alglib/specialfunctions.cpp"
#include "alglib/integration.cpp"
*/
#include <cmath>
#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>

using namespace std;
//using namespace alglib;

/*
 * Compute the zeros of Legendre polynomial Pn(x) in the interval
 *          [-1,1], and the corresponding weighting coefficients
 *          for Gauss-Legendre integration
 * Input:   n                   - Order of the Legendre polynomial
 * Output:  LegzoResult.x[n]    - Zeros of the Legendre polynomial
 *          LegzoResult.w[n] 	- Corresponding weighting coefficients
 *
 * Original: Budak V. P. Matlab legzo
*/
LegzoResult SphericalHarmonics::Legzo( unsigned int n )
{
    LegzoResult result;

    double n0 = ( (double)n + 1) / 2;

    for( unsigned int i = 0; i < n; i++ )
    {
        result.x.push_back(0);
        result.w.push_back(0);
    }
    double hn = 1.0 - 1.0/n;

    for ( double nr = 1; nr < n0; nr++ )
    {
        int nrIndex = nr - 1;

        double z = cos(M_PI * ( nr - 0.5 ) / n );
        double pd = 0;
        while (true)
        {
            double z0 = z;
            double f0 = 1.0;

            double fixn2 = floor(n/2);
            if ( nr == n0 && n != 2*fixn2 )
            {
                z = 0.0;
            }

            double f1 = z;

            for( unsigned int k = 2; k <= n-1; k++ )
            {
                double h = 1.0 - 1.0/k;
                double pf = (1+h)*z*f1 - h*f0;
                f0 = f1;
                f1 = pf;
            }


            double pf = (1+hn)*z*f1 - hn*f0;
            pd = n*(f1 - z*pf)/(1.0 - z*z);
            if ( z == 0.0 )
            {
                break;
            }

            double sum1p = 0;
            for( unsigned int index = 1; index <= nr - 1; index++ )
            {
                unsigned int index1 = index - 1;
                double p = z - result.x[index1];
                sum1p += 1.0/p;
            }
            z = z - pf / ( pd - sum1p * pf );
            if ( abs(z-z0) < abs(z)*1.0e-12 )
            {
                break;
            }
        }

        unsigned int n1 = n - 1;
        result.x[nrIndex] = z;
        result.x[n1 - nrIndex] = -z;
        result.w[nrIndex] = 2.0/((1.0-z*z)*pd*pd);
        result.w[n1 - nrIndex] = result.w[nrIndex];

        n1 = n1;

    }

    return result;


    /*
    typedef boost::multi_array<double, 3> array_type;
    typedef array_type::index index;
    array_type A(boost::extents[3][4][2]);


    index iMin = A.index_bases()[0];
    index iMax = iMin + A.shape()[0] - 1;
    index jMin = A.index_bases()[1];
    index jMax = jMin + A.shape()[1] - 1;
    index kMin = A.index_bases()[2];
    index kMax = kMin + A.shape()[2] - 1;

    for (index i=iMin; i<=iMax; ++i)
    {
        for (index j=jMin; j<=jMax; ++j)
        {
            for (index k=kMin; k<=kMax; ++k)
            {
                A[i][j][k] = 1;
            }
        }
    }
    */
    //A.si

    //A[1][0][2] = 10;

    //delete A;
}

DoubleArray SphericalHarmonics::Schmidt(double mu, unsigned int n)
{
    //unsigned int n1 = n + 1;
    double mu2 = pow( mu, 2 );
    double smu = sqrt(1 - mu2);

    DoubleArray Qkm(boost::extents[n][n]);
    for ( unsigned int i = 0; i < n; i++)
        for ( unsigned int j = 0; j < n; j++)
            Qkm[i][j] = 0;

    Qkm[0][0] = 1;

    for( unsigned int m = 0; m < n; m++ )
    {
        unsigned int m1 = m + 1;
        unsigned int m2 = pow(m, 2);

        if ( m > 0 )
        {
            double somx2 = pow(smu, m);
            double prod = 1;
            for( unsigned int l = 2; l <= 2*m; l = l + 2 )
            {
                prod *= 1.0 - 1.0/(double)l;
            }
            double val = sqrt(prod) * somx2;
            Qkm[m][m] = val;
        }
        if ( m1 < n )
        {
            double val = sqrt(2*m + 1) * mu * Qkm[m][m];
            Qkm[m+1][m] = val;
        }

        for( unsigned int k = (m + 2); k < n; k++ )
        {
            double val = ((2*k-1)*mu * Qkm[k-1][m] - sqrt(pow(k-1,2)-m2)*Qkm[k-2][m]) / sqrt(pow(k,2)-m2);
            Qkm[k][m] = val;
        }
    }



    return Qkm;
}

SHCoefficients SphericalHarmonics::AngleFuncToSHCoefficients(DoubleArray &af, vector<double> &theta, vector<double> &phi, unsigned int n)
{
    unsigned int nphi = phi.size();
    unsigned int ntheta = theta.size();

    /*
    float dphi = 2 * M_PI/ (nphi - 1);
    LegzoResult legzo = SphericalHarmonics::Legzo( ntheta );
    */
    vector<DoubleArray> Qkm;
    for( unsigned int i = 0; i < ntheta; i++ )
    {
        DoubleArray qkm = SphericalHarmonics::Schmidt( cos(theta[i]), n );
        Qkm.push_back( qkm );
    }


    for( unsigned int it = 0; it < ntheta; it++ )
    {
        DoubleArray &qkm = Qkm[it];

        cout<<"mu = "<<theta[it]<<endl;
        for ( unsigned int k = 0; k < n; k++)
        {
            for ( unsigned int m = 0; m <= k; m++)
            {
                //cout<< "Qkm[" << i << "][" << j << "]=" << Qkm[i][j];
                cout<< std::setiosflags(std::ios::fixed)
                    << std::setprecision(4)
                    << std::setw(18)
                    << std::left
                    << qkm[k][m];
            }
            cout<< endl;
        }
    }


    SHCoefficients result(n);
    float norm = 0.00659016290787699370242132345241;
    for( unsigned int k = 0; k < n; k++ )
    {
        float k2 = 2*k + 1;

        for( unsigned int m = 0; m <= k; m++ )
        {

            float ksi = ( m == 0 ) ? 1 : 2;


            for( unsigned int it = 0; it < ntheta; it++ )
            {
                for( unsigned int ip = 0; ip < nphi; ip++ )
                {
                    float temp_phi = phi[ip];
                    float temp_theta = theta[it];

                    result.A[k][m] += norm * ksi * af[it][ip] * Qkm[it][k][m] * cos(m*temp_phi) * k2 * abs( sin(temp_theta) );
                    result.B[k][m] += norm * ksi * af[it][ip] * Qkm[it][k][m] * sin(m*temp_phi) * k2 * abs( sin(temp_theta) );
                }
            }
            /*
            if ( m == 0 )
                ksi = ksi * 2;
                */
        }
    }

    cout<<"Result.A="<<endl;
    for ( unsigned int k = 0; k < n; k++ )
    {
        for ( unsigned int m = 0; m <= k; m++ )
        {
            //cout<< "Qkm[" << i << "][" << j << "]=" << Qkm[i][j];
            cout<< std::setiosflags(std::ios::fixed)
                << std::setprecision(4)
                << std::setw(18)
                << std::left
                << result.A[k][m];
        }
        cout<< endl;
    }

    return result;

    //alglib::real_1d_array b; b.setlength(3);

    //alglib::real_1d_array xq();
    //
    //real_1d_array algPhi; algPhi.setlength(nphi);
    //algPhi.setcontent(phi.size(), &phi[0]);

    //algPhi->setcontent(0, &phi);




    //alglib::spline2dbuildbicubic()


}

SphericalHarmonics::SphericalHarmonics()
{
}


SHCoefficients::SHCoefficients(unsigned int n)
{
    this->A.resize(boost::extents[n][n]);
    this->B.resize(boost::extents[n][n]);
    for( unsigned int i = 0; i < n; i++ )
        for( unsigned int j = 0; j < n; j++ )
        {
            this->A[i][j] = 0;
            this->B[i][j] = 0;
        }
}

SHCoefficients::~SHCoefficients()
{
    //delete this->A;
    //delete this->B;
}
