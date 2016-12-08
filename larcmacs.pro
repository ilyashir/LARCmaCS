#-------------------------------------------------
#
# Project created by QtCreator 2016-12-02T01:05:35
#
#-------------------------------------------------

CONFIG += qt thread
CONFIG += console
CONFIG += c++11
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
    receiver.cpp \
    ../src/shared/util/helpers.cpp \
    ../src/shared/vartypes/primitives/VarBlob.cpp \
    ../src/shared/vartypes/primitives/VarBool.cpp \
    ../src/shared/vartypes/primitives/VarBoolVal.cpp \
    ../src/shared/vartypes/primitives/VarDouble.cpp \
    ../src/shared/vartypes/primitives/VarDoubleVal.cpp \
    ../src/shared/vartypes/primitives/VarExternal.cpp \
    ../src/shared/vartypes/primitives/VarInt.cpp \
    ../src/shared/vartypes/primitives/VarIntVal.cpp \
    ../src/shared/vartypes/primitives/VarList.cpp \
    ../src/shared/vartypes/primitives/VarProtoBuffer.cpp \
    ../src/shared/vartypes/primitives/VarProtoBufferVal.cpp \
    ../src/shared/vartypes/primitives/VarQWidget.cpp \
    ../src/shared/vartypes/primitives/VarSelection.cpp \
    ../src/shared/vartypes/primitives/VarString.cpp \
    ../src/shared/vartypes/primitives/VarStringEnum.cpp \
    ../src/shared/vartypes/primitives/VarStringVal.cpp \
    ../src/shared/vartypes/primitives/VarTrigger.cpp \
    ../src/shared/vartypes/primitives/VarType.cpp \
    ../src/shared/vartypes/primitives/VarVal.cpp \
    ../src/shared/vartypes/gui/VarItem.cpp \
    ../src/shared/vartypes/gui/VarItemDelegate.cpp \
    ../src/shared/vartypes/gui/VarTreeModel.cpp \
    ../src/shared/vartypes/gui/VarTreeView.cpp \
    ../src/shared/vartypes/gui/VarTreeViewOptions.cpp \
    ../src/shared/vartypes/xml/xmlParser.cpp \
    ../src/shared/vartypes/VarBase64.cpp \
    ../src/shared/vartypes/VarNotifier.cpp \
    ../src/shared/vartypes/VarTypes.cpp \
    ../src/shared/vartypes/VarTypesFactory.cpp \
    ../src/shared/vartypes/VarTypesInstance.cpp \
    ../src/shared/vartypes/VarXML.cpp

HEADERS  += larcmacs.h \
    receiver.h \
    packetSSL.h \
    $${SHARED_DIR}/net/netraw.h \
    $${SHARED_DIR}/net/robocup_ssl_client.h \
    $${SHARED_DIR}/util/timer.h \
    $${SHARED_DIR}/util/field.h \
    $${SHARED_DIR}/util/field_default_constants.h \
    ../src/shared/util/helpers.h \
    ../src/shared/vartypes/primitives/VarVal.h \
    ../src/shared/gl/glcamera.h \
    ../src/shared/gl/globject.h \
    ../src/shared/net/robocup_ssl_server.h \
    ../src/shared/proto/cpp/messages_robocup_ssl_detection.pb.h \
    ../src/shared/proto/cpp/messages_robocup_ssl_geometry.pb.h \
    ../src/shared/proto/cpp/messages_robocup_ssl_geometry_legacy.pb.h \
    ../src/shared/proto/cpp/messages_robocup_ssl_refbox_log.pb.h \
    ../src/shared/proto/cpp/messages_robocup_ssl_wrapper.pb.h \
    ../src/shared/proto/cpp/messages_robocup_ssl_wrapper_legacy.pb.h \
    ../src/shared/util/affinity_manager.h \
    ../src/shared/util/bbox.h \
    ../src/shared/util/bitflags.h \
    ../src/shared/util/camera_calibration.h \
    ../src/shared/util/colors.h \
    ../src/shared/util/conversions.h \
    ../src/shared/util/field_filter.h \
    ../src/shared/util/font.h \
    ../src/shared/util/framecounter.h \
    ../src/shared/util/framelimiter.h \
    ../src/shared/util/geomalgo.h \
    ../src/shared/util/geometry.h \
    ../src/shared/util/global_random.h \
    ../src/shared/util/gvector.h \
    ../src/shared/util/image.h \
    ../src/shared/util/image_interface.h \
    ../src/shared/util/image_io.h \
    ../src/shared/util/lut3d.h \
    ../src/shared/util/nkdtree.h \
    ../src/shared/util/nvector.h \
    ../src/shared/util/pixelloc.h \
    ../src/shared/util/pose.h \
    ../src/shared/util/qgetopt.h \
    ../src/shared/util/quaternion.h \
    ../src/shared/util/random.h \
    ../src/shared/util/range.h \
    ../src/shared/util/rawimage.h \
    ../src/shared/util/ringbuffer.h \
    ../src/shared/util/sobel.h \
    ../src/shared/util/texture.h \
    ../src/shared/util/util.h \
    ../src/shared/util/vis_util.h \
    ../src/shared/util/zoom.h \
    ../src/shared/vartypes/gui/VarItem.h \
    ../src/shared/vartypes/gui/VarItemDelegate.h \
    ../src/shared/vartypes/gui/VarTreeModel.h \
    ../src/shared/vartypes/gui/VarTreeView.h \
    ../src/shared/vartypes/gui/VarTreeViewOptions.h \
    ../src/shared/vartypes/primitives/VarBlob.h \
    ../src/shared/vartypes/primitives/VarBool.h \
    ../src/shared/vartypes/primitives/VarBoolVal.h \
    ../src/shared/vartypes/primitives/VarDouble.h \
    ../src/shared/vartypes/primitives/VarDoubleVal.h \
    ../src/shared/vartypes/primitives/VarExternal.h \
    ../src/shared/vartypes/primitives/VarInt.h \
    ../src/shared/vartypes/primitives/VarIntVal.h \
    ../src/shared/vartypes/primitives/VarList.h \
    ../src/shared/vartypes/primitives/VarProtoBuffer.h \
    ../src/shared/vartypes/primitives/VarProtoBufferVal.h \
    ../src/shared/vartypes/primitives/VarQWidget.h \
    ../src/shared/vartypes/primitives/VarSelection.h \
    ../src/shared/vartypes/primitives/VarString.h \
    ../src/shared/vartypes/primitives/VarStringEnum.h \
    ../src/shared/vartypes/primitives/VarStringVal.h \
    ../src/shared/vartypes/primitives/VarTrigger.h \
    ../src/shared/vartypes/primitives/VarType.h \
    ../src/shared/vartypes/xml/xmlParser.h \
    ../src/shared/vartypes/VarBase64.h \
    ../src/shared/vartypes/VarNotifier.h \
    ../src/shared/vartypes/VarTypes.h \
    ../src/shared/vartypes/VarTypesFactory.h \
    ../src/shared/vartypes/VarTypesInstance.h \
    ../src/shared/vartypes/VarXML.h

FORMS    += larcmacs.ui







