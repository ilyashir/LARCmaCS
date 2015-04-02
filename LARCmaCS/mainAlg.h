#ifndef MAINALG_H
#define MAINALG_H

#include <QObject>
#include <QThread>
#include <QSharedPointer>
#include "packetSSL.h"
#include <iostream>
#include "mlData.h"
//#include "BTtransmitter.h"

using namespace std;
#include <time.h>       /* clock_t, clock(), CLOCKS_PER_SEC */

struct MainAlgWorker : public QObject
{
    Q_OBJECT
    clock_t t,st,mt,maxt;
    int Time_count;
public:
    explicit MainAlgWorker(){st=0; mt=clock(); Time_count=0;}

signals:
    void sendToConnector(double *ruleArray);
    void sendToBTtransmitter(char * message);
    void ForvardReciver();
    void StatusMessage(QString message);

public slots:
    void start()
    {
        shutdowncomp = false;
        cout << "MainAlg worker start" << endl;
        init();
    }

    void stop() { shutdowncomp = true; }

    void run(PacketSSL packetssl);

    void run_matlab();
    void stop_matlab();

private:
    void init();

    char m_buffer[256]; // matlab buffer
    MlData fmldata;
    bool fmtlab;
    bool shutdowncomp;
};

struct MainAlg : public QObject
{
    Q_OBJECT

public:
    MainAlgWorker worker;
    QThread thread;

    explicit MainAlg(){}
    ~MainAlg()
    {
        stop();
        thread.terminate();
        thread.wait(100);
    }

    void init()
    {
        worker.moveToThread(&thread);
        cout << "Init mainAlg ok" << endl;
        connect(this, SIGNAL(wstart()), &worker, SLOT(start()));
        connect(this, SIGNAL(wstop()), &worker, SLOT(stop()));
        connect(&thread, SIGNAL(finished()), &worker, SLOT(deleteLater()));
    }

    void start()
    {
        thread.start();
        cout << "Thread start" << endl;
        emit wstart();
    }

    void stop() { emit wstop(); }

signals:
    void wstart();
    void wstop();

public slots:

};

#endif // MAINALG_H
