#ifndef LOCALESTIMATEGEOMCOMPRESSED_H
#define LOCALESTIMATEGEOMCOMPRESSED_H

#include "globalillumination.h"
#include "LocalEstimate/localestimatecalculator.h"
#include "LocalEstimate/facelocalestimate.h"
#include <vector>

using namespace std;

class LocalEstimateGeomCompressed: public GlobalIllumination
{
public:
    LocalEstimateGeomCompressed( RayTracer &rt, Log &lg );
    virtual ~LocalEstimateGeomCompressed();

    virtual void Render( RenderFrame &frame );

private:
    LocalEstimateCalculator *calculator;

    vector<RenderPointLocalEstimate> renderPoints;
    vector<FaceLocalEstimate> renderPointsFaces;

    void GenerateCalculatedStructure(RenderFrame &frame);
};

#endif // LOCALESTIMATEGEOMCOMPRESSED_H
