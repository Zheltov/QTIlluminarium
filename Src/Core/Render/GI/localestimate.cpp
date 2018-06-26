#include "localestimate.h"
#include "LocalEstimate/renderframelocalestimate.h"
#include "Debug/raydebugcollection.h"
#include "Core/func.h"
#include "Core/constants.h"
#include <vector>
#include <exception>
#include <stdexcept>
#include <unistd.h>

using namespace std;

LocalEstimate::LocalEstimate(RayTracer &rt, Log &lg)
    : rayTracer( rt ),
      log( lg ),
      renderFrame( NULL ),
      totalRaysCalculated( 0 )
{ }

LocalEstimate::~LocalEstimate()
{
}

void LocalEstimate::Render( RenderFrame &frame )
{
    this->renderFrame = &frame;

    // оптимальное число потоков
    const uint threadsCount = ( QThread::idealThreadCount() > 2 ) ? QThread::idealThreadCount() - 1 : QThread::idealThreadCount();

    log.AddMessage("Start render");

    for( uint threadIndex = 0; threadIndex < threadsCount; threadIndex++  )
    {
        // ***************************************
        usleep(1000);
        // ***************************************

        RenderFrameLocalEstimate *frameLocalEstimate = new RenderFrameLocalEstimate();

        // Clone points
        for( unsigned int i = 0; i < frame.renderPoints.size(); i++ )
        {
            RenderPoint &renderPoint = *this->renderFrame->renderPoints[i];

            RenderPointLocalEstimate *p = new RenderPointLocalEstimate( renderPoint );

            frameLocalEstimate->AddRenderPoint( *p );
        }

        LocalEstimateCalculator *calculator = new LocalEstimateCalculator( threadIndex, this->rayTracer, this->log, *frameLocalEstimate );

        connect( calculator, SIGNAL( raysCalculated(uint,uint,uint) ), this, SLOT( raysCalculated(uint,uint,uint) ) );
        connect( calculator, SIGNAL( messageInfo(std::string) ), this, SLOT( messageInfo(std::string) ) );

        this->calculatorThreads.push_back( calculator );

        log.AddMessage("Created " + func::to_string( threadIndex + 1) + "/" + func::to_string( threadsCount)  +  " thread");
    }

    for( uint threadIndex = 0; threadIndex < threadsCount; threadIndex++  )
    {
        this->calculatorThreads[threadIndex]->start();
    }
    log.AddMessage("Threads runned");

}

void LocalEstimate::Stop()
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

void LocalEstimate::raysCalculated( uint threadId, uint raysCount, uint deltaRaysCount )
{
    totalRaysCalculated += deltaRaysCount;
    log.AddMessage( "Thread: #" + func::to_string(threadId) + " Rays: " + func::to_string(raysCount) + " Total rays: "  + func::to_string(this->totalRaysCalculated) );
}

void LocalEstimate::messageInfo(const string msg)
{
    log.AddMessage(msg);
}

