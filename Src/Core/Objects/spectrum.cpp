#include "spectrum.h"

Spectrum::Spectrum()
{
}

Spectrum::Spectrum(Coordinate rgb) : r(rgb), g(rgb), b(rgb)
{

}

Spectrum::Spectrum(Coordinate _r, Coordinate _g, Coordinate _b) : r(_r), g(_g), b(_b)
{

}

Spectrum::~Spectrum()
{

}
