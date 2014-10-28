#ifndef CAMERASETTINGS_H
#define CAMERASETTINGS_H

#include <QWidget>
#include "videoInput.h"
#include <QSlider>
#include <QLabel>

class CameraSettings : public QWidget
{
    Q_OBJECT
public:
    CameraSettings();
    videoInput vi;
    int index;
    QSlider * slider1;
    QSlider * slider2;
    QSlider * slider3;
    int getSize();

public slots:
    void slider1changed(int val);
    void slider2changed(int val);
    void slider3changed(int val);
};

#endif // CAMERASETTINGS_H
