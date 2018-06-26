#ifndef LOCALESTIMATECALCULATORTHREAD_H
#define LOCALESTIMATECALCULATORTHREAD_H

#include <QThread>
#include <QMutexLocker>
#include "localestimatecalculator.h"

class LocalEstimateCalculatorThread : public QThread
{
public:
    LocalEstimateCalculatorThread( RenderFrameLocalEstimate &_frame );

public slots:
    void stop();

private:
    RenderFrameLocalEstimate &frame;
    QMutex m_mutex;
    bool m_stop;

    void run();
};

#endif // LOCALESTIMATECALCULATORTHREAD_H
