#ifndef RENDERVIEWDIALOG_H
#define RENDERVIEWDIALOG_H

#include "Core/Render/renderviewframe.h"

#include <QDialog>
#include <QPixmap>

namespace Ui {
class RenderViewDialog;
}

class RenderViewDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RenderViewDialog(QWidget *parent = 0);
    ~RenderViewDialog();


    void setRenderViewFrame( RenderViewFrame &frame );

private:
    Ui::RenderViewDialog *ui;
};

#endif // RENDERVIEWDIALOG_H
