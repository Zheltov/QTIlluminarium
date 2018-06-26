#include "func.h"

#include <string>
#include <sstream>
#include <iomanip>
#include <iostream>
#include <cstdlib>
#include <algorithm>
//#include <random>

#include <QTime>

#include <ctime>
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/linear_congruential.hpp>
#include <boost/random/uniform_int.hpp>
#include <boost/random/uniform_real.hpp>
#include <boost/random/variate_generator.hpp>

string func::to_string(int value)
{
    std::stringstream ss;
    ss<<value;
    std::string str;
    ss>>str;

    return str;
}

string func::to_string(float value, int precision)
{
    std::stringstream ss;
    ss<<setprecision(precision)<<value;
    std::string str;
    ss>>str;

    return str;
}


float func::randf()
{
    return static_cast <float> ( qrand() ) / static_cast <float> (RAND_MAX);
    /*
    boost::mt19937 rng();
    boost::uniform_real<float> u(0, 1);
    boost::variate_generator<boost::mt19937&, boost::uniform_real<float> > gen(rng, u);
    return gen();
    */
    //srand( time(0) );
    //return static_cast <float> (rng()) / static_cast <float> (RAND_MAX);
}


void func::randSetFuse(unsigned int value)
{
    qsrand( value );
}
