#############################################################################
# Makefile for building: PowerFalcon
# Generated by qmake (3.0) (Qt 5.3.1)
# Project:  PowerFalcon.pro
# Template: subdirs
# Command: C:\Qt\5.3.1\5.3\msvc2010_opengl\bin\qmake.exe -spec win32-msvc2010 -o Makefile PowerFalcon.pro
#############################################################################

MAKEFILE      = Makefile

first: make_first
QMAKE         = C:\Qt\5.3.1\5.3\msvc2010_opengl\bin\qmake.exe
DEL_FILE      = del
CHK_DIR_EXISTS= if not exist
MKDIR         = mkdir
COPY          = copy /y
COPY_FILE     = $(COPY)
COPY_DIR      = xcopy /s /q /y /i
INSTALL_FILE  = $(COPY_FILE)
INSTALL_PROGRAM = $(COPY_FILE)
INSTALL_DIR   = $(COPY_DIR)
DEL_FILE      = del
SYMLINK       = copy /y
DEL_DIR       = rmdir
MOVE          = move
SUBTARGETS    =  \
		sub-FalconObjectMaker \
		sub-FalconModelSharedLib \
		sub-FalconWarMaker \
		sub-FalconGame


sub-FalconObjectMaker-qmake_all:  FORCE
	@if not exist FalconObjectMaker\ mkdir FalconObjectMaker\ & if not exist FalconObjectMaker\ exit 1
	cd FalconObjectMaker\ && $(QMAKE) "C:\Documents and Settings\mike\My Documents\Qt\PowerFalcon\FalconObjectMaker\FalconObjectMaker.pro" -spec win32-msvc2010 -o Makefile
	@set MAKEFLAGS=$(MAKEFLAGS)
	cd FalconObjectMaker\ && $(MAKE) -f Makefile qmake_all
sub-FalconObjectMaker: FORCE
	@if not exist FalconObjectMaker\ mkdir FalconObjectMaker\ & if not exist FalconObjectMaker\ exit 1
	@set MAKEFLAGS=$(MAKEFLAGS)
	cd FalconObjectMaker\ && ( if not exist Makefile $(QMAKE) "C:\Documents and Settings\mike\My Documents\Qt\PowerFalcon\FalconObjectMaker\FalconObjectMaker.pro" -spec win32-msvc2010 -o Makefile ) && $(MAKE) -f Makefile
sub-FalconObjectMaker-make_first: FORCE
	@if not exist FalconObjectMaker\ mkdir FalconObjectMaker\ & if not exist FalconObjectMaker\ exit 1
	@set MAKEFLAGS=$(MAKEFLAGS)
	cd FalconObjectMaker\ && ( if not exist Makefile $(QMAKE) "C:\Documents and Settings\mike\My Documents\Qt\PowerFalcon\FalconObjectMaker\FalconObjectMaker.pro" -spec win32-msvc2010 -o Makefile ) && $(MAKE) -f Makefile 
sub-FalconObjectMaker-all: FORCE
	@if not exist FalconObjectMaker\ mkdir FalconObjectMaker\ & if not exist FalconObjectMaker\ exit 1
	@set MAKEFLAGS=$(MAKEFLAGS)
	cd FalconObjectMaker\ && ( if not exist Makefile $(QMAKE) "C:\Documents and Settings\mike\My Documents\Qt\PowerFalcon\FalconObjectMaker\FalconObjectMaker.pro" -spec win32-msvc2010 -o Makefile ) && $(MAKE) -f Makefile all
sub-FalconObjectMaker-clean: FORCE
	@if not exist FalconObjectMaker\ mkdir FalconObjectMaker\ & if not exist FalconObjectMaker\ exit 1
	@set MAKEFLAGS=$(MAKEFLAGS)
	cd FalconObjectMaker\ && ( if not exist Makefile $(QMAKE) "C:\Documents and Settings\mike\My Documents\Qt\PowerFalcon\FalconObjectMaker\FalconObjectMaker.pro" -spec win32-msvc2010 -o Makefile ) && $(MAKE) -f Makefile clean
sub-FalconObjectMaker-distclean: FORCE
	@if not exist FalconObjectMaker\ mkdir FalconObjectMaker\ & if not exist FalconObjectMaker\ exit 1
	@set MAKEFLAGS=$(MAKEFLAGS)
	cd FalconObjectMaker\ && ( if not exist Makefile $(QMAKE) "C:\Documents and Settings\mike\My Documents\Qt\PowerFalcon\FalconObjectMaker\FalconObjectMaker.pro" -spec win32-msvc2010 -o Makefile ) && $(MAKE) -f Makefile distclean
sub-FalconObjectMaker-install_subtargets: FORCE
	@if not exist FalconObjectMaker\ mkdir FalconObjectMaker\ & if not exist FalconObjectMaker\ exit 1
	@set MAKEFLAGS=$(MAKEFLAGS)
	cd FalconObjectMaker\ && ( if not exist Makefile $(QMAKE) "C:\Documents and Settings\mike\My Documents\Qt\PowerFalcon\FalconObjectMaker\FalconObjectMaker.pro" -spec win32-msvc2010 -o Makefile ) && $(MAKE) -f Makefile install
sub-FalconObjectMaker-uninstall_subtargets: FORCE
	@if not exist FalconObjectMaker\ mkdir FalconObjectMaker\ & if not exist FalconObjectMaker\ exit 1
	@set MAKEFLAGS=$(MAKEFLAGS)
	cd FalconObjectMaker\ && ( if not exist Makefile $(QMAKE) "C:\Documents and Settings\mike\My Documents\Qt\PowerFalcon\FalconObjectMaker\FalconObjectMaker.pro" -spec win32-msvc2010 -o Makefile ) && $(MAKE) -f Makefile uninstall
sub-FalconModelSharedLib-qmake_all:  FORCE
	@if not exist FalconModelSharedLib\ mkdir FalconModelSharedLib\ & if not exist FalconModelSharedLib\ exit 1
	cd FalconModelSharedLib\ && $(QMAKE) "C:\Documents and Settings\mike\My Documents\Qt\PowerFalcon\FalconModelSharedLib\FalconModelSharedLib.pro" -spec win32-msvc2010 -o Makefile
	@set MAKEFLAGS=$(MAKEFLAGS)
	cd FalconModelSharedLib\ && $(MAKE) -f Makefile qmake_all
sub-FalconModelSharedLib: FORCE
	@if not exist FalconModelSharedLib\ mkdir FalconModelSharedLib\ & if not exist FalconModelSharedLib\ exit 1
	@set MAKEFLAGS=$(MAKEFLAGS)
	cd FalconModelSharedLib\ && ( if not exist Makefile $(QMAKE) "C:\Documents and Settings\mike\My Documents\Qt\PowerFalcon\FalconModelSharedLib\FalconModelSharedLib.pro" -spec win32-msvc2010 -o Makefile ) && $(MAKE) -f Makefile
