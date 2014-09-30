#include "larcmacs.h"
#include <QApplication>
#include <QTcpServer>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    LARCmaCS w;
    w.show();

    return a.exec();
}
