#include "sceneView.h"
#include <iostream>

#include <QtWidgets/QApplication>

using namespace std;

void sceneViewWorker::run(){

    while(!shutdownview){
//        cout << "signal updateView" << endl;
        emit updateView();
        QApplication::processEvents();
        Sleep(1);
    }

}

void sceneViewWorker::repaintScene(PacketSSL packetssl){
   // cout << "yep! repain" << endl;
    emit updateRobots();
    QApplication::processEvents();
}
