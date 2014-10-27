#include "camerasettings.h"
#include <QDebug>

CameraSettings::CameraSettings()
{

   // vi=v;
  //  vi.setupDevice(index,640,480);
    //vi=v;
 //   this->setWindowTitle(QString::number(idx));
    slider1 = new QSlider(this);
    //slider1->setInvertedAppearance(1);
    //slider1->setInvertedControls(1);
    slider1->setOrientation(Qt::Orientation::Horizontal);
    slider1->setMinimum(-9);
    slider1->setMaximum(0);
   // slider1->setSingleStep();
    connect(slider1,SIGNAL(valueChanged(int)),this,SLOT(slider1changed(int)));
    //vi = v;
   // v.
}

void CameraSettings::slider1changed(int val)
{
    //vi.setVideoSettingCamera(index,vi.propExposure,val);
    qDebug()<<"Before";
    vi.setVideoSettingCamera(index, 4, val, 2);
    qDebug()<<"After";
    //qDebug()<<vi.setVideoSettingCamera(index, 4, (float)val/10, 2);
//    long min,max,SteppingDelta,currentValue, flags,defaultValue;
//    qDebug()<<currentValue;
//    vi.getVideoSettingCamera(index, 4, min, max, SteppingDelta, currentValue, flags, defaultValue);
//    qDebug()<<currentValue;
    //vi.restartDevice(index);
}

int CameraSettings::getSize()
{
    return vi.getSize(index);
}
