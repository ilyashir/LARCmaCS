#ifndef BTFORM_H
#define BTFORM_H

#include <QWidget>
#define NUMBER_OF_BT_UNIT 12

namespace Ui {
class BTform;
}

class BTform : public QWidget
{
    Q_OBJECT

public:
    bool Send2BT[NUMBER_OF_BT_UNIT+1];
    explicit BTform(QWidget *parent = 0);
    ~BTform();

public:
    void init();

private slots:
    void on_checkBox_bt10_stateChanged(int arg1);

    void on_checkBox_bt9_stateChanged(int arg1);

    void on_checkBox_bt8_stateChanged(int arg1);

    void on_checkBox_bt7_stateChanged(int arg1);

    void on_checkBox_bt6_stateChanged(int arg1);

    void on_checkBox_bt5_stateChanged(int arg1);

    void on_checkBox_bt4_stateChanged(int arg1);

    void on_checkBox_bt3_stateChanged(int arg1);

    void on_checkBox_bt2_stateChanged(int arg1);

    void on_checkBox_bt1_stateChanged(int arg1);

    void on_checkBox_bt_all_stateChanged(int arg1);
    void on_checkBox_bt11_stateChanged(int arg1);

    void on_checkBox_bt12_stateChanged(int arg1);

signals:
    void Send2BTChange(bool *);
private:
    Ui::BTform *ui;
};

#endif // BTFORM_H
