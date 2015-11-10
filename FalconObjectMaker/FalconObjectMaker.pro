#-------------------------------------------------
#
# Project created by QtCreator 2014-08-15T01:17:16
#
#-------------------------------------------------

QT       += core gui opengl xml xmlpatterns

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = FalconObjectMaker
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    src_gfx/graphicsview.cpp \
    src_gfx/graphicsscene.cpp \
    src_menu/menuhandler.cpp \
    src_gfx/glviewer.cpp \
    src_xml/xmlbuilder.cpp \
    src_xml/qobjectxmlmodel.cpp \
    src_ui/instructionlistedit.cpp \
    src_ui/modeltree.cpp \
    src_ui/subcomponentlistedit.cpp


HEADERS  += mainwindow.h \
    src_gfx/graphicsview.h \
    src_gfx/gfx.h \
    src_gfx/graphicsscene.h \
    src_menu/menuhandler.h \
    src_gfx/glviewer.h \
    src_xml/xmlbuilder.h \
    src_xml/qobjectxmlmodel.h \
    falconmodelsharedlib_global.h \
    src_ui/instructionlistedit.h \
    src_ui/modeltree.h \
    src_ui/subcomponentlistedit.h


MOC_DIR += ./GeneratedFiles/moc
OBJECTS_DIR += ./GeneratedFiles/obj
UI_DIR += ./GeneratedFiles/ui
RCC_DIR += ./GeneratedFiles/rcc

win32: LIBS += -L$$PWD/GL/ -lglut32

INCLUDEPATH += $$PWD/GL
DEPENDPATH += $$PWD/GL

OTHER_FILES +=

win32: LIBS += -L$$PWD/GL/ -lQGLViewer2

INCLUDEPATH += $$PWD/GL
DEPENDPATH += $$PWD/GL

SUBDIRS += \
    GL/QGLViewer.pro

FORMS += \
    GL/ImageInterface.ui \
    GL/VRenderInterface.ui \
    src_ui/modeltree.ui \
    src_ui/instructionlistedit.ui \
    src_ui/subcomponentlistedit.ui

RESOURCES += \
    resources.qrc
if(contains(QT, core)) {
    Qt5Core.commands = copy /Y %QTDIR%\\bin\\Qt5Core.dll release
    Qt5Core.target = release/Qt5Core.dll
    Qt5Core.CONFIG = no_check_exist
    icudt52.commands = copy /Y %QTDIR%\\bin\\icudt52.dll release
    icudt52.target = release/icudt52.dll
    icudt52.CONFIG = no_check_exist

    icuin52.commands = copy /Y %QTDIR%\\bin\\icuin52.dll release
    icuin52.target = release/icuin52.dll
    icuin52.CONFIG = no_check_exist

    icuuc52.commands = copy /Y %QTDIR%\\bin\\icuuc52.dll release
    icuuc52.target = release/icuuc52.dll
    icuuc52.CONFIG = no_check_exist

    QMAKE_EXTRA_TARGETS += Qt5Core icudt52 icuin52 icuuc52
    PRE_TARGETDEPS += release/Qt5Core.dll release/icudt52.dll release/icuin52.dll release/icuuc52.dll
}

if(contains(QT, gui)) {
    Qt5Gui.commands = copy /Y %QTDIR%\\bin\\Qt5Gui.dll release
    Qt5Gui.target = release/Qt5Gui.dll
    Qt5Gui.CONFIG = no_check_exist

    QMAKE_EXTRA_TARGETS += Qt5Gui
    PRE_TARGETDEPS += release/Qt5Gui.dll
}


if(contains(QT, opengl)) {
    Qt5OpenGL.commands = copy /Y %QTDIR%\\bin\\Qt5OpenGL.dll release
    Qt5OpenGL.target = release/Qt5OpenGL.dll
    Qt5OpenGL.CONFIG = no_check_exist

    QGLViewer2.commands = copy /Y %QTDIR%\\bin\\QGLViewer2.dll release
    QGLViewer2.target = release/QGLViewer2.dll
    QGLViewer2.CONFIG = no_check_exist

    QMAKE_EXTRA_TARGETS += Qt5OpenGL QGLViewer2
    PRE_TARGETDEPS += release/Qt5OpenGL.dll release/QGLViewer2.dll
}
if(contains(QT, xml)) {
    Qt5Xml.commands = copy /Y %QTDIR%\\bin\\Qt5Xml.dll release
    Qt5Xml.target = release/Qt5Xml.dll
    Qt5Xml.CONFIG = no_check_exist

    Qt5XmlPatterns.commands = copy /Y %QTDIR%\\bin\\Qt5XmlPatterns.dll release
    Qt5XmlPatterns.target = release/Qt5XmlPatterns.dll
    Qt5XmlPatterns.CONFIG = no_check_exist

    QMAKE_EXTRA_TARGETS += Qt5Xml Qt5XmlPatterns
    PRE_TARGETDEPS += release/Qt5Xml.dll release/Qt5XmlPatterns.dll
}
if(contains(QT, widgets)) {
    Qt5Widgets.commands = copy /Y %QTDIR%\\bin\\Qt5Widgets.dll release
    Qt5Widgets.target = release/Qt5Widgets.dll
    Qt5Widgets.CONFIG = no_check_exist

    QMAKE_EXTRA_TARGETS += Qt5Widgets
    PRE_TARGETDEPS += release/Qt5Widgets.dll
}
if(contains(QT, sql)) {
    Qt5Sql.commands = copy /Y %QTDIR%\\bin\\Qt5Sql.dll release
    Qt5Sql.target = release/Qt5Sql.dll
    Qt5Sql.CONFIG = no_check_exist

    QMAKE_EXTRA_TARGETS += Qt5Sql
    PRE_TARGETDEPS += release/Qt5Sql.dll
}
win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../FalconModelSharedLib/release/ -lFalconModelSharedLib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../FalconModelSharedLib/debug/ -lFalconModelSharedLib
else:unix:!macx: LIBS += -L$$OUT_PWD/../FalconModelSharedLib/ -lFalconModelSharedLib

INCLUDEPATH += $$PWD/../FalconModelSharedLib
DEPENDPATH += $$PWD/../FalconModelSharedLib
win32:RC_FILE = FalconObjectMaker.rc

win32: LIBS += -lglut32
