#include "logdialog.h"
#include "ui_logdialog.h"

#include "Core/func.h"

LogDialog::LogDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LogDialog)
{
    ui->setupUi(this);

    timer.start();
}

LogDialog::~LogDialog()
{
    delete ui;
}

void LogDialog::AddMessage(const string &message)
{
    qint64 e = timer.elapsed();
    float time = (float)( e - lastElapsed ) / 1000.0;

    ui->list->addItem( QString::fromStdString( "[" + func::to_string( time, 4) + " s] - " + message ) );
    QApplication::processEvents();

    lastElapsed = e;
}

void LogDialog::raysCalculated(unsigned int raysCount)
{
    this->AddMessage( "Render rays" + func::to_string(raysCount) );
}
