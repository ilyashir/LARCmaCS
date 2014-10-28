#include "camerasettings.h"
#include <QDebug>

CameraSettings::CameraSettings()
{
    this->setGeometry(100,100,400,250);
    qDebug()<<"prop"<<vi.propSharpness;
    QLabel* lb1 = new QLabel(this);
    lb1->setText("Exposure");
    lb1->setGeometry(10,10,50,25);
    slider1 = new QSlider(this);

    slider1->setOrientation(Qt::Orientation::Horizontal);
    slider1->setMinimum(-9);
    slider1->setMaximum(0);
    slider1->setGeometry(10,lb1->geometry().y()+lb1->geometry().height(),300,40);
    //slider1->setSizePolicy(QSizePolicy::);
    //slider1->setInvertedControls(1);
    slider1->setInvertedAppearance(1);
    //slider1->set

    connect(slider1,SIGNAL(valueChanged(int)),this,SLOT(slider1changed(int)));


    QLabel* lb2 = new QLabel(this);
    lb2->setText("Gain");
    lb2->setGeometry(10,slider1->geometry().y()+slider1->geometry().height(),50,25);

    slider2 = new QSlider(this);

    slider2->setOrientation(Qt::Orientation::Horizontal);
    slider2->setMinimum(0);
    slider2->setMaximum(255);
    slider2->setGeometry(10,lb2->geometry().y()+lb2->geometry().height(),300,40);

    QLabel* lb3 = new QLabel(this);
    lb3->setText("White Balance");
    lb3->setGeometry(10,slider2->geometry().y()+slider2->geometry().height(),50,25);

    slider3 = new QSlider(this);

    slider3->setOrientation(Qt::Orientation::Horizontal);
    slider3->setMinimum(0);
    slider3->setMaximum(100);
   // slider3->setSingleStep(1000);

    slider3->setGeometry(10,lb3->geometry().y()+lb3->geometry().height(),300,40);


    connect(slider3,SIGNAL(valueChanged(int)),this,SLOT(slider3changed(int)));

}

void CameraSettings::slider1changed(int val)
{
    //vi.setVideoSettingCamera(index,vi.propExposure,val);
    //qDebug()<<"Before";
    qDebug()<<val;
    vi.setVideoSettingCamera(index, vi.propExposure, val, 2);
    //qDebug()<<"After";
    //qDebug()<<vi.setVideoSettingCamera(index, 4, (float)val/10, 2);
//    long min,max,SteppingDelta,currentValue, flags,defaultValue;
//    qDebug()<<currentValue;
//    vi.getVideoSettingCamera(index, 4, min, max, SteppingDelta, currentValue, flags, defaultValue);
//    qDebug()<<currentValue;
    //vi.restartDevice(index);
}

void CameraSettings::slider2changed(int val)
{
    //vi.setVideoSettingCamera(index,vi.propExposure,val);
   // qDebug()<<"Before";
    //vi.setVideoSettingCameraPct(index, vi.propGain, (float)val/10.0, 2);
    //vi.setVideoSettingCamera(index,vi.propGain,val,2);
    qDebug()<<val;
    vi.setVideoSettingFilter(index,vi.propGain,val,2);
    //qDebug()<<"After";
    //qDebug()<<vi.setVideoSettingCamera(index, 4, (float)val/10, 2);
//    long min,max,SteppingDelta,currentValue, flags,defaultValue;
//    qDebug()<<currentValue;
//    vi.getVideoSettingCamera(index, 4, min, max, SteppingDelta, currentValue, flags, defaultValue);
//    qDebug()<<currentValue;
    //vi.restartDevice(index);
}

void CameraSettings::slider3changed(int val)
{
    //vi.setVideoSettingCamera(index,vi.propExposure,val);
   // qDebug()<<"Before";
    //vi.setVideoSettingCameraPct(index, vi.propGain, (float)val/10.0, 2);
    //vi.setVideoSettingCamera(index,vi.propGain,val,2);
    qDebug()<<val;
    vi.setVideoSettingFilter(index,vi.propWhiteBalance,val*100,2);
    //qDebug()<<"After";
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
