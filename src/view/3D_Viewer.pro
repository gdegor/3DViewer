QT += core gui widgets opengl openglwidgets
include(../../QTGifimage-master/src/gifimage/qtgifimage.pri)

TARGET = 3D_Viewer
TEMPLATE = app

SOURCES += main.cc \
    ../model/affin.cc \
    ../model/model.cc \
    mainwindow.cc

SOURCES += \
    mainwidget.cc \
    geometryengine.cc

HEADERS += \
    ../controller/controller.h \
    ../model/affin.h \
    ../model/model.h \
    facade.h \
    mainwidget.h \
    geometryengine.h \
    mainwindow.h

RESOURCES += \
    shaders.qrc

# install
target.path = $$[QT_INSTALL_EXAMPLES]/opengl/cube
INSTALLS += target

DISTFILES += \
    ../QtGifImage-master/src/gifimage/qtgifimage.pri \

FORMS += \
    mainwindow.ui

ICON += \
    ../../logo/icon.icns