sub-FalconModelSharedLib-make_first: FORCE
	@if not exist FalconModelSharedLib\ mkdir FalconModelSharedLib\ & if not exist FalconModelSharedLib\ exit 1
	@set MAKEFLAGS=$(MAKEFLAGS)
	cd FalconModelSharedLib\ && ( if not exist Makefile $(QMAKE) "C:\Documents and Settings\mike\My Documents\Qt\PowerFalcon\FalconModelSharedLib\FalconModelSharedLib.pro" -spec win32-msvc2010 -o Makefile ) && $(MAKE) -f Makefile 
sub-FalconModelSharedLib-all: FORCE
	@if not exist FalconModelSharedLib\ mkdir FalconModelSharedLib\ & if not exist FalconModelSharedLib\ exit 1
	@set MAKEFLAGS=$(MAKEFLAGS)
	cd FalconModelSharedLib\ && ( if not exist Makefile $(QMAKE) "C:\Documents and Settings\mike\My Documents\Qt\PowerFalcon\FalconModelSharedLib\FalconModelSharedLib.pro" -spec win32-msvc2010 -o Makefile ) && $(MAKE) -f Makefile all
sub-FalconModelSharedLib-clean: FORCE
	@if not exist FalconModelSharedLib\ mkdir FalconModelSharedLib\ & if not exist FalconModelSharedLib\ exit 1
	@set MAKEFLAGS=$(MAKEFLAGS)
	cd FalconModelSharedLib\ && ( if not exist Makefile $(QMAKE) "C:\Documents and Settings\mike\My Documents\Qt\PowerFalcon\FalconModelSharedLib\FalconModelSharedLib.pro" -spec win32-msvc2010 -o Makefile ) && $(MAKE) -f Makefile clean
sub-FalconModelSharedLib-distclean: FORCE
	@if not exist FalconModelSharedLib\ mkdir FalconModelSharedLib\ & if not exist FalconModelSharedLib\ exit 1
	@set MAKEFLAGS=$(MAKEFLAGS)
	cd FalconModelSharedLib\ && ( if not exist Makefile $(QMAKE) "C:\Documents and Settings\mike\My Documents\Qt\PowerFalcon\FalconModelSharedLib\FalconModelSharedLib.pro" -spec win32-msvc2010 -o Makefile ) && $(MAKE) -f Makefile distclean
sub-FalconModelSharedLib-install_subtargets: FORCE
	@if not exist FalconModelSharedLib\ mkdir FalconModelSharedLib\ & if not exist FalconModelSharedLib\ exit 1
	@set MAKEFLAGS=$(MAKEFLAGS)
	cd FalconModelSharedLib\ && ( if not exist Makefile $(QMAKE) "C:\Documents and Settings\mike\My Documents\Qt\PowerFalcon\FalconModelSharedLib\FalconModelSharedLib.pro" -spec win32-msvc2010 -o Makefile ) && $(MAKE) -f Makefile install
sub-FalconModelSharedLib-uninstall_subtargets: FORCE
	@if not exist FalconModelSharedLib\ mkdir FalconModelSharedLib\ & if not exist FalconModelSharedLib\ exit 1
	@set MAKEFLAGS=$(MAKEFLAGS)
	cd FalconModelSharedLib\ && ( if not exist Makefile $(QMAKE) "C:\Documents and Settings\mike\My Documents\Qt\PowerFalcon\FalconModelSharedLib\FalconModelSharedLib.pro" -spec win32-msvc2010 -o Makefile ) && $(MAKE) -f Makefile uninstall
sub-FalconWarMaker-qmake_all:  FORCE
	@if not exist FalconWarMaker\ mkdir FalconWarMaker\ & if not exist FalconWarMaker\ exit 1
	cd FalconWarMaker\ && $(QMAKE) "C:\Documents and Settings\mike\My Documents\Qt\PowerFalcon\FalconWarMaker\FalconWarMaker.pro" -spec win32-msvc2010 -o Makefile
	@set MAKEFLAGS=$(MAKEFLAGS)
	cd FalconWarMaker\ && $(MAKE) -f Makefile qmake_all
sub-FalconWarMaker: FORCE
	@if not exist FalconWarMaker\ mkdir FalconWarMaker\ & if not exist FalconWarMaker\ exit 1
	@set MAKEFLAGS=$(MAKEFLAGS)
	cd FalconWarMaker\ && ( if not exist Makefile $(QMAKE) "C:\Documents and Settings\mike\My Documents\Qt\PowerFalcon\FalconWarMaker\FalconWarMaker.pro" -spec win32-msvc2010 -o Makefile ) && $(MAKE) -f Makefile
sub-FalconWarMaker-make_first: FORCE
	@if not exist FalconWarMaker\ mkdir FalconWarMaker\ & if not exist FalconWarMaker\ exit 1
	@set MAKEFLAGS=$(MAKEFLAGS)
	cd FalconWarMaker\ && ( if not exist Makefile $(QMAKE) "C:\Documents and Settings\mike\My Documents\Qt\PowerFalcon\FalconWarMaker\FalconWarMaker.pro" -spec win32-msvc2010 -o Makefile ) && $(MAKE) -f Makefile 
sub-FalconWarMaker-all: FORCE
	@if not exist FalconWarMaker\ mkdir FalconWarMaker\ & if not exist FalconWarMaker\ exit 1
	@set MAKEFLAGS=$(MAKEFLAGS)
	cd FalconWarMaker\ && ( if not exist Makefile $(QMAKE) "C:\Documents and Settings\mike\My Documents\Qt\PowerFalcon\FalconWarMaker\FalconWarMaker.pro" -spec win32-msvc2010 -o Makefile ) && $(MAKE) -f Makefile all
sub-FalconWarMaker-clean: FORCE
	@if not exist FalconWarMaker\ mkdir FalconWarMaker\ & if not exist FalconWarMaker\ exit 1
	@set MAKEFLAGS=$(MAKEFLAGS)
	cd FalconWarMaker\ && ( if not exist Makefile $(QMAKE) "C:\Documents and Settings\mike\My Documents\Qt\PowerFalcon\FalconWarMaker\FalconWarMaker.pro" -spec win32-msvc2010 -o Makefile ) && $(MAKE) -f Makefile clean
sub-FalconWarMaker-distclean: FORCE
	@if not exist FalconWarMaker\ mkdir FalconWarMaker\ & if not exist FalconWarMaker\ exit 1
	@set MAKEFLAGS=$(MAKEFLAGS)
	cd FalconWarMaker\ && ( if not exist Makefile $(QMAKE) "C:\Documents and Settings\mike\My Documents\Qt\PowerFalcon\FalconWarMaker\FalconWarMaker.pro" -spec win32-msvc2010 -o Makefile ) && $(MAKE) -f Makefile distclean
