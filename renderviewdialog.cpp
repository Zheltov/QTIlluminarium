#include <QPainter>

#include "renderviewdialog.h"
#include "ui_renderviewdialog.h"

RenderViewDialog::RenderViewDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RenderViewDialog)
{
    ui->setupUi(this);

}

RenderViewDialog::~RenderViewDialog()
{
    delete ui;
}

void RenderViewDialog::setRenderViewFrame(RenderViewFrame &frame)
{
    this->ui->imageViewer->setRenderViewFrame( frame );
}

/*
void RenderViewDialog::setRenderResult(RenderViewFrame &frame)
{
    if ( this->pixmap != 0 )
        delete this->pixmap;


    float maxOD = 0;
    float maxLD = 0;
    for( int i = 0; i < frame.renderScreenPoints.size(); i++ )
    {
        RenderScreenPoint &renderPoint = *frame.renderScreenPoints[i];
        //Coordinate maxVal = renderPoint.illuminanceDirect.MaxValue();
        Coordinate maxVal = renderPoint.illuminanceIndirect.MaxValue();

        Light *l = dynamic_cast<Light*>( &renderPoint.getRenderPoint().obj);

        if ( l != NULL )
        {
            if ( maxVal > maxLD )
                maxLD = maxVal;
        }
        else
        {
            if ( maxVal > maxOD )
                maxOD = maxVal;
        }
    }


    int w = frame.width;
    int h = frame.height;

    this->pixmap = new QPixmap(w, h);
    QPainter painter(this->pixmap);

    QColor color;

    for( int i = 0; i < frame.renderScreenPoints.size(); i++ )
    {
        RenderScreenPoint &renderScreenPoint = *frame.renderScreenPoints[i];
        //RenderPoint &renderPoint = renderScreenPoint.getRenderPoint();


        Light *l = dynamic_cast<Light*>( &renderScreenPoint.getRenderPoint().obj);
        Coordinate norm = l != NULL  ? maxLD : maxOD;

        int r = 255 * renderScreenPoint.illuminanceIndirect.getColorR() / norm;
        int g = 255 * renderScreenPoint.illuminanceDirect.getColorG() / norm;
        int b = 255 * renderScreenPoint.illuminanceDirect.getColorB() / norm;

        //int g = 255 * static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
        //int b = 255 * static_cast <float> (rand()) / static_cast <float> (RAND_MAX);

        color.setRed(r);
        color.setGreen(g);
        color.setBlue(b);
        painter.setPen(color);
        painter.drawPoint(renderScreenPoint.getX(), renderScreenPoint.getY());

    }
}

void RenderViewDialog::paintEvent(QPaintEvent *e)
{
    if ( this->pixmap != 0 )
    {
        QPainter painter(this);
        painter.drawPixmap(0, 0, *this->pixmap);
    }

    //painter.drawPoint(5,5);
}
*/
