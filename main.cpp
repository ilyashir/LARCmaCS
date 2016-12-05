#include "larcmacs.h"
#include <qt4/QtGui/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LARCmaCS w;
    w.show();

    return a.exec();
}