sub-FalconWarMaker-install_subtargets: FORCE
	@if not exist FalconWarMaker\ mkdir FalconWarMaker\ & if not exist FalconWarMaker\ exit 1
	@set MAKEFLAGS=$(MAKEFLAGS)
	cd FalconWarMaker\ && ( if not exist Makefile $(QMAKE) "C:\Documents and Settings\mike\My Documents\Qt\PowerFalcon\FalconWarMaker\FalconWarMaker.pro" -spec win32-msvc2010 -o Makefile ) && $(MAKE) -f Makefile install
sub-FalconWarMaker-uninstall_subtargets: FORCE
	@if not exist FalconWarMaker\ mkdir FalconWarMaker\ & if not exist FalconWarMaker\ exit 1
	@set MAKEFLAGS=$(MAKEFLAGS)
	cd FalconWarMaker\ && ( if not exist Makefile $(QMAKE) "C:\Documents and Settings\mike\My Documents\Qt\PowerFalcon\FalconWarMaker\FalconWarMaker.pro" -spec win32-msvc2010 -o Makefile ) && $(MAKE) -f Makefile uninstall
sub-FalconGame-qmake_all:  FORCE
	@if not exist FalconGame\ mkdir FalconGame\ & if not exist FalconGame\ exit 1
	cd FalconGame\ && $(QMAKE) "C:\Documents and Settings\mike\My Documents\Qt\PowerFalcon\FalconGame\FalconGame.pro" -spec win32-msvc2010 -o Makefile
	@set MAKEFLAGS=$(MAKEFLAGS)
	cd FalconGame\ && $(MAKE) -f Makefile qmake_all
sub-FalconGame: FORCE
	@if not exist FalconGame\ mkdir FalconGame\ & if not exist FalconGame\ exit 1
	@set MAKEFLAGS=$(MAKEFLAGS)
	cd FalconGame\ && ( if not exist Makefile $(QMAKE) "C:\Documents and Settings\mike\My Documents\Qt\PowerFalcon\FalconGame\FalconGame.pro" -spec win32-msvc2010 -o Makefile ) && $(MAKE) -f Makefile
sub-FalconGame-make_first: FORCE
	@if not exist FalconGame\ mkdir FalconGame\ & if not exist FalconGame\ exit 1
	@set MAKEFLAGS=$(MAKEFLAGS)
	cd FalconGame\ && ( if not exist Makefile $(QMAKE) "C:\Documents and Settings\mike\My Documents\Qt\PowerFalcon\FalconGame\FalconGame.pro" -spec win32-msvc2010 -o Makefile ) && $(MAKE) -f Makefile 
sub-FalconGame-all: FORCE
	@if not exist FalconGame\ mkdir FalconGame\ & if not exist FalconGame\ exit 1
	@set MAKEFLAGS=$(MAKEFLAGS)
	cd FalconGame\ && ( if not exist Makefile $(QMAKE) "C:\Documents and Settings\mike\My Documents\Qt\PowerFalcon\FalconGame\FalconGame.pro" -spec win32-msvc2010 -o Makefile ) && $(MAKE) -f Makefile all
sub-FalconGame-clean: FORCE
	@if not exist FalconGame\ mkdir FalconGame\ & if not exist FalconGame\ exit 1
	@set MAKEFLAGS=$(MAKEFLAGS)
	cd FalconGame\ && ( if not exist Makefile $(QMAKE) "C:\Documents and Settings\mike\My Documents\Qt\PowerFalcon\FalconGame\FalconGame.pro" -spec win32-msvc2010 -o Makefile ) && $(MAKE) -f Makefile clean
sub-FalconGame-distclean: FORCE
	@if not exist FalconGame\ mkdir FalconGame\ & if not exist FalconGame\ exit 1
	@set MAKEFLAGS=$(MAKEFLAGS)
	cd FalconGame\ && ( if not exist Makefile $(QMAKE) "C:\Documents and Settings\mike\My Documents\Qt\PowerFalcon\FalconGame\FalconGame.pro" -spec win32-msvc2010 -o Makefile ) && $(MAKE) -f Makefile distclean
sub-FalconGame-install_subtargets: FORCE
	@if not exist FalconGame\ mkdir FalconGame\ & if not exist FalconGame\ exit 1
	@set MAKEFLAGS=$(MAKEFLAGS)
	cd FalconGame\ && ( if not exist Makefile $(QMAKE) "C:\Documents and Settings\mike\My Documents\Qt\PowerFalcon\FalconGame\FalconGame.pro" -spec win32-msvc2010 -o Makefile ) && $(MAKE) -f Makefile install
sub-FalconGame-uninstall_subtargets: FORCE
	@if not exist FalconGame\ mkdir FalconGame\ & if not exist FalconGame\ exit 1
	@set MAKEFLAGS=$(MAKEFLAGS)
	cd FalconGame\ && ( if not exist Makefile $(QMAKE) "C:\Documents and Settings\mike\My Documents\Qt\PowerFalcon\FalconGame\FalconGame.pro" -spec win32-msvc2010 -o Makefile ) && $(MAKE) -f Makefile uninstall

