#include "localestimatecompressedmesh.h"

#include "LocalEstimate/renderframelocalestimate.h"
#include "Debug/raydebugcollection.h"
#include "Core/func.h"
#include <vector>
#include <exception>
#include <stdexcept>
#include <unistd.h>

using namespace std;

LocalEstimateCompressedMesh::LocalEstimateCompressedMesh(RayTracer &rt, Log &lg, RenderFrameCompressorMesh *_compressor)
    : rayTracer( rt ),
      log( lg ),
      compressor( _compressor ),
      compressedFrame( NULL ),
      totalRaysCalculated( 0 )
{ }

LocalEstimateCompressedMesh::~LocalEstimateCompressedMesh()
{
    if ( compressedFrame != NULL )
        delete this->compressedFrame;
}

void LocalEstimateCompressedMesh::Render( RenderFrame &frame )
{
    // оптимальное число потоков
    const uint threadsCount = QThread::idealThreadCount();

    log.AddMessage("Start render");

    // мы не работаем без компрессора
    if ( this->compressor == NULL )
        throw new std::runtime_error( "Compressor is not set" );

    // сжатие фрейма
    this->compressedFrame = this->compressor->Compress( frame );

    log.AddMessage( "Frame compressed by faces. It has " + func::to_string( this->compressedFrame->renderPoints.size() ) + " render points in " + func::to_string(this->compressedFrame->renderPointsFaces.size()) + " triangle faces" );

    for( uint threadIndex = 0; threadIndex < threadsCount; threadIndex++  )
    {
        // ***************************************
        usleep(1000);
        // ***************************************
        RenderFrameLocalEstimate *frameLocalEstimate = new RenderFrameLocalEstimate();

        // Clone points
        for( unsigned int i = 0; i < this->compressedFrame->renderPoints.size(); i++ )
        {
            RenderPointLocalEstimate *renderPoint = this->compressedFrame->renderPoints[i];

            RenderPointLocalEstimate *p = new RenderPointLocalEstimate( renderPoint->renderPoint );

            frameLocalEstimate->AddRenderPoint( *p );
        }


        LocalEstimateCalculator *calculator = new LocalEstimateCalculator( threadIndex, this->rayTracer, this->log, *frameLocalEstimate );

        connect( calculator, SIGNAL( raysCalculated(uint,uint,uint) ), this, SLOT( raysCalculated(uint,uint,uint) ) );

        this->calculatorThreads.push_back( calculator );

        log.AddMessage("Created " + func::to_string( threadIndex + 1) + "/" + func::to_string( threadsCount)  +  " thread");
    }

    for( uint threadIndex = 0; threadIndex < threadsCount; threadIndex++  )
    {
        this->calculatorThreads[threadIndex]->start();
    }
    log.AddMessage("Threads runned");

}

void LocalEstimateCompressedMesh::Stop()
{
    log.AddMessage( "Start stop threads" );
    for( uint threadIndex = 0; threadIndex < this->calculatorThreads.size(); threadIndex++ )
    {
        LocalEstimateCalculator *calculator = this->calculatorThreads[threadIndex];
        calculator->stop();
    }

    log.AddMessage( "Wait stop threads" );
    vector<RenderFrameLocalEstimate*> frames;
    for( uint threadIndex = 0; threadIndex < this->calculatorThreads.size(); threadIndex++ )
    {
        LocalEstimateCalculator *calculator = this->calculatorThreads[threadIndex];
        calculator->wait();

        frames.push_back( calculator->getRenderFrame() );
    }
    log.AddMessage( "Threads stopped" );


    this->BugsCorrectionFrames( frames );
    log.AddMessage( "Frames bugs corrected" );

    // Сбор в один frame
    this->CollectFramesToFrame( frames );
    log.AddMessage( "Frames collected to one frame" );

    if ( this->compressor != NULL )
        this->compressor->UncompressIlluminance( *this->compressedFrame );

    log.AddMessage( "Frame uncompressed" );


    for( uint threadIndex = 0; threadIndex < this->calculatorThreads.size(); threadIndex++ )
    {
        LocalEstimateCalculator *calculator = this->calculatorThreads[threadIndex];

        // удаляем frame т.к. был создан только для калькулятора
        delete calculator->getRenderFrame();
        delete calculator;
    }
    log.AddMessage( "All objects were destroy" );
}

void LocalEstimateCompressedMesh::raysCalculated( uint threadId, uint raysCount, uint deltaRaysCount )
{
    totalRaysCalculated += deltaRaysCount;
    log.AddMessage( "Thread: #" + func::to_string(threadId) + " Total rays: " + func::to_string(this->totalRaysCalculated) + " Rays: " + func::to_string(raysCount) );
}

void LocalEstimateCompressedMesh::BugsCorrectionFrames( vector<RenderFrameLocalEstimate*> &frames )
{
    const float coeff = 2;
    RenderFrameLocalEstimate &frame0 = *frames[0];

    for( unsigned int i = 0; i < frame0.renderPoints.size(); i++ )
    {
        Coordinate avg = 0;
        Spectrum avgIlluminance(0);
        for( unsigned int iFrame = 0; iFrame < frames.size(); iFrame++ )
        {
            RenderPointLocalEstimate &renderPoint = *frames[iFrame]->renderPoints[i];

            avgIlluminance += renderPoint.illuminance;
        }
        avgIlluminance /= frames.size();

        avg = avgIlluminance.Sum() * coeff;
        //avg *= coeff;
        for( unsigned int iFrame = 0; iFrame < frames.size(); iFrame++ )
        {
            RenderPointLocalEstimate &renderPoint = *frames[iFrame]->renderPoints[i];
            float x = renderPoint.illuminance.Sum();

            if ( x > avg )
            {
                renderPoint.illuminance = avgIlluminance;
            }

            //if ( iFrame == 7 )
            //    renderPoint.illuminance = Spectrum(1, 0, 0);
        }


    }

}

void LocalEstimateCompressedMesh::CollectFramesToFrame( const vector<RenderFrameLocalEstimate *> frames )
{
    for( unsigned int i = 0; i < this->compressedFrame->renderPoints.size(); i++ )
    {
        RenderPointLocalEstimate &renderPoint = *this->compressedFrame->renderPoints[i];

        for( uint iFrame = 0; iFrame < frames.size(); iFrame++ )
        {
            RenderFrameLocalEstimate &frame = *frames[iFrame];
            RenderPointLocalEstimate &p = *frame.renderPoints[i];

                renderPoint.illuminance += p.illuminance;
                renderPoint.counterRaysCos1Zero += p.counterRaysCos1Zero;
        }

        renderPoint.illuminance = renderPoint.illuminance / frames.size();
        renderPoint.renderPoint.illuminanceIndirect = renderPoint.illuminance;
    }
}



