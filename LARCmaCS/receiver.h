#ifndef RECIEVER_H
#define RECIEVER_H

#include <QObject>
#include <QThread>
#include <QSharedPointer>
#include "packetSSL.h"
#include "robocup_ssl_client.h"
#include <iostream>


using namespace std;

#include <time.h>       /* clock_t, clock(), CLOCKS_PER_SEC */


struct ReceiverWorker : public QObject
{
    Q_OBJECT
public:
    explicit ReceiverWorker() {mainalgisfree=true;timer_m=clock(); Time_count=0;}
public slots:
    void MainAlgFree()
    {
       if ((NewPacket) && (MaxPacketFrequencyMod))
       {
           mainalgisfree=false;
           NewPacket=false;
           emit activateMA(packetssl);
           //emit activateGUI();
       }
       else
           mainalgisfree=true;
    }
    void start()
    {
        shutdownread = false;
        mainalgisfree = true;
        NewPacket=false;
        MaxPacketFrequencyMod=false;
        cout << "Receiver worker start" << endl;
        run();
    }    

    void stop() { shutdownread = true; }

public slots:
    void ChangeMaxPacketFrequencyMod(bool state)
    {
        MaxPacketFrequencyMod=state;
        cout<<"MaxPacketFrequencyMod = "<<state<<endl;
    }
public:
    SSL_DetectionFrame detection;
signals:
    void activateGUI();
    void activateMA(PacketSSL packetssl);
    void UpdateSSLFPS(QString message);

private:
    PacketSSL packetssl;
    clock_t timer_m;
    int Time_count;
private:
    void run();
    RoboCupSSLClient client;
    SSL_WrapperPacket packet;
    bool NewPacket;
    bool shutdownread;
    bool mainalgisfree;
    bool MaxPacketFrequencyMod;
};

struct Receiver : public QObject
{
    Q_OBJECT
public:
    ReceiverWorker worker;
    QThread thread;

    Receiver() {}
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
        cout << "Init ok" << endl;
        connect(this, SIGNAL(wstart()), &worker, SLOT(start()));
        connect(this, SIGNAL(wstop()), &worker, SLOT(stop()));
        connect(&thread, SIGNAL(finished()), &worker, SLOT(deleteLater()));
    }

    void start()
    {
        thread.start();
//        cout << "thread start" << endl;
        emit wstart();
    }

    void stop() { emit wstop(); }

signals:
    void wstart();
    void wstop();
};

#endif // RECIEVER_H
