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

    sceneViewWorker(){}

public slots:
    void start(){
        shutdownview = false;
        cout << "sceneVie worker start" << endl;
        run();
    }

    void stop(){
        shutdownview = true;
    }

    void repaintScene();
signals:
    void updateView();

private:

    void run();
    bool shutdownview;
};


struct sceneView: public QObject
{
    Q_OBJECT

public:
    sceneViewWorker worker;
    QThread thread;

    sceneView(){}
    ~sceneView() { stop(); thread.terminate(); thread.wait(100); }

    void init(){
        worker.moveToThread(&thread);
        cout << "sceneView init ok" << endl;
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

};

#endif // SCENEVIEW_H
