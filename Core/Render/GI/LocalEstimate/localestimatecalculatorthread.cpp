#include "localestimatecalculatorthread.h"
#include <QDebug>

LocalEstimateCalculatorThread::LocalEstimateCalculatorThread(RenderFrameLocalEstimate &_frame)
    : frame( _frame ), m_stop( false )
{
}

void LocalEstimateCalculatorThread::stop()
{
    qDebug()<<"Thread::stop called from main thread: "<<currentThreadId();
    QMutexLocker locker( &m_mutex );
    m_stop = true;
}

void LocalEstimateCalculatorThread::run()
{
    long i = 0;
    while (1) {
        if ( i % 1000000 == 0 )
            qDebug()<<"aaaa";

        QMutexLocker locker(&m_mutex);
        if (m_stop)
        {
            qDebug()<<"go out";
            break;
        }

        i = i + 1;

        //msleep(3000);
    }

}
