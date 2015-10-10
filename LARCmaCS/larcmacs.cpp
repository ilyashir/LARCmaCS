#include <math.h>
#include "larcmacs.h"
#include "ui_larcmacs.h"
#include "packetSSL.h"

LARCmaCS::LARCmaCS(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LARCmaCS),
    scalingRequested(true),
    sizescene(10),
    drawscale(1)
{
    ui->setupUi(this);

    fieldscene = new FieldScene();
    ui->fieldView->setScene(fieldscene);

    macsArray = new QString[12];

    receiver.init();
    mainalg.init();
    sceneview.init();
    connector.init();
    bttransmitter.init();

    //robots connect
    connect(&wifiform,SIGNAL(initRobots()),&connector.worker, SLOT(startBroadcast()));
    connect(&wifiform,SIGNAL(stopInit()),&connector.worker, SLOT(stopBroadcast()));
    connect(&connector.worker,SIGNAL(robotAdded(QString)),&wifiform,SLOT(addRobot(QString)));
    connect(&connector.worker,SIGNAL(allNeededRobotsEnabled()),&wifiform,SLOT(initEnded()));

    // GUIS
    connect(&wifiform,SIGNAL(PickWifiRobot(QString)),this, SLOT(PickWifiRobot(QString)));
    connect(&connector.worker,SIGNAL(sendPortList(QStringList)),this,SLOT(displayPorts(QStringList)));
    connect(this,SIGNAL(openPort(QString)),&connector.worker,SLOT(openPort(QString)));

    //algorithm connect
    connect(this, SIGNAL(MLEvalString(QString)),&mainalg.worker,SLOT(EvalString(QString)));
    connect(this, SIGNAL(MatlabPause()), &mainalg.worker, SLOT(Pause()));
    connect(&receiver.worker, SIGNAL(activateMA(PacketSSL)), &mainalg.worker, SLOT(run(PacketSSL)));
    connect(&mainalg.worker, SIGNAL(mainAlgFree()), &receiver.worker, SLOT(MainAlgFree()));
    //reciever
    connect(this,SIGNAL(ChangeMaxPacketFrequencyMod(bool)),&receiver.worker,SLOT(ChangeMaxPacketFrequencyMod(bool)));

    //send command to robots
    connect(this,SIGNAL(receiveMacArray(QString*)),&connector.worker,SLOT(receiveMacArray(QString*)));
    connect(&mainalg.worker, SIGNAL(sendToConnector(int,QByteArray)), &connector.worker, SLOT(run(int,QByteArray)));

    //gui connector
    connect(&sceneview.worker, SIGNAL(updateView()), this, SLOT(updateView()));
    connect(ui->sceneslider, SIGNAL(valueChanged(int)), this, SLOT(scaleView(int)));

    //info GUI
    connect(&mainalg.worker,SIGNAL(UpdatePauseState(QString)),this,SLOT(UpdatePauseState(QString)));
    connect(&mainalg.worker, SIGNAL(StatusMessage(QString)), this, SLOT(UpdateStatusBar(QString)));
    connect(&receiver.worker, SIGNAL(UpdateSSLFPS(QString)), this, SLOT(UpdateSSLFPS(QString)));
    connect(&bttransmitter.worker, SIGNAL(UpdatePipeStatus(bool)), this, SLOT(UpdatePipeStatus(bool)));

    //SendToBTtransmitter
    connect(&mainalg.worker,SIGNAL(sendToBTtransmitter(char*)),&bttransmitter.worker,SLOT(addmessage(char*)));

    //remotecontrol
    connect(&remotecontol,SIGNAL(RC_control(int,int,int,int)),this,SLOT(remcontrolsender(int, int,int, int)));
    connect(this,SIGNAL(sendToConnectorRM(int,QByteArray)),&connector.worker,SLOT(run(int,QByteArray)));

    //fieldScene Update
    connect(&receiver.worker,SIGNAL(activateGUI()),this,SLOT(fieldsceneUpdateRobots()));
    connect(this,SIGNAL(updateRobots()),fieldscene,SLOT(update()));
    //    connect(&receiver.worker, SIGNAL(activateGUI(PacketSSL)), &sceneview.worker, SLOT(repaintScene(PacketSSL)));

    //BTsenderform
    connect(&btform,SIGNAL(Send2BTChange(bool *)),this,SLOT(Send2BTChangeit(bool *)));
    connect(&btform,SIGNAL(Send2BTChange(bool *)),&mainalg.worker,SLOT(Send2BTChangeit(bool *)));

    sceneview.start();
    receiver.start();
    mainalg.start();
    connector.start();
    bttransmitter.start();
    UpdateStatusBar("Waiting SSL connection...");
    UpdateSSLFPS("FPS=0");
    Send2BTChangeit(btform.Send2BT);

}

void LARCmaCS::displayPorts(QStringList portList)
{
    //for (int i=0;i<portList.size();++i)
    ui->ard_comboBox->addItems(portList);
}

