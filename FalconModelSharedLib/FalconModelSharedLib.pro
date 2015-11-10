#-------------------------------------------------
#
# Project created by QtCreator 2014-08-25T03:24:26
#
#-------------------------------------------------

QT       += widgets opengl xml xmlpatterns

QT       -= gui

TARGET = FalconModelSharedLib
TEMPLATE = lib

DEFINES += FALCONMODELSHAREDLIB_LIBRARY

SOURCES += falconmodelsharedlib.cpp \
    src_core/component.cpp \
    src_core/instruction.cpp \
    src_core/instructionlist.cpp \
    src_core/mesh.cpp \
    src_core/model.cpp \
    src_core/subcomponentlist.cpp \
    src_handlers/glhandler.cpp \
    src_level/level.cpp \
    src_level/levelobject.cpp

HEADERS += falconmodelsharedlib.h\
        falconmodelsharedlib_global.h \
    src_core/component.h \
    src_core/core.h \
    src_core/instruction.h \
    src_core/instructionlist.h \
    src_core/mesh.h \
    src_core/model.h \
    src_core/subcomponentlist.h \
    src_handlers/glhandler.h \
    src_level/level.h \
    src_level/levelobject.h \
    src_handlers/glut.h \
    src_core/glut.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}



OTHER_FILES += \
    GL/glut32.lib



win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../libQGLViewer-2.3.17/QGLViewer/release/ -lQGLViewer2
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../libQGLViewer-2.3.17/QGLViewer/debug/ -lQGLViewer2

INCLUDEPATH += $$PWD/../../libQGLViewer-2.3.17/QGLViewer/release
DEPENDPATH += $$PWD/../../libQGLViewer-2.3.17/QGLViewer/release
INCLUDEPATH += $$PWD/../../libQGLViewer-2.3.17/QGLViewer
DEPENDPATH += $$PWD/../../libQGLViewer-2.3.17/QGLViewer


