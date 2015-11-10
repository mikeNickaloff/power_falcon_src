/****************************************************************************
**
** Author: Mike Nickaloff
**
** Contact: seppfuv@gmail.com  (http://www.datafault.net)
**
**
** GNU General Public License Usage
** This file may be used under the terms of the GNU General
** Public License version 3.0 as published by the Free Software Foundation
** and appearing in the file LICENSE.GPL included in the packaging of this
** file. Please review the following information to ensure the GNU General
** Public License version 3.0 requirements will be met:
** http://www.gnu.org/copyleft/gpl.html.
**
**
****************************************************************************/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "../falconmodelsharedlib_global.h"
#include <QMainWindow>
#include <QObject>
#include <QMap>
#include <QMetaObject>
#include <QDesktopWidget>
#include <QVector3D>
#include <QDomElement>

class MODEL_LIBRARY Component;
class MODEL_LIBRARY Instruction;
class MODEL_LIBRARY InstructionList;
class MODEL_LIBRARY Model;
class MODEL_LIBRARY SubComponentList;
class MODEL_LIBRARY GLHandler;
class MODEL_LIBRARY Level;
class MODEL_LIBRARY LevelObject;
class GLViewer;
class MenuHandler;
class AddLevelObject;
class LevelObjectEditor;
class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  MainWindow(QWidget *parent = 0);
  ~MainWindow();
  GLHandler* _glHandler;
  Model* _model;
  GLViewer* m_viewer;
  QStatusBar* sb;
  QMenuBar* m_menuBar;
  QMenu* new_menu;
  QMap<int, QMenu*> m_menu_hash;
  QMap<QString, QMenu*> m_menu_strings;
  QMap<QAction*, QMenu*> m_action_hash;
  void create_action(QString text, QMenu* parent_menu);
  QMenu* find_menu(QString text);
  QAction* new_action;
  MenuHandler* m_menuHandler;
  Level* _level;
 // LevelObject* levelObject;
  QHash<int, LevelObject*> levelObjects;
  int m_objectEditorSelectedLevelObjectIdx;
signals:
  void sendMsgToSb(QString message);
  void announcelevelObjectProperties(QVector3D translation, QVector3D rotation, QVector3D scale);
public slots:
  void initViewer();
  void draw();
  void drawNames();
  void sbMsg(QString msg);
  void slot_create_topLevel_menu(QString str_menu);
  void slot_action_triggered();
  void showResizeLevelDialog();
  void showAddNewLevelObject();
  void showLevelObjectEditor();
  void requestedLevelObjectProperties(int objIdx);
  void informPropertiesChanged(QVector3D trans, QVector3D rot, QVector3D scale);
  void saveLevel(QString fn);
  void loadLevel(QString fn);
  QVector3D elementToVector3D(QDomElement &elem);
};

#endif // MAINWINDOW_H
