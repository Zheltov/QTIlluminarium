#ifndef LOCALESTIMATECALCULATOR_H
#define LOCALESTIMATECALCULATOR_H

#include <QThread>
#include <QMutexLocker>

#include "Core/Log.h"
#include "Core/RayTracer/raytracer.h"
#include "renderframelocalestimate.h"

#include <vector>

using namespace std;

class LocalEstimateCalculator : public QThread
{
    Q_OBJECT
public:
    LocalEstimateCalculator( uint _threadIndex, RayTracer &rt, Log &lg );
    LocalEstimateCalculator( uint _threadIndex, RayTracer &rt, Log &lg, RenderFrameLocalEstimate &_frame );
    virtual ~LocalEstimateCalculator();


    RenderFrameLocalEstimate *getRenderFrame();
    void setRenderFrame( RenderFrameLocalEstimate &_frame );
    void Render();

public slots:
    void stop();

signals:
    void raysCalculated( uint threadId, uint raysCount, uint deltaRaysCount );
    void messageInfo( const std::string msg );

private:
    RayTracer &rayTracer;
    Log &log;
    RenderFrameLocalEstimate *frame;
    uint threadIndex;

    QMutex m_mutex;
    bool m_stop;

    Light *RouletteLight();
    void run();
};

#endif // LOCALESTIMATECALCULATOR_H
