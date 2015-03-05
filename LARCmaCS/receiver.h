#ifndef RECIEVER_H
#define RECIEVER_H

#include <QObject>
#include <QThread>
#include <QSharedPointer>
#include "packetSSL.h"
#include "robocup_ssl_client.h"
#include <iostream>

using namespace std;

struct ReceiverWorker : public QObject
{
    Q_OBJECT
public:
    explicit ReceiverWorker() {}

public slots:
    void start()
    {
        shutdownread = false;
        cout << "Receiver worker start" << endl;
        run();
    }    

    void stop() { shutdownread = true; }

    void mainAlgFree() { mainalgisfree = true; }

signals:
    void activate(PacketSSL packetssl);
    void activateGUI(PacketSSL packetssl);

private:
    void run();

    RoboCupSSLClient client;
    SSL_WrapperPacket packet;
    bool shutdownread;
    bool mainalgisfree;
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
