#ifndef LARCMACS_H
#define LARCMACS_H

#include <QWidget>

#include "fieldScene.h"
#include "receiver.h"
#include "mainAlg.h"
#include "sceneView.h"
#include "connector.h"
#include "BTtransmitter.h"
#include "BTform.h"
#include "WiFiForm.h"

#define NUM_CONTROL_ROBOTS 12

namespace Ui
{
    class LARCmaCS;
}

class LARCmaCS : public QWidget
{
    Q_OBJECT

public:

    WifiForm wifiform;
    BTform btform;
    explicit LARCmaCS(QWidget *parent = 0);
    ~LARCmaCS();

    FieldScene *fieldscene;
    QString * macsArray;

protected:    
    BTtransmitter bttransmitter;
    bool scalingRequested;
    sceneView sceneview;
    Receiver receiver;
    MainAlg mainalg;
    Connector connector;


private:
    Ui::LARCmaCS *ui;
    float drawscale;
    qreal sizescene;
    QString wifiaddrdata[NUM_CONTROL_ROBOTS];

private slots:
    void fieldsceneUpdateRobots();
    void UpdateSSLFPS(QString message);
    void UpdateStatusBar(QString message);
    void UpdatePipeStatus(bool status);
    void UpdatePauseState(int status);
    void updateView();
    void scaleView(int);
    void on_pushButton_clicked();

private slots:
    void PickWifiRobot(QString addr);
    void on_pushButton_Pause_clicked();
    void on_PickRobot_pushButton_clicked();
    void on_pushButton_SetMLdir_clicked();

signals:

    void receiveMacArray(QString*);
    void MatlabPause();
    void MatlabChangeDirrectory(QString dir);
};

#endif // LARCMACS_H
