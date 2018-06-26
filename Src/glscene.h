#ifndef GLSCENE_H
#define GLSCENE_H

#include <QWidget>
#include <QGLWidget>

namespace Ui {
class GLScene;
}

class GLScene : public QGLWidget
{
    Q_OBJECT

public:
    explicit GLScene(QWidget *parent = 0);
    ~GLScene();
protected:
    void initializeGL();
    void resizeGL(int nWidth, int nHeight);
    void paintGL();
private:
    Ui::GLScene *ui;
};

#endif // GLSCENE_H
