#include "btform.h"
#include "ui_btform.h"

BTform::BTform(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BTform)
{
    ui->setupUi(this);
    for (int i=0; i<NUMBER_OF_BT_UNIT; i++)
    {
        Send2BT[i]=1;
    }
}

BTform::~BTform()
{
    delete ui;
}
void BTform::init()
{
    ui->checkBox_bt1->setChecked(Send2BT[1-1]);
    ui->checkBox_bt2->setChecked(Send2BT[2-1]);
    ui->checkBox_bt3->setChecked(Send2BT[3-1]);
    ui->checkBox_bt4->setChecked(Send2BT[4-1]);
    ui->checkBox_bt5->setChecked(Send2BT[5-1]);
    ui->checkBox_bt6->setChecked(Send2BT[6-1]);
    ui->checkBox_bt7->setChecked(Send2BT[7-1]);
    ui->checkBox_bt8->setChecked(Send2BT[8-1]);
    ui->checkBox_bt9->setChecked(Send2BT[9-1]);
    ui->checkBox_bt10->setChecked(Send2BT[10-1]);
    ui->checkBox_bt11->setChecked(Send2BT[11-1]);
    ui->checkBox_bt12->setChecked(Send2BT[12-1]);
}

void BTform::on_checkBox_bt12_stateChanged(int arg1)
{

    Send2BT[12-1]=(arg1>0);
    emit Send2BTChange(Send2BT);
}

void BTform::on_checkBox_bt11_stateChanged(int arg1)
{

    Send2BT[11-1]=(arg1>0);
    emit Send2BTChange(Send2BT);
}

void BTform::on_checkBox_bt10_stateChanged(int arg1)
{
    Send2BT[10-1]=(arg1>0);
    emit Send2BTChange(Send2BT);
}

void BTform::on_checkBox_bt9_stateChanged(int arg1)
{
    Send2BT[9-1]=(arg1>0);
    emit Send2BTChange(Send2BT);
}

void BTform::on_checkBox_bt8_stateChanged(int arg1)
{
    Send2BT[8-1]=(arg1>0);
    emit Send2BTChange(Send2BT);
}

void BTform::on_checkBox_bt7_stateChanged(int arg1)
{
    Send2BT[7-1]=(arg1>0);
    emit Send2BTChange(Send2BT);
}

void BTform::on_checkBox_bt6_stateChanged(int arg1)
{
    Send2BT[6-1]=(arg1>0);
    emit Send2BTChange(Send2BT);
}

void BTform::on_checkBox_bt5_stateChanged(int arg1)
{
    Send2BT[5-1]=(arg1>0);
    emit Send2BTChange(Send2BT);
}

void BTform::on_checkBox_bt4_stateChanged(int arg1)
{
    Send2BT[4-1]=(arg1>0);
    emit Send2BTChange(Send2BT);
}

void BTform::on_checkBox_bt3_stateChanged(int arg1)
{
    Send2BT[3-1]=(arg1>0);
    emit Send2BTChange(Send2BT);
}

void BTform::on_checkBox_bt2_stateChanged(int arg1)
{
    Send2BT[2-1]=(arg1>0);
    emit Send2BTChange(Send2BT);
}

void BTform::on_checkBox_bt1_stateChanged(int arg1)
{
    Send2BT[1-1]=(arg1>0);
    emit Send2BTChange(Send2BT);
}

void BTform::on_checkBox_bt_all_stateChanged(int arg1)
{
    for (int i=0; i<NUMBER_OF_BT_UNIT; i++)
    {
        Send2BT[i]=(arg1>0);
    }
    init();
    emit Send2BTChange(Send2BT);
}
