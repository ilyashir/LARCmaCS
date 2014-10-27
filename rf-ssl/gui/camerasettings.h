#ifndef CAMERASETTINGS_H
#define CAMERASETTINGS_H

#include <QWidget>
#include "videoInput.h"
#include <QSlider>

class CameraSettings : public QWidget
{
    Q_OBJECT
public:
    CameraSettings();
    videoInput vi;
    int index;
    QSlider * slider1;
    int getSize();

public slots:
    void slider1changed(int val);
};

#endif // CAMERASETTINGS_H
