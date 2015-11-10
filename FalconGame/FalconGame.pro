#-------------------------------------------------
#
# Project created by QtCreator 2014-08-26T01:56:45
#
#-------------------------------------------------

#-------------------------------------------------
#
# Project created by QtCreator 2014-08-25T04:18:34
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets opengl xml xmlpatterns

TARGET = FalconGame
TEMPLATE = app


SOURCES += main.cpp\
	mainwindow.cpp \
    src_gfx/glviewer.cpp \
    src_math/3DMath.cpp \
    src_game/gameobject.cpp \
    src_game/laserbeam.cpp

HEADERS  += mainwindow.h \
    falconmodelsharedlib_global.h \
    GL/glut.h \
    src_gfx/glviewer.h \
    src_math/3DMath.h \
    src_game/gameobject.h \
    src_game/laserbeam.h


win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../FalconModelSharedLib/release/ -lFalconModelSharedLib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../FalconModelSharedLib/debug/ -lFalconModelSharedLib
else:unix:!macx: LIBS += -L$$OUT_PWD/../FalconModelSharedLib/ -lFalconModelSharedLib

INCLUDEPATH += $$PWD/../FalconModelSharedLib
DEPENDPATH += $$PWD/../FalconModelSharedLib




OTHER_FILES += \
    GL/glut32.dll \
    GL/glut32.lib

win32: LIBS += -L$$PWD/GL/ -lglut32

INCLUDEPATH += $$PWD/GL
DEPENDPATH += $$PWD/GL

win32: LIBS += -L$$PWD/GL/ -lQGLViewer2

INCLUDEPATH += $$PWD/GL
DEPENDPATH += $$PWD/GL
MOC_DIR += ./GeneratedFiles/moc
OBJECTS_DIR += ./GeneratedFiles/obj
UI_DIR += ./GeneratedFiles/ui
RCC_DIR += ./GeneratedFiles/rcc


if(contains(QT, core)) {
    Qt5Core.commands = cp /Y %QTDIR%\\bin\\Qt5Core.dll release
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

    qwindows.commands = COPY /Y %QTDIR%\\plugins\\platforms\\qwindows.dll release
    qwindows.target = release/platforms/qwindows.dll
    qwindows.CONFIG = no_check_exist

    QMAKE_EXTRA_TARGETS += Qt5Core icudt52 icuin52 icuuc52 qwindows
    PRE_TARGETDEPS += release/Qt5Core.dll release/icudt52.dll release/icuin52.dll release/icuuc52.dll release/qwindows.dll
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

    sqlite.commands = COPY /Y %QTDIR%\\plugins\\sqldrivers\\qsqlite.dll release
    sqlite.target = release/sqldrivers/qsqlite.dll
    sqlite.CONFIG = no_check_exist

    my.commands = COPY /Y %QTDIR%\\plugins\\sqldrivers\\qsqlmysql.dll release
    my.target = release/sqldrivers/qsqlmysql.dll
    my.CONFIG = no_check_exist

    QMAKE_EXTRA_TARGETS += Qt5Sql
    PRE_TARGETDEPS += release/Qt5Sql.dll
}
Qt5pflib.commands = copy /Y $$PWD\\..\\FalconModelSharedLib\\release\\FalconModelSharedLib.dll release
Qt5pflib.target = release/FalconModelSharedLib.dll
Qt5pflib.CONFIG = no_check_exist
QMAKE_EXTRA_TARGETS += Qt5pflib
PRE_TARGETDEPS += release/FalconModelSharedLib.dll