void LocalEstimate::BugsCorrectionFrames( vector<RenderFrameLocalEstimate*> &frames )
{
    return;

    const float coeff = 1.25;
    RenderFrameLocalEstimate &frame0 = *frames[0];


    for( unsigned int i = 0; i < frame0.renderPoints.size(); i++ )
    {
        // получаем средние показатели для точки
        Coordinate avg = 0;
        Spectrum sumIlluminance(0);
        Spectrum avgIlluminance(0);
        vector<Spectrum> illuminance;
        for( unsigned int iFrame = 0; iFrame < frames.size(); iFrame++ )
        {
            RenderPointLocalEstimate &renderPoint = *frames[iFrame]->renderPoints[i];

            illuminance.push_back( renderPoint.illuminance );
            sumIlluminance += renderPoint.illuminance;

            //avgIlluminance += renderPoint.illuminance;
        }
        avgIlluminance = sumIlluminance / frames.size();

        avg = avgIlluminance.Sum() * coeff;


        // точки превосходящие средние показатели в coeff раз
        vector<uint> moreAvgIndexes;
        Spectrum moreAvgIlluminance(0);
        for( unsigned int iFrame = 0; iFrame < frames.size(); iFrame++ )
        {
            RenderPointLocalEstimate &renderPoint = *frames[iFrame]->renderPoints[i];
            float x = renderPoint.illuminance.Sum();

            if ( x > avg )
            {
                moreAvgIndexes.push_back( iFrame );
                moreAvgIlluminance += renderPoint.illuminance;
            }
        }

        // новая средняя яркость
        avgIlluminance = ( sumIlluminance - moreAvgIlluminance ) / ( frames.size() - moreAvgIndexes.size() );
        for( uint k = 0; k < moreAvgIndexes.size(); k++ )
        {
            uint iFrame = moreAvgIndexes[k];
            RenderPointLocalEstimate &renderPoint = *frames[iFrame]->renderPoints[i];

            renderPoint.illuminance = Spectrum(0,5,0); //avgIlluminance;
        }



        /*
        //avg *= coeff;
        for( unsigned int iFrame = 0; iFrame < frames.size(); iFrame++ )
        {
            RenderPointLocalEstimate &renderPoint = *frames[iFrame]->renderPoints[i];
            float x = renderPoint.illuminance.Sum();

            if ( x > avg )
            {
                // Spectrum(3, 0, 0); //

                Spectrum illuminance = ( sumIlluminance - renderPoint.illuminance ) / ( frames.size() - 1 );

                renderPoint.illuminance = illuminance;
            }

            //if ( iFrame == 7 )
            //    renderPoint.illuminance = Spectrum(1, 0, 0);
        }
        */

    }

}

void LocalEstimate::CollectFramesToFrame( const vector<RenderFrameLocalEstimate *> frames )
{
    const float coeff = 4;

    for( unsigned int i = 0; i < this->renderFrame->renderPoints.size(); i++ )
    {
        RenderPoint &renderPoint = *this->renderFrame->renderPoints[i];

        Spectrum avgIlluminance(0);
        for( uint iFrame = 0; iFrame < frames.size(); iFrame++ )
        {
            RenderFrameLocalEstimate &frame = *frames[iFrame];
            RenderPointLocalEstimate &p = *frame.renderPoints[i];

            avgIlluminance += p.illuminance;
        }
        avgIlluminance = avgIlluminance / frames.size();
        float avg = avgIlluminance.Sum() * coeff;

        if ( avg < Constants::Eps )
            continue;


        int count = 0;
        for( uint iFrame = 0; iFrame < frames.size(); iFrame++ )
        {
            RenderFrameLocalEstimate &frame = *frames[iFrame];
            RenderPointLocalEstimate &p = *frame.renderPoints[i];

            if ( p.illuminance.Sum() > avg )
            {
                //renderPoint.illuminanceIndirect = Spectrum(0, 8, 0);
                //count = 0;
                //break;
            }
            else
            {
                renderPoint.illuminanceIndirect += p.illuminance;
                count++;
            }

            /*
            if ( p.illuminance.Sum() < avg )
            {
                renderPoint.illuminanceIndirect += p.illuminance;
                count++;
            }
            else
            {
                renderPoint.illuminanceIndirect += Spectrum(0,8,0);
            }
            */
        }

        if ( count > 0 )
        {
            renderPoint.illuminanceIndirect = renderPoint.illuminanceIndirect / count;
        }
    }
}

/*
void LocalEstimate::CollectFramesToFrame( const vector<RenderFrameLocalEstimate *> frames )
{
    for( unsigned int i = 0; i < this->renderFrame->renderPoints.size(); i++ )
    {
        RenderPoint &renderPoint = *this->renderFrame->renderPoints[i];

        Spectrum avgIlluminance(0);
        for( uint iFrame = 0; iFrame < frames.size(); iFrame++ )
        {
            RenderFrameLocalEstimate &frame = *frames[iFrame];
            RenderPointLocalEstimate &p = *frame.renderPoints[i];

            renderPoint.illuminanceIndirect += p.illuminance;
        }

        renderPoint.illuminanceIndirect = renderPoint.illuminanceIndirect / frames.size();
    }
}
*/
