#ifndef WIFIFORM_H
#define WIFIFORM_H

#include <QWidget>

namespace Ui {
class WifiForm;
}

class WifiForm : public QWidget
{
    Q_OBJECT

public:
    explicit WifiForm(QWidget *parent = 0);
    ~WifiForm();

private slots:
    void on_robotsList_doubleClicked(const QModelIndex &index);

    void on_initRobotsBtn_clicked();

private slots:
    void addRobot(QString);
    void initEnded();

private:
    Ui::WifiForm *ui;
signals:
    void initRobots();
    void stopInit();
    void PickWifiRobot(QString);
};

#endif // WIFIFORM_H
