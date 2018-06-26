#ifndef RENDERVIEWFRAMEIMAGEWINDOW_H
#define RENDERVIEWFRAMEIMAGEWINDOW_H

#include <QMainWindow>
#include <QPixmap>
#include <QClipboard>

#include "Core/Render/renderviewframe.h"

namespace Ui {
class RenderViewFrameImageWindow;
}

class RenderViewFrameImageWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit RenderViewFrameImageWindow(QWidget *parent = 0);
    ~RenderViewFrameImageWindow();

    void setRenderViewFrame( RenderViewFrame *_frame );

private slots:
    void on_comboBox_currentIndexChanged(int index);

    void on_btnExportIlluminanceToClipboard_clicked();

private:
    RenderViewFrame *frame;
    Ui::RenderViewFrameImageWindow *ui;
};

#endif // RENDERVIEWFRAMEIMAGEWINDOW_H