Makefile: PowerFalcon.pro C:\Qt\5.3.1\5.3\msvc2010_opengl\mkspecs\win32-msvc2010\qmake.conf C:\Qt\5.3.1\5.3\msvc2010_opengl\mkspecs\features\spec_pre.prf \
		C:\Qt\5.3.1\5.3\msvc2010_opengl\mkspecs\common\shell-win32.conf \
		C:\Qt\5.3.1\5.3\msvc2010_opengl\mkspecs\qconfig.pri \
		C:\Qt\5.3.1\5.3\msvc2010_opengl\mkspecs\modules\qt_lib_axbase.pri \
		C:\Qt\5.3.1\5.3\msvc2010_opengl\mkspecs\modules\qt_lib_axbase_private.pri \
		C:\Qt\5.3.1\5.3\msvc2010_opengl\mkspecs\modules\qt_lib_axcontainer.pri \
		C:\Qt\5.3.1\5.3\msvc2010_opengl\mkspecs\modules\qt_lib_axcontainer_private.pri \
		C:\Qt\5.3.1\5.3\msvc2010_opengl\mkspecs\modules\qt_lib_axserver.pri \
		C:\Qt\5.3.1\5.3\msvc2010_opengl\mkspecs\modules\qt_lib_axserver_private.pri \
		C:\Qt\5.3.1\5.3\msvc2010_opengl\mkspecs\modules\qt_lib_bluetooth.pri \
		C:\Qt\5.3.1\5.3\msvc2010_opengl\mkspecs\modules\qt_lib_bluetooth_private.pri \
		C:\Qt\5.3.1\5.3\msvc2010_opengl\mkspecs\modules\qt_lib_bootstrap_private.pri \
		C:\Qt\5.3.1\5.3\msvc2010_opengl\mkspecs\modules\qt_lib_clucene_private.pri \
		C:\Qt\5.3.1\5.3\msvc2010_opengl\mkspecs\modules\qt_lib_concurrent.pri \
		C:\Qt\5.3.1\5.3\msvc2010_opengl\mkspecs\modules\qt_lib_concurrent_private.pri \
		C:\Qt\5.3.1\5.3\msvc2010_opengl\mkspecs\modules\qt_lib_core.pri \
		C:\Qt\5.3.1\5.3\msvc2010_opengl\mkspecs\modules\qt_lib_core_private.pri \
		C:\Qt\5.3.1\5.3\msvc2010_opengl\mkspecs\modules\qt_lib_declarative.pri \
		C:\Qt\5.3.1\5.3\msvc2010_opengl\mkspecs\modules\qt_lib_declarative_private.pri \
		C:\Qt\5.3.1\5.3\msvc2010_opengl\mkspecs\modules\qt_lib_designer.pri \
		C:\Qt\5.3.1\5.3\msvc2010_opengl\mkspecs\modules\qt_lib_designer_private.pri \
		C:\Qt\5.3.1\5.3\msvc2010_opengl\mkspecs\modules\qt_lib_designercomponents_private.pri \
		C:\Qt\5.3.1\5.3\msvc2010_opengl\mkspecs\modules\qt_lib_enginio.pri \
		C:\Qt\5.3.1\5.3\msvc2010_opengl\mkspecs\modules\qt_lib_enginio_private.pri \
		C:\Qt\5.3.1\5.3\msvc2010_opengl\mkspecs\modules\qt_lib_gui.pri \
		C:\Qt\5.3.1\5.3\msvc2010_opengl\mkspecs\modules\qt_lib_gui_private.pri \
		C:\Qt\5.3.1\5.3\msvc2010_opengl\mkspecs\modules\qt_lib_help.pri \
		C:\Qt\5.3.1\5.3\msvc2010_opengl\mkspecs\modules\qt_lib_help_private.pri \
		C:\Qt\5.3.1\5.3\msvc2010_opengl\mkspecs\modules\qt_lib_multimedia.pri \
		C:\Qt\5.3.1\5.3\msvc2010_opengl\mkspecs\modules\qt_lib_multimedia_private.pri \
		C:\Qt\5.3.1\5.3\msvc2010_opengl\mkspecs\modules\qt_lib_multimediawidgets.pri \
		C:\Qt\5.3.1\5.3\msvc2010_opengl\mkspecs\modules\qt_lib_multimediawidgets_private.pri \
		C:\Qt\5.3.1\5.3\msvc2010_opengl\mkspecs\modules\qt_lib_network.pri \
		C:\Qt\5.3.1\5.3\msvc2010_opengl\mkspecs\modules\qt_lib_network_private.pri \
		C:\Qt\5.3.1\5.3\msvc2010_opengl\mkspecs\modules\qt_lib_nfc.pri \
		C:\Qt\5.3.1\5.3\msvc2010_opengl\mkspecs\modules\qt_lib_nfc_private.pri \
		C:\Qt\5.3.1\5.3\msvc2010_opengl\mkspecs\modules\qt_lib_opengl.pri \
		C:\Qt\5.3.1\5.3\msvc2010_opengl\mkspecs\modules\qt_lib_opengl_private.pri \
		C:\Qt\5.3.1\5.3\msvc2010_opengl\mkspecs\modules\qt_lib_openglextensions.pri \
		C:\Qt\5.3.1\5.3\msvc2010_opengl\mkspecs\modules\qt_lib_openglextensions_private.pri \
		C:\Qt\5.3.1\5.3\msvc2010_opengl\mkspecs\modules\qt_lib_platformsupport_private.pri \
		C:\Qt\5.3.1\5.3\msvc2010_opengl\mkspecs\modules\qt_lib_positioning.pri \
		C:\Qt\5.3.1\5.3\msvc2010_opengl\mkspecs\modules\qt_lib_positioning_private.pri \
		C:\Qt\5.3.1\5.3\msvc2010_opengl\mkspecs\modules\qt_lib_printsupport.pri \
		C:\Qt\5.3.1\5.3\msvc2010_opengl\mkspecs\modules\qt_lib_printsupport_private.pri \
		C:\Qt\5.3.1\5.3\msvc2010_opengl\mkspecs\modules\qt_lib_qml.pri \
		C:\Qt\5.3.1\5.3\msvc2010_opengl\mkspecs\modules\qt_lib_qml_private.pri \
		C:\Qt\5.3.1\5.3\msvc2010_opengl\mkspecs\modules\qt_lib_qmldevtools_private.pri \
		C:\Qt\5.3.1\5.3\msvc2010_opengl\mkspecs\modules\qt_lib_qmltest.pri \
		C:\Qt\5.3.1\5.3\msvc2010_opengl\mkspecs\modules\qt_lib_qmltest_private.pri \
		C:\Qt\5.3.1\5.3\msvc2010_opengl\mkspecs\modules\qt_lib_qtmultimediaquicktools_private.pri \
		C:\Qt\5.3.1\5.3\msvc2010_opengl\mkspecs\modules\qt_lib_quick.pri \
		C:\Qt\5.3.1\5.3\msvc2010_opengl\mkspecs\modules\qt_lib_quick_private.pri \
		C:\Qt\5.3.1\5.3\msvc2010_opengl\mkspecs\modules\qt_lib_quickparticles_private.pri \
		C:\Qt\5.3.1\5.3\msvc2010_opengl\mkspecs\modules\qt_lib_quickwidgets.pri \
		C:\Qt\5.3.1\5.3\msvc2010_opengl\mkspecs\modules\qt_lib_quickwidgets_private.pri \
		C:\Qt\5.3.1\5.3\msvc2010_opengl\mkspecs\modules\qt_lib_script.pri \
		C:\Qt\5.3.1\5.3\msvc2010_opengl\mkspecs\modules\qt_lib_script_private.pri \
		C:\Qt\5.3.1\5.3\msvc2010_opengl\mkspecs\modules\qt_lib_scripttools.pri \
		C:\Qt\5.3.1\5.3\msvc2010_opengl\mkspecs\modules\qt_lib_scripttools_private.pri \
		C:\Qt\5.3.1\5.3\msvc2010_opengl\mkspecs\modules\qt_lib_sensors.pri \
		C:\Qt\5.3.1\5.3\msvc2010_opengl\mkspecs\modules\qt_lib_sensors_private.pri \
		C:\Qt\5.3.1\5.3\msvc2010_opengl\mkspecs\modules\qt_lib_serialport.pri \
		C:\Qt\5.3.1\5.3\msvc2010_opengl\mkspecs\modules\qt_lib_serialport_private.pri \
		C:\Qt\5.3.1\5.3\msvc2010_opengl\mkspecs\modules\qt_lib_sql.pri \
		C:\Qt\5.3.1\5.3\msvc2010_opengl\mkspecs\modules\qt_lib_sql_private.pri \
		C:\Qt\5.3.1\5.3\msvc2010_opengl\mkspecs\modules\qt_lib_svg.pri \
		C:\Qt\5.3.1\5.3\msvc2010_opengl\mkspecs\modules\qt_lib_svg_private.pri \
		C:\Qt\5.3.1\5.3\msvc2010_opengl\mkspecs\modules\qt_lib_testlib.pri \
		C:\Qt\5.3.1\5.3\msvc2010_opengl\mkspecs\modules\qt_lib_testlib_private.pri \
		C:\Qt\5.3.1\5.3\msvc2010_opengl\mkspecs\modules\qt_lib_uitools.pri \
		C:\Qt\5.3.1\5.3\msvc2010_opengl\mkspecs\modules\qt_lib_uitools_private.pri \
		C:\Qt\5.3.1\5.3\msvc2010_opengl\mkspecs\modules\qt_lib_webkit.pri \
		C:\Qt\5.3.1\5.3\msvc2010_opengl\mkspecs\modules\qt_lib_webkit_private.pri \
		C:\Qt\5.3.1\5.3\msvc2010_opengl\mkspecs\modules\qt_lib_webkitwidgets.pri \
		C:\Qt\5.3.1\5.3\msvc2010_opengl\mkspecs\modules\qt_lib_webkitwidgets_private.pri \
		C:\Qt\5.3.1\5.3\msvc2010_opengl\mkspecs\modules\qt_lib_websockets.pri \
		C:\Qt\5.3.1\5.3\msvc2010_opengl\mkspecs\modules\qt_lib_websockets_private.pri \
		C:\Qt\5.3.1\5.3\msvc2010_opengl\mkspecs\modules\qt_lib_widgets.pri \
		C:\Qt\5.3.1\5.3\msvc2010_opengl\mkspecs\modules\qt_lib_widgets_private.pri \
		C:\Qt\5.3.1\5.3\msvc2010_opengl\mkspecs\modules\qt_lib_winextras.pri \
		C:\Qt\5.3.1\5.3\msvc2010_opengl\mkspecs\modules\qt_lib_winextras_private.pri \
		C:\Qt\5.3.1\5.3\msvc2010_opengl\mkspecs\modules\qt_lib_xml.pri \
		C:\Qt\5.3.1\5.3\msvc2010_opengl\mkspecs\modules\qt_lib_xml_private.pri \
		C:\Qt\5.3.1\5.3\msvc2010_opengl\mkspecs\modules\qt_lib_xmlpatterns.pri \
		C:\Qt\5.3.1\5.3\msvc2010_opengl\mkspecs\modules\qt_lib_xmlpatterns_private.pri \
		C:\Qt\5.3.1\5.3\msvc2010_opengl\mkspecs\features\qt_functions.prf \
		C:\Qt\5.3.1\5.3\msvc2010_opengl\mkspecs\features\qt_config.prf \
		C:\Qt\5.3.1\5.3\msvc2010_opengl\mkspecs\features\win32\qt_config.prf \
		C:\Qt\5.3.1\5.3\msvc2010_opengl\mkspecs\win32-msvc2010\qmake.conf \
		C:\Qt\5.3.1\5.3\msvc2010_opengl\mkspecs\features\spec_post.prf \
		C:\Qt\5.3.1\5.3\msvc2010_opengl\mkspecs\features\exclusive_builds.prf \
		C:\Qt\5.3.1\5.3\msvc2010_opengl\mkspecs\features\default_pre.prf \
		C:\Qt\5.3.1\5.3\msvc2010_opengl\mkspecs\features\win32\default_pre.prf \
		C:\Qt\5.3.1\5.3\msvc2010_opengl\mkspecs\features\resolve_config.prf \
		C:\Qt\5.3.1\5.3\msvc2010_opengl\mkspecs\features\exclusive_builds_post.prf \
		C:\Qt\5.3.1\5.3\msvc2010_opengl\mkspecs\features\default_post.prf \
		C:\Qt\5.3.1\5.3\msvc2010_opengl\mkspecs\features\win32\rtti.prf \
		C:\Qt\5.3.1\5.3\msvc2010_opengl\mkspecs\features\precompile_header.prf \
		C:\Qt\5.3.1\5.3\msvc2010_opengl\mkspecs\features\warn_on.prf \
		C:\Qt\5.3.1\5.3\msvc2010_opengl\mkspecs\features\win32\windows.prf \
		C:\Qt\5.3.1\5.3\msvc2010_opengl\mkspecs\features\testcase_targets.prf \
		C:\Qt\5.3.1\5.3\msvc2010_opengl\mkspecs\features\exceptions.prf \
		C:\Qt\5.3.1\5.3\msvc2010_opengl\mkspecs\features\yacc.prf \
		C:\Qt\5.3.1\5.3\msvc2010_opengl\mkspecs\features\lex.prf \
		PowerFalcon.pro
	$(QMAKE) -spec win32-msvc2010 -o Makefile PowerFalcon.pro
