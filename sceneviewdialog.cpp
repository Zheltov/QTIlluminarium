#include "sceneviewdialog.h"
#include "ui_sceneviewdialog.h"

SceneViewDialog::SceneViewDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SceneViewDialog)
{
    ui->setupUi(this);
}

SceneViewDialog::~SceneViewDialog()
{
    delete ui;
}

void SceneViewDialog::setScene(Scene &scene)
{
    this->ui->SceneGLWidget->scene = &scene;
}

void SceneViewDialog::setAF(boost::multi_array<double, 2> &af, vector<double> &afTheta, vector<double> &afPhi)
{
    this->ui->SceneGLWidget->AF = &af;
    this->ui->SceneGLWidget->AFTheta = &afTheta;
    this->ui->SceneGLWidget->AFPhi = &afPhi;

}
