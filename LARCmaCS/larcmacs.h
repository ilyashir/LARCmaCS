#ifndef LARCMACS_H
#define LARCMACS_H

#include <QWidget>
#include "fieldScene.h"
#include "sceneView.h"
//#include "recievedn.h"
#include "receiver.h"
#include "mainAlg.h"

namespace Ui {
class LARCmaCS;
}

class LARCmaCS : public QWidget
{
    Q_OBJECT

public:
    explicit LARCmaCS(QWidget *parent = 0);
    ~LARCmaCS();

    FieldScene* fieldscene;

protected:
    bool scalingRequested;
    sceneView sceneview;
    Receiver receiver;
    MainAlg mainalg;
//    RecievedN recievedn;


private:
    Ui::LARCmaCS *ui;
    float drawscale;
    qreal sizescene;

private slots:
    void updateView();
    void scaleView(int);
};

#endif // LARCMACS_H
