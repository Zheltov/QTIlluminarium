#ifndef RENDER_H
#define RENDER_H

#include "Core/RayTracer/raytracer.h"

class Render
{
public:
    Render( RayTracer &rt );

private:
    RayTracer &rayTracer;
};

#endif // RENDER_H
