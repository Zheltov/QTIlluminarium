#ifndef RENDERVIEWFRAMEIMAGEWIDGET_H
#define RENDERVIEWFRAMEIMAGEWIDGET_H

#include <QWidget>
#include <QPixmap>

#include "Core/Render/renderviewframe.h"

namespace Ui {
class RenderViewFrameImageWidget;
}


enum RenderViewFrameImageMode{
    Full = 0,
    Direct = 1,
    Indirect = 2
};

enum NormCoefficientType {
    NormCoefficientTypeObject = 0,
    NormCoefficientTypeLights = 0
};

class RenderViewFrameImageWidget : public QWidget
{
    Q_OBJECT

public:
    explicit RenderViewFrameImageWidget(QWidget *parent = 0);
    ~RenderViewFrameImageWidget();

    void setRenderViewFrame( RenderViewFrame *_frame );
    void setRenderViewFrameImageMode( RenderViewFrameImageMode mode );
    void drawPixmap();

protected:
    void paintEvent(QPaintEvent *);

private:
    Ui::RenderViewFrameImageWidget *ui;

    RenderViewFrame *frame;
    RenderViewFrameImageMode imageMode;
    QPixmap* pixmap;

    Spectrum getSpectrumByImageMode( RenderScreenPoint &renderPoint );
    Coordinate getNormCoefficient( NormCoefficientType type );
};




#endif // RENDERVIEWFRAMEIMAGEWIDGET_H
