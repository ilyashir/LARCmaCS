#include "btform.h"
#include "ui_btform.h"

BTform::BTform(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BTform)
{
    ui->setupUi(this);
}

BTform::~BTform()
{
    delete ui;
}

void BTform::on_checkBox_bt10_stateChanged(int arg1)
{
    Send2BT[10]=(arg1>0);
}

void BTform::on_checkBox_bt9_stateChanged(int arg1)
{
    Send2BT[9]=(arg1>0);
}

void BTform::on_checkBox_bt8_stateChanged(int arg1)
{
    Send2BT[8]=(arg1>0);
}

void BTform::on_checkBox_bt7_stateChanged(int arg1)
{
    Send2BT[7]=(arg1>0);
}

void BTform::on_checkBox_bt6_stateChanged(int arg1)
{
    Send2BT[6]=(arg1>0);
}

void BTform::on_checkBox_bt5_stateChanged(int arg1)
{
    Send2BT[5]=(arg1>0);
}

void BTform::on_checkBox_bt4_stateChanged(int arg1)
{
    Send2BT[4]=(arg1>0);
}

void BTform::on_checkBox_bt3_stateChanged(int arg1)
{
    Send2BT[3]=(arg1>0);
}

void BTform::on_checkBox_bt2_stateChanged(int arg1)
{
    Send2BT[2]=(arg1>0);
}

void BTform::on_checkBox_bt1_stateChanged(int arg1)
{
    Send2BT[1]=(arg1>0);
}

void BTform::on_checkBox_bt_all_stateChanged(int arg1)
{
    for (int i=0; i<NUMBER_OF_BT_UNIT; i++)
    {
        Send2BT[i+1]=(arg1>0);
    }
    ui->checkBox_bt1->setChecked(arg1);
    ui->checkBox_bt2->setChecked(arg1);
    ui->checkBox_bt3->setChecked(arg1);
    ui->checkBox_bt4->setChecked(arg1);
    ui->checkBox_bt5->setChecked(arg1);
    ui->checkBox_bt6->setChecked(arg1);
    ui->checkBox_bt7->setChecked(arg1);
    ui->checkBox_bt8->setChecked(arg1);
    ui->checkBox_bt9->setChecked(arg1);
    ui->checkBox_bt10->setChecked(arg1);
}