C:\Qt\5.3.1\5.3\msvc2010_opengl\mkspecs\features\spec_pre.prf:
C:\Qt\5.3.1\5.3\msvc2010_opengl\mkspecs\common\shell-win32.conf:
C:\Qt\5.3.1\5.3\msvc2010_opengl\mkspecs\qconfig.pri:
C:\Qt\5.3.1\5.3\msvc2010_opengl\mkspecs\modules\qt_lib_axbase.pri:
C:\Qt\5.3.1\5.3\msvc2010_opengl\mkspecs\modules\qt_lib_axbase_private.pri:
C:\Qt\5.3.1\5.3\msvc2010_opengl\mkspecs\modules\qt_lib_axcontainer.pri:
C:\Qt\5.3.1\5.3\msvc2010_opengl\mkspecs\modules\qt_lib_axcontainer_private.pri:
C:\Qt\5.3.1\5.3\msvc2010_opengl\mkspecs\modules\qt_lib_axserver.pri:
C:\Qt\5.3.1\5.3\msvc2010_opengl\mkspecs\modules\qt_lib_axserver_private.pri:
C:\Qt\5.3.1\5.3\msvc2010_opengl\mkspecs\modules\qt_lib_bluetooth.pri:
C:\Qt\5.3.1\5.3\msvc2010_opengl\mkspecs\modules\qt_lib_bluetooth_private.pri:
C:\Qt\5.3.1\5.3\msvc2010_opengl\mkspecs\modules\qt_lib_bootstrap_private.pri:
C:\Qt\5.3.1\5.3\msvc2010_opengl\mkspecs\modules\qt_lib_clucene_private.pri:
C:\Qt\5.3.1\5.3\msvc2010_opengl\mkspecs\modules\qt_lib_concurrent.pri:
C:\Qt\5.3.1\5.3\msvc2010_opengl\mkspecs\modules\qt_lib_concurrent_private.pri:
C:\Qt\5.3.1\5.3\msvc2010_opengl\mkspecs\modules\qt_lib_core.pri:
C:\Qt\5.3.1\5.3\msvc2010_opengl\mkspecs\modules\qt_lib_core_private.pri:
C:\Qt\5.3.1\5.3\msvc2010_opengl\mkspecs\modules\qt_lib_declarative.pri:
C:\Qt\5.3.1\5.3\msvc2010_opengl\mkspecs\modules\qt_lib_declarative_private.pri:
C:\Qt\5.3.1\5.3\msvc2010_opengl\mkspecs\modules\qt_lib_designer.pri:
C:\Qt\5.3.1\5.3\msvc2010_opengl\mkspecs\modules\qt_lib_designer_private.pri:
C:\Qt\5.3.1\5.3\msvc2010_opengl\mkspecs\modules\qt_lib_designercomponents_private.pri:
C:\Qt\5.3.1\5.3\msvc2010_opengl\mkspecs\modules\qt_lib_enginio.pri:
C:\Qt\5.3.1\5.3\msvc2010_opengl\mkspecs\modules\qt_lib_enginio_private.pri:
C:\Qt\5.3.1\5.3\msvc2010_opengl\mkspecs\modules\qt_lib_gui.pri:
C:\Qt\5.3.1\5.3\msvc2010_opengl\mkspecs\modules\qt_lib_gui_private.pri:
C:\Qt\5.3.1\5.3\msvc2010_opengl\mkspecs\modules\qt_lib_help.pri:
C:\Qt\5.3.1\5.3\msvc2010_opengl\mkspecs\modules\qt_lib_help_private.pri:
C:\Qt\5.3.1\5.3\msvc2010_opengl\mkspecs\modules\qt_lib_multimedia.pri:
C:\Qt\5.3.1\5.3\msvc2010_opengl\mkspecs\modules\qt_lib_multimedia_private.pri:
C:\Qt\5.3.1\5.3\msvc2010_opengl\mkspecs\modules\qt_lib_multimediawidgets.pri:
C:\Qt\5.3.1\5.3\msvc2010_opengl\mkspecs\modules\qt_lib_multimediawidgets_private.pri:
C:\Qt\5.3.1\5.3\msvc2010_opengl\mkspecs\modules\qt_lib_network.pri:
C:\Qt\5.3.1\5.3\msvc2010_opengl\mkspecs\modules\qt_lib_network_private.pri:
C:\Qt\5.3.1\5.3\msvc2010_opengl\mkspecs\modules\qt_lib_nfc.pri:
C:\Qt\5.3.1\5.3\msvc2010_opengl\mkspecs\modules\qt_lib_nfc_private.pri:
C:\Qt\5.3.1\5.3\msvc2010_opengl\mkspecs\modules\qt_lib_opengl.pri:
C:\Qt\5.3.1\5.3\msvc2010_opengl\mkspecs\modules\qt_lib_opengl_private.pri:
C:\Qt\5.3.1\5.3\msvc2010_opengl\mkspecs\modules\qt_lib_openglextensions.pri:
C:\Qt\5.3.1\5.3\msvc2010_opengl\mkspecs\modules\qt_lib_openglextensions_private.pri:
C:\Qt\5.3.1\5.3\msvc2010_opengl\mkspecs\modules\qt_lib_platformsupport_private.pri:
C:\Qt\5.3.1\5.3\msvc2010_opengl\mkspecs\modules\qt_lib_positioning.pri:
C:\Qt\5.3.1\5.3\msvc2010_opengl\mkspecs\modules\qt_lib_positioning_private.pri:
C:\Qt\5.3.1\5.3\msvc2010_opengl\mkspecs\modules\qt_lib_printsupport.pri:
C:\Qt\5.3.1\5.3\msvc2010_opengl\mkspecs\modules\qt_lib_printsupport_private.pri:
C:\Qt\5.3.1\5.3\msvc2010_opengl\mkspecs\modules\qt_lib_qml.pri:
C:\Qt\5.3.1\5.3\msvc2010_opengl\mkspecs\modules\qt_lib_qml_private.pri:
C:\Qt\5.3.1\5.3\msvc2010_opengl\mkspecs\modules\qt_lib_qmldevtools_private.pri:
C:\Qt\5.3.1\5.3\msvc2010_opengl\mkspecs\modules\qt_lib_qmltest.pri:
C:\Qt\5.3.1\5.3\msvc2010_opengl\mkspecs\modules\qt_lib_qmltest_private.pri:
C:\Qt\5.3.1\5.3\msvc2010_opengl\mkspecs\modules\qt_lib_qtmultimediaquicktools_private.pri:
C:\Qt\5.3.1\5.3\msvc2010_opengl\mkspecs\modules\qt_lib_quick.pri:
C:\Qt\5.3.1\5.3\msvc2010_opengl\mkspecs\modules\qt_lib_quick_private.pri:
C:\Qt\5.3.1\5.3\msvc2010_opengl\mkspecs\modules\qt_lib_quickparticles_private.pri:
C:\Qt\5.3.1\5.3\msvc2010_opengl\mkspecs\modules\qt_lib_quickwidgets.pri:
C:\Qt\5.3.1\5.3\msvc2010_opengl\mkspecs\modules\qt_lib_quickwidgets_private.pri:
C:\Qt\5.3.1\5.3\msvc2010_opengl\mkspecs\modules\qt_lib_script.pri:
C:\Qt\5.3.1\5.3\msvc2010_opengl\mkspecs\modules\qt_lib_script_private.pri:
C:\Qt\5.3.1\5.3\msvc2010_opengl\mkspecs\modules\qt_lib_scripttools.pri:
C:\Qt\5.3.1\5.3\msvc2010_opengl\mkspecs\modules\qt_lib_scripttools_private.pri:
C:\Qt\5.3.1\5.3\msvc2010_opengl\mkspecs\modules\qt_lib_sensors.pri:
C:\Qt\5.3.1\5.3\msvc2010_opengl\mkspecs\modules\qt_lib_sensors_private.pri:
C:\Qt\5.3.1\5.3\msvc2010_opengl\mkspecs\modules\qt_lib_serialport.pri:
C:\Qt\5.3.1\5.3\msvc2010_opengl\mkspecs\modules\qt_lib_serialport_private.pri:
C:\Qt\5.3.1\5.3\msvc2010_opengl\mkspecs\modules\qt_lib_sql.pri:
C:\Qt\5.3.1\5.3\msvc2010_opengl\mkspecs\modules\qt_lib_sql_private.pri:
C:\Qt\5.3.1\5.3\msvc2010_opengl\mkspecs\modules\qt_lib_svg.pri:
C:\Qt\5.3.1\5.3\msvc2010_opengl\mkspecs\modules\qt_lib_svg_private.pri:
C:\Qt\5.3.1\5.3\msvc2010_opengl\mkspecs\modules\qt_lib_testlib.pri:
C:\Qt\5.3.1\5.3\msvc2010_opengl\mkspecs\modules\qt_lib_testlib_private.pri:
C:\Qt\5.3.1\5.3\msvc2010_opengl\mkspecs\modules\qt_lib_uitools.pri:
C:\Qt\5.3.1\5.3\msvc2010_opengl\mkspecs\modules\qt_lib_uitools_private.pri:
C:\Qt\5.3.1\5.3\msvc2010_opengl\mkspecs\modules\qt_lib_webkit.pri:
C:\Qt\5.3.1\5.3\msvc2010_opengl\mkspecs\modules\qt_lib_webkit_private.pri:
C:\Qt\5.3.1\5.3\msvc2010_opengl\mkspecs\modules\qt_lib_webkitwidgets.pri:
C:\Qt\5.3.1\5.3\msvc2010_opengl\mkspecs\modules\qt_lib_webkitwidgets_private.pri:
C:\Qt\5.3.1\5.3\msvc2010_opengl\mkspecs\modules\qt_lib_websockets.pri:
C:\Qt\5.3.1\5.3\msvc2010_opengl\mkspecs\modules\qt_lib_websockets_private.pri:
C:\Qt\5.3.1\5.3\msvc2010_opengl\mkspecs\modules\qt_lib_widgets.pri:
C:\Qt\5.3.1\5.3\msvc2010_opengl\mkspecs\modules\qt_lib_widgets_private.pri:
C:\Qt\5.3.1\5.3\msvc2010_opengl\mkspecs\modules\qt_lib_winextras.pri:
C:\Qt\5.3.1\5.3\msvc2010_opengl\mkspecs\modules\qt_lib_winextras_private.pri:
C:\Qt\5.3.1\5.3\msvc2010_opengl\mkspecs\modules\qt_lib_xml.pri:
C:\Qt\5.3.1\5.3\msvc2010_opengl\mkspecs\modules\qt_lib_xml_private.pri:
C:\Qt\5.3.1\5.3\msvc2010_opengl\mkspecs\modules\qt_lib_xmlpatterns.pri:
C:\Qt\5.3.1\5.3\msvc2010_opengl\mkspecs\modules\qt_lib_xmlpatterns_private.pri:
C:\Qt\5.3.1\5.3\msvc2010_opengl\mkspecs\features\qt_functions.prf:
C:\Qt\5.3.1\5.3\msvc2010_opengl\mkspecs\features\qt_config.prf:
C:\Qt\5.3.1\5.3\msvc2010_opengl\mkspecs\features\win32\qt_config.prf:
C:\Qt\5.3.1\5.3\msvc2010_opengl\mkspecs\win32-msvc2010\qmake.conf:
C:\Qt\5.3.1\5.3\msvc2010_opengl\mkspecs\features\spec_post.prf:
C:\Qt\5.3.1\5.3\msvc2010_opengl\mkspecs\features\exclusive_builds.prf:
C:\Qt\5.3.1\5.3\msvc2010_opengl\mkspecs\features\default_pre.prf:
C:\Qt\5.3.1\5.3\msvc2010_opengl\mkspecs\features\win32\default_pre.prf:
C:\Qt\5.3.1\5.3\msvc2010_opengl\mkspecs\features\resolve_config.prf:
C:\Qt\5.3.1\5.3\msvc2010_opengl\mkspecs\features\exclusive_builds_post.prf:
C:\Qt\5.3.1\5.3\msvc2010_opengl\mkspecs\features\default_post.prf:
C:\Qt\5.3.1\5.3\msvc2010_opengl\mkspecs\features\win32\rtti.prf:
C:\Qt\5.3.1\5.3\msvc2010_opengl\mkspecs\features\precompile_header.prf:
C:\Qt\5.3.1\5.3\msvc2010_opengl\mkspecs\features\warn_on.prf:
C:\Qt\5.3.1\5.3\msvc2010_opengl\mkspecs\features\win32\windows.prf:
C:\Qt\5.3.1\5.3\msvc2010_opengl\mkspecs\features\testcase_targets.prf:
C:\Qt\5.3.1\5.3\msvc2010_opengl\mkspecs\features\exceptions.prf:
C:\Qt\5.3.1\5.3\msvc2010_opengl\mkspecs\features\yacc.prf:
C:\Qt\5.3.1\5.3\msvc2010_opengl\mkspecs\features\lex.prf:
PowerFalcon.pro:
qmake: FORCE
	@$(QMAKE) -spec win32-msvc2010 -o Makefile PowerFalcon.pro

