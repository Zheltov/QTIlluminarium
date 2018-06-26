#ifndef SCENEVIEWDIALOG_H
#define SCENEVIEWDIALOG_H

#include <QDialog>

#include "Core/Objects/scene.h"

#include "boost/multi_array.hpp"
#include <vector>

using namespace std;

namespace Ui {
class SceneViewDialog;
}

class SceneViewDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SceneViewDialog(QWidget *parent = 0);
    ~SceneViewDialog();

    void setScene( Scene &scene );
    void setAF(boost::multi_array<double, 2> &af, vector<double> &afTheta, vector<double> &afPhi);

private:
    Ui::SceneViewDialog *ui;
};

#endif // SCENEVIEWDIALOG_H
