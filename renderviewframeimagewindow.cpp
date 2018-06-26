#include "renderviewframeimagewindow.h"
#include "ui_renderviewframeimagewindow.h"

RenderViewFrameImageWindow::RenderViewFrameImageWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::RenderViewFrameImageWindow)
{
    ui->setupUi(this);
}

RenderViewFrameImageWindow::~RenderViewFrameImageWindow()
{
    delete ui;
}

void RenderViewFrameImageWindow::setRenderViewFrame(RenderViewFrame *_frame)
{
    this->frame = _frame;
    this->ui->imageViewer->setRenderViewFrame( _frame );
}

void RenderViewFrameImageWindow::on_comboBox_currentIndexChanged(int index)
{
    RenderViewFrameImageMode mode = static_cast<RenderViewFrameImageMode>(index);
    this->ui->imageViewer->setRenderViewFrameImageMode( mode );
}

void RenderViewFrameImageWindow::on_btnExportIlluminanceToClipboard_clicked()
{
    QClipboard *clipboard = QApplication::clipboard();
    QString result;

    for( unsigned int i = 0; i < this->frame->renderScreenPoints.size(); i++ )
    {
        RenderScreenPoint &point = *this->frame->renderScreenPoints[i];

        result += QString::number(point.getX())
                + "|" + QString::number(point.getY())
                + "|" + QString::number(point.illuminanceDirect.getColorR())
                + "|" + QString::number(point.illuminanceDirect.getColorG())
                + "|" + QString::number(point.illuminanceDirect.getColorB())
                + "|" + QString::number(point.illuminanceIndirect.getColorR())
                + "|" + QString::number(point.illuminanceIndirect.getColorG())
                + "|" + QString::number(point.illuminanceIndirect.getColorB())
                + "\r\n";
    }

    clipboard->setText(result);
}
