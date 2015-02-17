#-------------------------------------------------
#
# Project created
#
#-------------------------------------------------

#read the global configuration file
include( ../config.pro.inc )

#qextserialport for  BTtransmitter
include(../LARCmaCS/src/qextserialport.pri)

#where to place built objects
OBJECTS_DIR = ../build/LARCmaCS/obj$${SUFFIX_STR}

#where to place temporary moc sources
MOC_DIR = ../build/LARCmaCS/moc

#where to place auto-generated UI files
UI_DIR = ../build/LARCmaCS/ui

#where to place intermediate resource files
RCC_DIR = ../build/LARCmaCS/resources

unix {
  #add google protocol buffers
  LIBS += -lprotobuf

  #add opengl support
  LIBS += -lGL -lGLU
}

win32 {
  #add libs
  LIBS += -L$$PWD/../lib/ -llibprotobuf$${SUFFIX_STR} \
          -lws2_32

  LIBS += -L$${MATLAB_DIR}/lib/win32/microsoft/ -llibeng \
          -L$${MATLAB_DIR}/lib/win32/microsoft/ -llibmat \
          -L$${MATLAB_DIR}/lib/win32/microsoft/ -llibmx
}

QT       += core gui
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = LARCmaCS
TEMPLATE = app

INCLUDEPATH +='C:\Program Files (x86)\MATLAB\R2014a\bin\win32'

#directories of sources of the vision client

INCLUDEPATH += \
  $${SHARED_DIR}/net \
  $${SHARED_DIR}/proto/cpp \
  $${SHARED_DIR}/util \
  $${SHARED_DIR}/rfprotocol \
  $${MATLAB_DIR}/include \
  $${SHARED_DIR}/vartypes

SOURCES += main.cpp\
  $${SHARED_DIR}/net/netraw.cpp \
  $${SHARED_DIR}/net/robocup_ssl_client.cpp \
        larcmacs.cpp \
    fieldScene.cpp \
    sceneView.cpp \
    receiver.cpp \
    mainAlg.cpp \
    mlData.cpp \
    connector.cpp \
    BTtransmitter.cpp

HEADERS  += \
  $${SHARED_DIR}/net/netraw.h \
  $${SHARED_DIR}/net/robocup_ssl_client.h \
  $${SHARED_DIR}/net/Pipe.h \
  $${SHARED_DIR}/util/timer.h \
  $${SHARED_DIR}/util/field.h \
  $${SHARED_DIR}/util/field_default_constants.h \
  $${SHARED_DIR}/rfprotocol/rfprotocol.h \
        larcmacs.h \
    fieldScene.h \
    sceneView.h \
    packetSSL.h \
    receiver.h \
    mainAlg.h \
    mlData.h \
    connector.h \
    BTtransmitter.h

FORMS    += larcmacs.ui
