#include "wifiform.h"
#include "ui_wifiform.h"

WifiForm::WifiForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WifiForm)
{
    ui->setupUi(this);
}

WifiForm::~WifiForm()
{
    delete ui;
}

#include <qdebug.h>
void WifiForm::on_robotsList_doubleClicked(const QModelIndex &index)
{
    int in=index.row();
    qDebug()<<in<<index.data()<<index.data().toString();
    emit stopInit();
    ui->initRobotsBtn->setText("Start");
    this->close();
    emit PickWifiRobot(index.data().toString());
}


void WifiForm::initEnded()
{
    ui->initRobotsBtn->setText("Start");
}

void WifiForm::addRobot(QString robot)
{
    ui->robotsList->addItem(robot);
}

void WifiForm::on_initRobotsBtn_clicked()
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
