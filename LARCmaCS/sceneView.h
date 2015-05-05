#ifndef SCENEVIEW_H
#define SCENEVIEW_H

#include <QObject>
#include <QThread>
#include <QSharedPointer>
#include "packetSSL.h"
#include "fieldScene.h"

struct sceneViewWorker: public QObject
{
    Q_OBJECT

public:
    explicit sceneViewWorker(){}

public slots:
    void start()
    {
        shutdownview = false;
        cout << "sceneView worker started" << endl;
        run();
    }

    void stop() { shutdownview = true; }
    //void repaintScene(PacketSSL packetssl);

signals:
    void updateView();    
//    void updateRobots();

private:
    void run();
    bool shutdownview;
};

struct sceneView: QObject
{
    Q_OBJECT

public:
    sceneViewWorker worker;
    QThread thread;

    explicit sceneView(){}
    ~sceneView() {
        stop();
        thread.wait(100);
        thread.terminate();
        thread.wait(100);
    }

    void init()
    {
        worker.moveToThread(&thread);
        cout << "sceneView init ok" << endl;
        connect(this, SIGNAL(wstart()), &worker, SLOT(start()));
        connect(this, SIGNAL(wstop()), &worker, SLOT(stop()));
        connect(&thread, SIGNAL(finished()), &worker, SLOT(deleteLater()));
    }

    void start()
    {
        thread.start();
        cout << "Scene view thread started" << endl;
        emit wstart();
    }

    void stop() { emit wstop(); }

signals:
    void wstart();
    void wstop();

};

#endif // SCENEVIEW_H
