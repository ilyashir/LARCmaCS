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

    receiver.init();
    mainalg.init();
    sceneview.init();
    connector.init();

    connect(this,SIGNAL(initRobots()),&connector.worker, SLOT(startBroadcast()));
    connect(this,SIGNAL(stopInit()),&connector.worker, SLOT(stopBroadcast()));
    connect(&connector.worker,SIGNAL(robotAdded(QString)),this,SLOT(addRobot(QString)));
    connect(&connector.worker,SIGNAL(allNeededRobotsEnabled()),this,SLOT(initEnded()));
    //ui->robotsList->add
    connect(&receiver.worker, SIGNAL(activate(PacketSSL)), &mainalg.worker, SLOT(run(PacketSSL)));
    connect(&mainalg.worker, SIGNAL(mainAlgFree()), &receiver.worker, SLOT(mainAlgFree()));
//    connect(&receiver.worker, SIGNAL(activateGUI(PacketSSL)), &sceneview.worker, SLOT(repaintScene(PacketSSL)));
    connect(&mainalg.worker, SIGNAL(sendToConnector(double *)), &connector.worker, SLOT(run(double *)));
    connect(&sceneview.worker, SIGNAL(updateView()), this, SLOT(updateView()));
    connect(ui->sceneslider, SIGNAL(valueChanged(int)), this, SLOT(scaleView(int)));

    sceneview.start();
    receiver.start();
    mainalg.start();
    connector.start();
}

LARCmaCS::~LARCmaCS()
{
    delete ui;
}

void LARCmaCS::initEnded()
{
    ui->initRobotsBtn->setText("Start");
}

void LARCmaCS::addRobot(QString robot)
{
    ui->robotsList->addItem(robot);
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
        ui->initRobotsBtn->setText("Start");
    }
}
