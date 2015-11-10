#-------------------------------------------------
#
# Project created by QtCreator 2014-08-31T20:11:05
#
#-------------------------------------------------

QT       += widgets opengl xml xmlpatterns

QT       -= gui

TARGET = FalconWarZoneSharedLibrary
TEMPLATE = lib

DEFINES += FALCONWARZONESHAREDLIBRARY_LIBRARY

SOURCES += falconwarzonesharedlibrary.cpp \
    src_level/level.cpp \
    src_level/levelobject.cpp

HEADERS += falconwarzonesharedlibrary.h\
        falconwarzonesharedlibrary_global.h \
    falconmodelsharedlib_global.h \
    src_level/level.h \
    src_level/levelobject.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../FalconModelSharedLib/release/ -lFalconModelSharedLib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../FalconModelSharedLib/debug/ -lFalconModelSharedLib

INCLUDEPATH += $$PWD/../FalconModelSharedLib
DEPENDPATH += $$PWD/../FalconModelSharedLib

win32: LIBS += -L$$PWD/GL/ -lglut32

INCLUDEPATH += $$PWD/GL
DEPENDPATH += $$PWD/GL

win32: LIBS += -L$$PWD/GL/ -lQGLViewer2

INCLUDEPATH += $$PWD/GL
DEPENDPATH += $$PWD/GL
