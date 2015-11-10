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

#include <QMainWindow>
#include <QMdiArea>
#include <QMenu>
#include <QMenuBar>
#include <QMap>
#include <QMetaObject>
#include <QtDebug>
#include <QDesktopWidget>
#include "falconmodelsharedlib_global.h"
class MODEL_LIBRARY Component;
class MODEL_LIBRARY Instruction;
class MODEL_LIBRARY InstructionList;
class MODEL_LIBRARY Model;
class MODEL_LIBRARY SubComponentList;
class MODEL_LIBRARY GLHandler;
class MenuHandler;
class GLViewer;
class ModelTree;
class InstructionListEdit;
class SubComponentListEdit;
class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  MainWindow(QWidget *parent = 0);
  ~MainWindow();
  QMdiArea* mdiArea;
  QMenuBar* m_menuBar;
  QMenu* new_menu;
  QMap<int, QMenu*> m_menu_hash;
  QMap<QString, QMenu*> m_menu_strings;
  QMap<QAction*, QMenu*> m_action_hash;
  void create_action(QString text, QMenu* parent_menu);
  QMenu* find_menu(QString text);
  QAction* new_action;
  MenuHandler* m_menuHandler;

  Model* currentModel();
  //GLHandler* glHandler() { if (!_glHandler) { _glHandler = new GLHandler(this); } return _glHandler; }
  GLHandler* _glHandler;
  Model* _model;
  ModelTree* _modelTree;
  GLViewer* m_viewer;
  InstructionListEdit* instructionListEdit;
  SubComponentListEdit* subComponentListEdit;
  Instruction* _selectedInstruction;
  QString _fileName;
signals:
  void signalParamCount(int count);
  void signalParamName(int id, QString name);
  void signalParamValue(int id, qreal value);
public slots:
  void slot_create_topLevel_menu(QString str_menu);
  void slot_action_triggered();
  void draw();
  void initViewer();
  void saveModel(QString fileName);
  void setGravityEnabled(bool gravityEnabled);
  void loadModel(QString fileName);
  void initModelTree();
  void setSelectedComponent(int id);
  void clearSelection();
  void setSelectedInstruction(int instructionId, int componentId);
  void setParamValue(int paramId, qreal value);
  void setModelSelected();
  void setSelectedInstructionList (int componentId);
   void removeInstruction(int parentComponent, Instruction* instruction, int instructionId);
   void setSelectedSubComponentList(int componentId);
   void updateModelTree();

private:

};

#endif // MAINWINDOW_H
