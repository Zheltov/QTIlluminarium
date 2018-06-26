#ifndef LOCALESTIMATE_H
#define LOCALESTIMATE_H

#include <QObject>
#include <QThread>

#include "globalillumination.h"
#include "LocalEstimate/localestimatecalculator.h"

class LocalEstimate : public QObject, public GlobalIllumination
{
    Q_OBJECT
public:
    LocalEstimate( RayTracer &rt, Log &lg );
    virtual ~LocalEstimate();

    virtual void Render( RenderFrame &frame );
    virtual void Stop();

public slots:
    void raysCalculated( uint threadId, uint raysCount, uint deltaRaysCount );
    void messageInfo( const std::string msg );

private:
    RayTracer &rayTracer;
    Log &log;

    vector<LocalEstimateCalculator*> calculatorThreads;
    int totalRaysCalculated;
    RenderFrame *renderFrame;

    void BugsCorrectionFrames( vector<RenderFrameLocalEstimate *> &frames );
    void CollectFramesToFrame(const vector<RenderFrameLocalEstimate*> frames);
};

#endif // LOCALESTIMATE_H
