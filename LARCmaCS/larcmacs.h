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
#include "remotecontrol.h"
#define NUM_CONTROL_ROBOTS 12

namespace Ui
{
    class LARCmaCS;
}

class LARCmaCS : public QWidget
{
    Q_OBJECT

public:
    RemoteControl remotecontol;
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
    void Send2BTChangeit(bool *BTbox);
    void fieldsceneUpdateRobots();
    void UpdateSSLFPS(QString message);
    void UpdateStatusBar(QString message);
    void UpdatePipeStatus(bool status);
    void UpdatePauseState(QString message);
    void updateView();
    void scaleView(int);

private slots:
    void PickWifiRobot(QString addr);
    void on_pushButton_Pause_clicked();
    void on_PickRobot_pushButton_clicked();
    void on_pushButton_SetMLdir_clicked();
    void on_pushButton_RC_clicked();
    void remcontrolsender(int l, int r,int k, int b);
    void on_checkBox_BT_stateChanged(int arg1);
    void on_pushButton_clicked();

    void on_RobotComboBox_currentIndexChanged(int index);

signals:
    void sendToConnectorRM(int N,QByteArray command);
    void receiveMacArray(QString*);
    void MatlabPause();
    void MLEvalString(QString s);
    void updateRobots();
};

#endif // LARCMACS_H
