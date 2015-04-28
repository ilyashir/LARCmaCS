#ifndef REMOTECONTROL_H
#define REMOTECONTROL_H

#include <QWidget>
#include <QTimer>
namespace Ui {
class RemoteControl;
}

#include <QKeyEvent>
class RemoteControl : public QWidget
{
    Q_OBJECT

    void closeEvent(QCloseEvent *);

public:
    explicit RemoteControl(QWidget *parent = 0);
    ~RemoteControl();
private:
    QTimer timer;
    void keyPressEvent(QKeyEvent *key);
    void keyReleaseEvent(QKeyEvent * key);
    int keys[256];
    int key_shift;
private slots:
    void RC_send(void);
public slots:
    void TimerStart();
    void TimerStop();
private:
    Ui::RemoteControl *ui;
signals:
    void RC_control(int left,int right,int kick,int beep);
};

#endif // REMOTECONTROL_H
