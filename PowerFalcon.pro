TEMPLATE = subdirs

SUBDIRS += \
    FalconObjectMaker \
    FalconModelSharedLib \
    FalconWarMaker \
    FalconGame

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../libQGLViewer-2.3.17/QGLViewer/release/ -lQGLViewer2
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../libQGLViewer-2.3.17/QGLViewer/debug/ -lQGLViewer2

INCLUDEPATH += $$PWD/../libQGLViewer-2.3.17/QGLViewer/release
DEPENDPATH += $$PWD/../libQGLViewer-2.3.17/QGLViewer/release

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../PowerFalcon-build/FalconModelSharedLib/release/ -lFalconModelSharedLib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../PowerFalcon-build/FalconModelSharedLib/debug/ -lFalconModelSharedLib

INCLUDEPATH += $$PWD/../PowerFalcon-build/FalconModelSharedLib/release
DEPENDPATH += $$PWD/../PowerFalcon-build/FalconModelSharedLib/release

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/FalconWarZoneSharedLibrary/release/ -lFalconWarZoneSharedLibrary
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/FalconWarZoneSharedLibrary/debug/ -lFalconWarZoneSharedLibrary

INCLUDEPATH += $$PWD/FalconWarZoneSharedLibrary
DEPENDPATH += $$PWD/FalconWarZoneSharedLibrary
