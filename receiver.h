#ifndef RECIEVER_H
#define RECIEVER_H

#include <QtGui/QWidget>
#include <QtCore/QDebug>
#include <QtCore/QThread>
#include <time.h>
#include "packetSSL.h"
#include "robocup_ssl_client.h"

struct ReceiverWorker : public QObject
{
    Q_OBJECT
public:
    SSL_DetectionFrame detection;
private:
    RoboCupSSLClient client;
    SSL_WrapperPacket packet;
    PacketSSL packetssl;
    clock_t timer_m;
    int Time_count;
    bool NewPacket;
    bool shutdownread;
    bool mainalgisfree;
    bool MaxPacketFrequencyMod;

public:
    explicit ReceiverWorker() {mainalgisfree=true; timer_m=clock(); Time_count=0;}

public slots:
//    void MainAlgFree()
//    {
//       if ((NewPacket) && (MaxPacketFrequencyMod))
//       {
//           mainalgisfree=false;
//           NewPacket=false;
//           emit activateMA(packetssl);
//           //emit activateGUI();
//       }
//       else
//           mainalgisfree=true;
//    }

    void start()
    {
        shutdownread = false;
        mainalgisfree = true;
        NewPacket=false;
        MaxPacketFrequencyMod=false;
        qDebug() << "Receiver worker start" << endl;
        run();
    }

    void stop() { shutdownread = true; }

//    void ChangeMaxPacketFrequencyMod(bool state)
//    {
//        MaxPacketFrequencyMod=state;
//        cout<<"MaxPacketFrequencyMod = "<<state<<endl;
//    }

signals:
//    void activateGUI();
//    void activateMA(PacketSSL packetssl);
//    void UpdateSSLFPS(QString message);

private:


private:
    void run();

};

struct Receiver : public QObject
{
    Q_OBJECT
public:
    ReceiverWorker worker;
    QThread thread;

    explicit Receiver() {}
    ~Receiver()
    {
        stop();
        thread.wait(100);
        thread.terminate();
        thread.wait(100);
    }

    void init()
    {

        worker.moveToThread(&thread);
        qDebug() << "Init ok" << endl;
        connect(this, SIGNAL(wstart()), &worker, SLOT(start()));
        connect(this, SIGNAL(wstop()), &worker, SLOT(stop()));
        connect(&thread, SIGNAL(finished()), &worker, SLOT(deleteLater()));
    }

    void start()
    {
        thread.start();
        qDebug() << ("<Reciever> thread started\n");
        emit wstart();
    }

    void stop() { emit wstop(); }

signals:
    void wstart();
    void wstop();
};

#endif // RECIEVER_H
