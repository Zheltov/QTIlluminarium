#include <QPainter>

#include "renderviewframeimagewidget.h"
#include "ui_renderviewframeimagewidget.h"

#include "Core/Light/light.h"

RenderViewFrameImageWidget::RenderViewFrameImageWidget(QWidget *parent) :
    QWidget(parent),
    pixmap( NULL ),
    frame( NULL ),
    imageMode( Full ),
    ui(new Ui::RenderViewFrameImageWidget)
{
    ui->setupUi(this);
}

RenderViewFrameImageWidget::~RenderViewFrameImageWidget()
{
    delete ui;

    if ( this->pixmap != 0 )
        delete this->pixmap;
}

void RenderViewFrameImageWidget::setRenderViewFrame(RenderViewFrame *_frame)
{
    this->frame = _frame;
    this->drawPixmap();
}

void RenderViewFrameImageWidget::setRenderViewFrameImageMode(RenderViewFrameImageMode mode)
{
    this->imageMode = mode;
    this->drawPixmap();
}

void RenderViewFrameImageWidget::drawPixmap()
{
    if ( this->pixmap != 0 )
        delete this->pixmap;

    if ( this->frame == NULL )
        return;

    float maxOD = this->getNormCoefficient( NormCoefficientTypeObject );
    float maxLD = this->getNormCoefficient( NormCoefficientTypeLights );

    int w = this->frame->width;
    int h = this->frame->height;

    this->pixmap = new QPixmap(w, h);
    QPainter painter(this->pixmap);

    QColor color;

    for( int i = 0; i < this->frame->renderScreenPoints.size(); i++ )
    {
        RenderScreenPoint &renderScreenPoint = *this->frame->renderScreenPoints[i];
        //RenderPoint &renderPoint = renderScreenPoint.getRenderPoint();


        Light *l = dynamic_cast<Light*>( renderScreenPoint.getRenderPoint().face.obj );
        Coordinate norm = l != NULL  ? maxLD : maxOD;
        if ( norm == 0 )
            norm = 1;

        //norm = norm / 2;

        Spectrum illuminance = this->getSpectrumByImageMode( renderScreenPoint );

        int r = 255 * illuminance.getColorR() / norm;
        int g = 255 * illuminance.getColorG() / norm;
        int b = 255 * illuminance.getColorB() / norm;

        if ( r > 255 ) r = 255;
        if ( g > 255 ) g = 255;
        if ( b > 255 ) b = 255;

        color.setRed(r);
        color.setGreen(g);
        color.setBlue(b);
        painter.setPen(color);
        painter.drawPoint(renderScreenPoint.getX(), renderScreenPoint.getY());

    }

    this->update();
}

void RenderViewFrameImageWidget::paintEvent(QPaintEvent *event)
{
    if ( this->pixmap != 0 )
    {
        QPainter painter(this);
        painter.drawPixmap(0, 0, *this->pixmap);
    }
}

Spectrum RenderViewFrameImageWidget::getSpectrumByImageMode(RenderScreenPoint &renderPoint)
{
    switch( this->imageMode )
    {
        case Full:
            return renderPoint.illuminanceDirect + renderPoint.illuminanceIndirect;
        case Direct:
            return renderPoint.illuminanceDirect;
        case Indirect:
            return renderPoint.illuminanceIndirect;
    }
}

Coordinate RenderViewFrameImageWidget::getNormCoefficient( NormCoefficientType type )
{
    const float avgThresholdCoefficient = 5;

    float max = 0;
    float avg = 0;
    float avgThreshold = 0;


    for( unsigned int i = 0; i < this->frame->renderScreenPoints.size(); i++ )
    {
        RenderScreenPoint &renderPoint = *this->frame->renderScreenPoints[i];
        avg += this->getSpectrumByImageMode( renderPoint ).MaxValue();
    }

    avg = avg / this->frame->renderScreenPoints.size();
    avgThreshold = avg * avgThresholdCoefficient;



    for( unsigned int i = 0; i < this->frame->renderScreenPoints.size(); i++ )
    {
        RenderScreenPoint &renderPoint = *this->frame->renderScreenPoints[i];
        Coordinate maxVal = this->getSpectrumByImageMode( renderPoint ).MaxValue();

        Light *l = dynamic_cast<Light*>( renderPoint.getRenderPoint().face.obj );

        if ( ( type == NormCoefficientTypeObject && l == NULL ) || ( type == NormCoefficientTypeLights && l != NULL ) )
        {
            if ( maxVal > max && maxVal < avgThreshold )
                max = maxVal;
        }
    }

    return max;
}