qmake_all: sub-FalconObjectMaker-qmake_all sub-FalconModelSharedLib-qmake_all sub-FalconWarMaker-qmake_all sub-FalconGame-qmake_all FORCE

make_first: sub-FalconObjectMaker-make_first sub-FalconModelSharedLib-make_first sub-FalconWarMaker-make_first sub-FalconGame-make_first FORCE
all: sub-FalconObjectMaker-all sub-FalconModelSharedLib-all sub-FalconWarMaker-all sub-FalconGame-all FORCE
clean: sub-FalconObjectMaker-clean sub-FalconModelSharedLib-clean sub-FalconWarMaker-clean sub-FalconGame-clean FORCE
distclean: sub-FalconObjectMaker-distclean sub-FalconModelSharedLib-distclean sub-FalconWarMaker-distclean sub-FalconGame-distclean FORCE
	-$(DEL_FILE) Makefile
install_subtargets: sub-FalconObjectMaker-install_subtargets sub-FalconModelSharedLib-install_subtargets sub-FalconWarMaker-install_subtargets sub-FalconGame-install_subtargets FORCE
uninstall_subtargets: sub-FalconObjectMaker-uninstall_subtargets sub-FalconModelSharedLib-uninstall_subtargets sub-FalconWarMaker-uninstall_subtargets sub-FalconGame-uninstall_subtargets FORCE

