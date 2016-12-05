#ifndef LARCMACS_H
#define LARCMACS_H

#include <QtGui/QWidget>
#include <QtCore/QDebug>
#include "receiver.h"

namespace Ui {
    class LARCmaCS;
}

class LARCmaCS : public QWidget
{
    Q_OBJECT
protected:
    Receiver receiver;

public:
    explicit LARCmaCS(QWidget *parent = 0);
    ~LARCmaCS();

private:
    Ui::LARCmaCS *ui;
};

#endif // LARCMACS_H
