#include "captureopencv.h"

#include <opencv/cv.h>
#include <opencv/cxcore.h>

#include "timer.h"
#include "image.h"

#include <QtCore/QDebug>


CaptureOpenCv::CaptureOpenCv(VarList * _settings)
    : CaptureInterface(_settings)
{
    mCaptureSettings = new VarList("Capture Settings");
    settings->addChild(mCaptureSettings);

    mIndex = new VarString("Camera index");
    mCaptureSettings->addChild(mIndex);

    test = new CameraSettings();
	printf("We work with OpenCv, init USB-cam\n");
}

CaptureOpenCv::~CaptureOpenCv()
{
}

RawImage CaptureOpenCv::getFrame()
{
    mutex.lock();
    //RawImage result;
    result.setTime(0.0);
//    int width = mVideoInput.getWidth(index);
//    int height = mVideoInput.getHeight(index);
//    bool success = mVideoInput.getPixels(index, mBuffer, false, true);

    int width = test->vi.getWidth(index);
    int height = test->vi.getHeight(index);
    bool success = test->vi.getPixels(index, mBuffer, false, true);


    if( success )
    {
         cv::Mat image( height, width, CV_8UC3, mBuffer );

        result.allocate(COLOR_RGB8, width, height);
        rgbImage img;
        img.fromRawImage(result);
        int const widthStep = image.step;
        int const channels = 3;
        for (int x = 0 ; x < width; x++) {
            for (int y = 0 ; y < height; y++) {
              rgb color2;
              //color2.r = mBuffer[width * y + 3 * x + 2];
              //color2.g = mBuffer[width * y + 3 * x + 1];
              //color2.b = mBuffer[width * y + 3 * x];
                color2.r = image.data[widthStep * y + channels * x + 2];
                color2.g = image.data[widthStep * y + channels * x + 1];
                color2.b = image.data[widthStep * y + channels * x];
              img.setPixel(x, y, color2);
          }
        }

        result.setWidth(width);
        result.setHeight(height);

        tval tv;
        gettimeofday(&tv,NULL);
        result.setTime((double)tv.tv_sec + tv.tv_usec*(1.0E-6));

    }
    else
    {
        qDebug()<<"VideoInput error!";
        result.allocate(COLOR_RGB8, 640, 480);
    }
//    if (!mCapture.grab()) {
//        qDebug() <<  "OpenCV Error: Failed to capture from camera" << mIndex;
//        mCapture.release();
//        result.allocate(COLOR_RGB8, 640, 480);
//    } else {
//        cv::Mat image;
//        mCapture.retrieve(image);

//        int const widthStep = image.step;
//        int const height = image.rows;
//        int const width = image.cols;
//        int const channels = 3;

//        result.allocate(COLOR_RGB8, width, height);

//        rgbImage img;
//        img.fromRawImage(result);

//        for (int x = 0 ; x < width; x++) {
//            for (int y = 0 ; y < height; y++) {
//              rgb color2;
//              color2.r = image.data[widthStep * y + channels * x + 2];
//              color2.g = image.data[widthStep * y + channels * x + 1];
//              color2.b = image.data[widthStep * y + channels * x];
//              img.setPixel(x, y, color2);
//          }
//        }

//        result.setWidth(width);
//        result.setHeight(height);

//        tval tv;
//        gettimeofday(&tv,NULL);
//        result.setTime((double)tv.tv_sec + tv.tv_usec*(1.0E-6));
//    }
    mutex.unlock();
    return result;
}

bool CaptureOpenCv::isCapturing()
{
  // return  mVideoInput.isDeviceSetup(index);
    return  test->vi.isDeviceSetup(index);
   // return mCapture.isOpened();
}

void CaptureOpenCv::releaseFrame()
{
}

bool CaptureOpenCv::startCapture()
{
    std::string const indexStr = mIndex->getString();
    //mCapture.

    bool err = false;
   // int const index = QString(indexStr.c_str()).toInt(&err);
    index = QString(indexStr.c_str()).toInt(&err);
    //VIDEOINPUT
   // bool res=mVideoInput.setupDevice(index, 640, 480);//, VI_USB);
//    int mSize = mVideoInput.getSize(index);
//    mBuffer = new unsigned char[mSize];

//    if (mVideoInput.setVideoSettingCamera(index, 4, -7, 2))
//    {
//        qDebug()<<"Exposure ok!";
//        //mVideoInput.setupDevice(index, 640, 480);
//       // mVideoInput.restartDevice(index);
//    }
   //qDebug()<<"VIDEOINPUT YO!!!!";
   // mVideoInput.showSettingsWindow(index);

    //CameraSettings * test = new CameraSettings(index);
    //test->setWindowTitle(QString::number(index));
    bool res=test->vi.setupDevice(index, 640, 480);
   // test = new CameraSettings();
    mBuffer = new unsigned char[test->getSize()];
    test->show();
    //mVideoInput = test->vi;
    //mVideoInput.

//    qDebug() << "Starting capture from" << index;

//    if (err)
//        mCapture.open(index);

//    qDebug() << "Success: " << mCapture.isOpened();
//    return mCapture.isOpened();
    return res;
}

bool CaptureOpenCv::stopCapture()
{
    //mCapture.release();
    mVideoInput.stopDevice(index);
    delete[] mBuffer;
    return true;
}

string CaptureOpenCv::getCaptureMethodName() const
{
    return "OpenCV";
}
