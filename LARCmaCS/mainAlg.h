#ifndef MAINALG_H
#define MAINALG_H

#include <QObject>
#include <QThread>
#include <QSharedPointer>
#include "packetSSL.h"
//#include "robocup_ssl_client.h"
#include <iostream>
#include "mlData.h"

using namespace std;

//main algorithm worker
struct MainAlgWorker : public QObject
{
    Q_OBJECT
public:
    MainAlgWorker(){}

public slots:
    void start(){
        shutdowncomp = false;
        cout << "MainAlg worker start" << endl;
        init();
    }

    void stop(){
        shutdowncomp = true;
    }

    void run();

    void run_matlab();
    void stop_matlab();
signals:


private:

    void init();

//    RoboCupSSLClient client;
//    SSL_WrapperPacket packet;
    char m_buffer[256];

    MlData fmldata;
    bool fmtlab;
    bool shutdowncomp;
};


//class main algorithm
class MainAlg : public QObject
{
    Q_OBJECT
public:
    MainAlgWorker worker;
    QThread thread;

    explicit MainAlg(){}
    ~MainAlg() { stop(); thread.terminate(); thread.wait(100); }

    void init(){
        worker.moveToThread(&thread);
        cout << "init mainAlg ok" << endl;
        connect(this, SIGNAL(wstart()), &worker, SLOT(start()));
        connect(this, SIGNAL(wstop()), &worker, SLOT(stop()));
        connect(&thread, SIGNAL(finished()), &worker, SLOT(deleteLater()));
    }

    void start() {
        thread.start();
//        cout << "thread start" << endl;
        emit wstart();
    }

    void stop() { emit wstop();}

signals:
    void wstart();
    void wstop();

public slots:

};

#endif // MAINALG_H
