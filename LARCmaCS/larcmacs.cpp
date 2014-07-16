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
    sceneview.init();
    mainalg.init();
//    connect(&receiver.worker, SIGNAL(activate()), &sceneview.worker, SLOT(repaintScene()));
    connect(&receiver.worker, SIGNAL(activate()), &mainalg.worker, SLOT(run()));
    connect(&sceneview.worker, SIGNAL(updateView()), this, SLOT(updateView()));
//    connect(&recievedn, SIGNAL(activate()),&sceneview,SLOT(repainScene()));
//    connect(&recievedn, SIGNAL(finished()), &recievedn, SLOT(deleteLater()));
    connect(ui->sceneslider, SIGNAL(valueChanged(int)), this, SLOT(scaleView(int)));
//    sceneview.start();
    //recievedn.startread();
    sceneview.start();
    receiver.start();
    mainalg.start();
}

LARCmaCS::~LARCmaCS()
{
    delete ui;
}

void LARCmaCS::scaleView ( int _sizescene )
{
//    cout << _sizescene << "  " << sizescene;
//    qreal scaleFactor = (drawScale-1) - (qreal)_scaleFactor/100;
//    cout << scaleFactor << "  ";
//    qreal factor = ui->view->matrix().scale ( scaleFactor, scaleFactor ).mapRect ( QRectF ( 0, 0, 1, 1 ) ).width();
//    cout << factor << "  ";
//    if ( factor > 0.07 && factor < 100.0 )
    //drawscale = 1 - (float)(sizescene-_sizescene)/10;
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
