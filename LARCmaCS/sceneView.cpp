#include "sceneView.h"
#include <iostream>

#include <QtWidgets/QApplication>

using namespace std;

void sceneViewWorker::run(){

    while(!shutdownview){
//        cout << "signal updateView" << endl;
        emit updateView();
        QApplication::processEvents();
    }

}

void sceneViewWorker::repaintScene(){
    cout << "yep! repain" << endl;
}