sub-FalconObjectMaker-debug:
	@if not exist FalconObjectMaker\ mkdir FalconObjectMaker\ & if not exist FalconObjectMaker\ exit 1
	@set MAKEFLAGS=$(MAKEFLAGS)
	cd FalconObjectMaker\ && ( if not exist Makefile $(QMAKE) "C:\Documents and Settings\mike\My Documents\Qt\PowerFalcon\FalconObjectMaker\FalconObjectMaker.pro" -spec win32-msvc2010 -o Makefile ) && $(MAKE) -f Makefile debug
sub-FalconModelSharedLib-debug:
	@if not exist FalconModelSharedLib\ mkdir FalconModelSharedLib\ & if not exist FalconModelSharedLib\ exit 1
	@set MAKEFLAGS=$(MAKEFLAGS)
	cd FalconModelSharedLib\ && ( if not exist Makefile $(QMAKE) "C:\Documents and Settings\mike\My Documents\Qt\PowerFalcon\FalconModelSharedLib\FalconModelSharedLib.pro" -spec win32-msvc2010 -o Makefile ) && $(MAKE) -f Makefile debug
sub-FalconWarMaker-debug:
	@if not exist FalconWarMaker\ mkdir FalconWarMaker\ & if not exist FalconWarMaker\ exit 1
	@set MAKEFLAGS=$(MAKEFLAGS)
	cd FalconWarMaker\ && ( if not exist Makefile $(QMAKE) "C:\Documents and Settings\mike\My Documents\Qt\PowerFalcon\FalconWarMaker\FalconWarMaker.pro" -spec win32-msvc2010 -o Makefile ) && $(MAKE) -f Makefile debug
