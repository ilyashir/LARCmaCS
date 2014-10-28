#pragma once

#include <opencv/highgui.h>

#include "captureinterface.h"
#include "videoInput.h"
#include "camerasettings.h"

class CaptureOpenCv : public CaptureInterface
{
public:
    CaptureOpenCv(VarList * _settings=0);
    virtual ~CaptureOpenCv();

    virtual RawImage getFrame();
    virtual bool isCapturing();
    virtual void releaseFrame();
    virtual bool startCapture();
    virtual bool stopCapture();
    virtual string getCaptureMethodName() const;

private:
	RawImage result;
    cv::VideoCapture mCapture;
    VarList *mCaptureSettings;
    VarString *mIndex;
    QMutex mutex;
    CameraSettings * test;

    unsigned char * mBuffer;
    int index;

    //VIDEOINPUT
    videoInput mVideoInput;
};
