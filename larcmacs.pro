#-------------------------------------------------
#
# Project created by QtCreator 2016-12-02T01:05:35
#
#-------------------------------------------------

CONFIG += qt thread
CONFIG += console
#CONFIG += c++11
CONFIG -= warn_off
CONFIG += debug_and_release build_al

SHARED_DIR = ../src/shared
LIST_DIR = ../build

#where to place built objects
OBJECTS_DIR = ../build/LARCmaCS/obj$${SUFFIX_STR}

#where to place temporary moc sources
MOC_DIR = ../build/LARCmaCS/moc

#where to place auto-generated UI files
UI_DIR = ../build/LARCmaCS/ui

#where to place intermediate resource files
RCC_DIR = ../build/LARCmaCS/resources

unix {
  DEFINES += UNIX
  DEFINES += LINUX
  DEFINES += _GNU_SOURCE

  #profiling:
  #CONFIG += debug
  #QMAKE_CFLAGS+=-pg
  #QMAKE_CXXFLAGS+=-pg
  #QMAKE_LFLAGS+=-pg

  #build the protocol buffer code
  #message(Compiling Protocol Buffer CPP Sources from .proto Files...)
#  system(protoc --cpp_out=$${SHARED_DIR}/cpp --proto_path=$${SHARED_DIR}/ $${SHARED_DIR}/proto/*.proto):HAS_PROTOBUF = TRUE

#  isEmpty(HAS_PROTOBUF) {
#    error(Failure building proto-buffer sources. Is the google protocol buffer compiler 'protoc' installed?)
#  }

  #messages defined through google protocol buffers (as compiled by protoc)
  LIST = $$system(ls $${LIST_DIR}/*.pb.cc)
  for(item, LIST) {
    SOURCES += $${item}
  }

  LIST = $$system(ls $${LIST_DIR}/*.pb.h)
  for(item, LIST) {
    HEADERS += $${item}
  }
}


#add google protocol buffers
LIBS += -lprotobuf

#add opengl support
LIBS += -lGL -lGLU

QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = larcmacs
TEMPLATE = app

INCLUDEPATH += \
  $${LIST_DIR} \
  $${SHARED_DIR}/net \
  $${SHARED_DIR}/proto \
  $${SHARED_DIR}/util \
  $${SHARED_DIR}/rfprotocol \
#  $${MATLAB_DIR}/include \
  $${SHARED_DIR}/vartypes

SOURCES += main.cpp\
        larcmacs.cpp \
    $${SHARED_DIR}/net/netraw.cpp \
    $${SHARED_DIR}/net/robocup_ssl_client.cpp \
    $${SHARED_DIR}/util/field.cpp \
    $${SHARED_DIR}/util/field_default_constants.cpp \
    receiver.cpp

HEADERS  += larcmacs.h \
    receiver.h \
    packetSSL.h \
    $${SHARED_DIR}/net/netraw.h \
    $${SHARED_DIR}/net/robocup_ssl_client.h \
    $${SHARED_DIR}/util/timer.h \
    $${SHARED_DIR}/util/field.h \
    $${SHARED_DIR}/util/field_default_constants.h

FORMS    += larcmacs.ui







