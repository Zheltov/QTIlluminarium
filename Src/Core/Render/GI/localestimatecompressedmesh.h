#ifndef LOCALESTIMATECOMPRESSEDMESH_H
#define LOCALESTIMATECOMPRESSEDMESH_H

#include <QObject>
#include <QThread>

#include "globalillumination.h"
#include "LocalEstimate/localestimatecalculator.h"
#include "LocalEstimate/renderframecompressormesh.h"


class LocalEstimateCompressedMesh : public QObject, public GlobalIllumination
{
    Q_OBJECT
public:
    LocalEstimateCompressedMesh( RayTracer &rt, Log &lg, RenderFrameCompressorMesh *_compressor );
    virtual ~LocalEstimateCompressedMesh();

    virtual void Render( RenderFrame &frame );
    virtual void Stop();

public slots:
    void raysCalculated( uint threadId, uint raysCount, uint deltaRaysCount );

private:
    RayTracer &rayTracer;
    Log &log;

    RenderFrameCompressed *compressedFrame;
    vector<LocalEstimateCalculator*> calculatorThreads;
    int totalRaysCalculated;

    RenderFrameCompressorMesh *compressor;

    void BugsCorrectionFrames( vector<RenderFrameLocalEstimate *> &frames );

    void CollectFramesToFrame(const vector<RenderFrameLocalEstimate*> frames);
};

#endif // LOCALESTIMATECOMPRESSEDMESH_H
