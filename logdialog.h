#ifndef LOGDIALOG_H
#define LOGDIALOG_H

#include <Core/Log.h>
#include <string>
#include <QDialog>
#include <QElapsedTimer>

using namespace std;

namespace Ui {
class LogDialog;
}

class LogDialog : public QDialog, public Log
{
    Q_OBJECT

public:
    explicit LogDialog(QWidget *parent = 0);
    ~LogDialog();

    virtual void AddMessage(const string &message);

public slots:
    void raysCalculated( unsigned int raysCount );

private:
    Ui::LogDialog *ui;

    QElapsedTimer timer;
    qint64 lastElapsed = 0;
};

#endif // LOGDIALOG_H