void LARCmaCS::Send2BTChangeit(bool * BTbox)
{
    ui->checkBox_BT->setChecked(btform.Send2BT[ui->RobotComboBox->currentIndex()]);
}
void LARCmaCS::remcontrolsender(int l, int r,int k, int b)
{
    //qDebug()<<"REM!";
    int N=ui->RobotComboBox->currentIndex()+1;
    QByteArray command;
    command.append(QString("rule ").toUtf8());
    command.append(l);
    command.append(r);
    command.append(k);
    command.append(b);
//    char dat[5];
//    //dat[0] = 'c';
//    dat[0] = '<';
//    dat[1] = r;
//    dat[2] = l;
//    dat[3] = k;
//    dat[4] = '>';
//    if (port->isOpen())
//        port->write(dat,5);
    emit sendToConnectorRM(N,command);
}
void LARCmaCS::fieldsceneUpdateRobots()
{
    fieldscene->UpdateRobots(receiver.worker.detection);
    emit updateRobots();
}
/*
void LARCmaCS::initEnded()
{
    ui->initRobotsBtn->setText("Start");
}

void LARCmaCS::addRobot(QString robot)
{
    ui->robotsList->addItem(robot);
}
void LARCmaCS::on_initRobotsBtn_clicked()
{
    if (!ui->initRobotsBtn->text().compare("Start"))
    {
        emit initRobots();
        ui->initRobotsBtn->setText("Stop");
    }
    else
    {
        emit stopInit();
        //        for (int i=0;i<ui->robotsList->count();++i)
        //        {
        //            macsArray[i] = ui->robotsList->item(i)->text();
        //        }
        ui->initRobotsBtn->setText("Start");
    }
}
*/

LARCmaCS::~LARCmaCS()
{
    delete ui;
}

void LARCmaCS::UpdatePauseState(QString message)
{ 
    ui->label_Pause->setText(message);
}
void LARCmaCS::UpdatePipeStatus(bool status)
{
    ui->pipe_checkBox->setChecked(status);
}
void LARCmaCS::UpdateSSLFPS(QString message)
{
    ui->label_SSL_FPS->setText(message);
}
void LARCmaCS::UpdateStatusBar(QString message)
{
    ui->StatusLabel->setText(message);
}
void LARCmaCS::scaleView(int _sizescene)
{
//    cout << _sizescene << "  " << sizescene;
//    qreal scaleFactor = (drawScale-1) - (qreal)_scaleFactor/100;
//    cout << scaleFactor << "  ";
//    qreal factor = ui->view->matrix().scale ( scaleFactor, scaleFactor ).mapRect ( QRectF ( 0, 0, 1, 1 ) ).width();
//    cout << factor << "  ";
//    if ( factor > 0.07 && factor < 100.0 )
//    drawscale = 1 - (float)(sizescene-_sizescene)/10;
    drawscale = pow(0.9, _sizescene-sizescene);
    sizescene = _sizescene;
//    ui->view->wheelEvent();
//    cout << " DS " << drawscale << endl;
    scalingRequested = true;

}

void LARCmaCS::updateView()
{
//  static float lastScale = 0;
//  if ( shutdownSoccerView )
//  {
//    return;
//  }
  if ( scalingRequested )
  {
      qreal factor = ui->fieldView->matrix().scale ( drawscale, drawscale ).mapRect ( QRectF ( 0, 0, 1, 1 ) ).width();
      if ( factor > 0.07 && factor < 100.0 )
          ui->fieldView->scale ( drawscale, drawscale );
      scalingRequested = false;
      ui->fieldView->viewport()->update();
  }

}
void LARCmaCS::on_pushButton_clicked()
{
    btform.hide();
    btform.show();
    btform.init();
}

void LARCmaCS::on_pushButton_Pause_clicked()
{
    emit MatlabPause();
}

#include <QFileDialog>
void LARCmaCS::on_pushButton_SetMLdir_clicked()
{
    QString  dir = QFileDialog::getExistingDirectory();
    QString  s="cd "+dir;
    qDebug()<<"New Matlab directory = "<<s;
    emit MLEvalString(s);
}

void LARCmaCS::on_PickRobot_pushButton_clicked()
{
    wifiform.hide();
    wifiform.show();
}

void LARCmaCS::PickWifiRobot(QString addr)
{
    wifiaddrdata[ui->RobotComboBox->currentIndex()]=addr;
    QString temp;
    temp.setNum(ui->RobotComboBox->currentIndex()+1);
    temp=temp+") "+addr;
    ui->RobotComboBox->setItemText(ui->RobotComboBox->currentIndex(),temp);
    qDebug()<<"PICK"<<addr;
    emit receiveMacArray(wifiaddrdata);
}

void LARCmaCS::on_pushButton_RC_clicked()
{
    remotecontol.hide();
    remotecontol.show();
    remotecontol.TimerStart();
}

void LARCmaCS::on_checkBox_BT_stateChanged(int arg1)
{
    btform.Send2BT[ui->RobotComboBox->currentIndex()]=arg1;
    btform.init();
}

void LARCmaCS::on_RobotComboBox_currentIndexChanged(int index)
{
     ui->checkBox_BT->setChecked(btform.Send2BT[ui->RobotComboBox->currentIndex()]);
}

void LARCmaCS::on_openPortButton_clicked()
{
    emit openPort(ui->ard_comboBox->currentText());
}

void LARCmaCS::on_checkBox_MlMaxFreq_stateChanged(int arg1)
{
    emit(ChangeMaxPacketFrequencyMod(arg1>0));
}
