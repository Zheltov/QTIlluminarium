#ifndef SPHERICALHARMONICS_H
#define SPHERICALHARMONICS_H

#include <vector>
#include "boost/multi_array.hpp"

using namespace std;


typedef boost::multi_array<double, 2> DoubleArray;
typedef DoubleArray::index index;


class LegzoResult
{
public:
    vector<double> x;
    vector<double> w;
};

class SHCoefficients
{
public:
    DoubleArray A;
    DoubleArray B;

    SHCoefficients(unsigned int n);
    ~SHCoefficients();
};

class SphericalHarmonics
{
public:
    static LegzoResult Legzo(unsigned int n);
    static DoubleArray Schmidt(double mu, unsigned int n );
    static SHCoefficients AngleFuncToSHCoefficients( DoubleArray &af, vector<double> &theta, vector<double> &phi, unsigned int n );

    SphericalHarmonics();
};



#endif // SPHERICALHARMONICS_H