sub-FalconGame-debug:
	@if not exist FalconGame\ mkdir FalconGame\ & if not exist FalconGame\ exit 1
	@set MAKEFLAGS=$(MAKEFLAGS)
	cd FalconGame\ && ( if not exist Makefile $(QMAKE) "C:\Documents and Settings\mike\My Documents\Qt\PowerFalcon\FalconGame\FalconGame.pro" -spec win32-msvc2010 -o Makefile ) && $(MAKE) -f Makefile debug
debug: sub-FalconObjectMaker-debug sub-FalconModelSharedLib-debug sub-FalconWarMaker-debug sub-FalconGame-debug

sub-FalconObjectMaker-release:
	@if not exist FalconObjectMaker\ mkdir FalconObjectMaker\ & if not exist FalconObjectMaker\ exit 1
	@set MAKEFLAGS=$(MAKEFLAGS)
	cd FalconObjectMaker\ && ( if not exist Makefile $(QMAKE) "C:\Documents and Settings\mike\My Documents\Qt\PowerFalcon\FalconObjectMaker\FalconObjectMaker.pro" -spec win32-msvc2010 -o Makefile ) && $(MAKE) -f Makefile release
sub-FalconModelSharedLib-release:
	@if not exist FalconModelSharedLib\ mkdir FalconModelSharedLib\ & if not exist FalconModelSharedLib\ exit 1
	@set MAKEFLAGS=$(MAKEFLAGS)
	cd FalconModelSharedLib\ && ( if not exist Makefile $(QMAKE) "C:\Documents and Settings\mike\My Documents\Qt\PowerFalcon\FalconModelSharedLib\FalconModelSharedLib.pro" -spec win32-msvc2010 -o Makefile ) && $(MAKE) -f Makefile release
sub-FalconWarMaker-release:
	@if not exist FalconWarMaker\ mkdir FalconWarMaker\ & if not exist FalconWarMaker\ exit 1
	@set MAKEFLAGS=$(MAKEFLAGS)
	cd FalconWarMaker\ && ( if not exist Makefile $(QMAKE) "C:\Documents and Settings\mike\My Documents\Qt\PowerFalcon\FalconWarMaker\FalconWarMaker.pro" -spec win32-msvc2010 -o Makefile ) && $(MAKE) -f Makefile release
sub-FalconGame-release:
	@if not exist FalconGame\ mkdir FalconGame\ & if not exist FalconGame\ exit 1
	@set MAKEFLAGS=$(MAKEFLAGS)
	cd FalconGame\ && ( if not exist Makefile $(QMAKE) "C:\Documents and Settings\mike\My Documents\Qt\PowerFalcon\FalconGame\FalconGame.pro" -spec win32-msvc2010 -o Makefile ) && $(MAKE) -f Makefile release
release: sub-FalconObjectMaker-release sub-FalconModelSharedLib-release sub-FalconWarMaker-release sub-FalconGame-release

sub-FalconObjectMaker-check:
	@if not exist FalconObjectMaker\ mkdir FalconObjectMaker\ & if not exist FalconObjectMaker\ exit 1
	@set MAKEFLAGS=$(MAKEFLAGS)
	cd FalconObjectMaker\ && ( if not exist Makefile $(QMAKE) "C:\Documents and Settings\mike\My Documents\Qt\PowerFalcon\FalconObjectMaker\FalconObjectMaker.pro" -spec win32-msvc2010 -o Makefile ) && $(MAKE) -f Makefile check
sub-FalconModelSharedLib-check:
	@if not exist FalconModelSharedLib\ mkdir FalconModelSharedLib\ & if not exist FalconModelSharedLib\ exit 1
	@set MAKEFLAGS=$(MAKEFLAGS)
	cd FalconModelSharedLib\ && ( if not exist Makefile $(QMAKE) "C:\Documents and Settings\mike\My Documents\Qt\PowerFalcon\FalconModelSharedLib\FalconModelSharedLib.pro" -spec win32-msvc2010 -o Makefile ) && $(MAKE) -f Makefile check
sub-FalconWarMaker-check:
	@if not exist FalconWarMaker\ mkdir FalconWarMaker\ & if not exist FalconWarMaker\ exit 1
	@set MAKEFLAGS=$(MAKEFLAGS)
	cd FalconWarMaker\ && ( if not exist Makefile $(QMAKE) "C:\Documents and Settings\mike\My Documents\Qt\PowerFalcon\FalconWarMaker\FalconWarMaker.pro" -spec win32-msvc2010 -o Makefile ) && $(MAKE) -f Makefile check
sub-FalconGame-check:
	@if not exist FalconGame\ mkdir FalconGame\ & if not exist FalconGame\ exit 1
	@set MAKEFLAGS=$(MAKEFLAGS)
	cd FalconGame\ && ( if not exist Makefile $(QMAKE) "C:\Documents and Settings\mike\My Documents\Qt\PowerFalcon\FalconGame\FalconGame.pro" -spec win32-msvc2010 -o Makefile ) && $(MAKE) -f Makefile check
check: sub-FalconObjectMaker-check sub-FalconModelSharedLib-check sub-FalconWarMaker-check sub-FalconGame-check
install: install_subtargets  FORCE

uninstall:  uninstall_subtargets FORCE

FORCE:
