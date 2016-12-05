#include "larcmacs.h"
#include "ui_larcmacs.h"

LARCmaCS::LARCmaCS(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LARCmaCS)
{
    ui->setupUi(this);

    receiver.init();

    receiver.start();
}

LARCmaCS::~LARCmaCS()
{
    delete ui;
}
