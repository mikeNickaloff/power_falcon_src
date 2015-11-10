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

#ifndef MODEL_H
#define MODEL_H

#include <QObject>
#include <QCoreApplication>
#include <QtXml/QtXml>
#include <QtXmlPatterns/QtXmlPatterns>
#include <QVector3D>
#include <QDockWidget>
#include "../falconmodelsharedlib_global.h"
class Component;
class Instruction;
class SubComponentList;
class InstructionList;
class Mesh;
class GLHandler;
//class MainWindow;
//class ModelTree;
//class GLViewer;
//class InstructionListEdit;
class MODEL_LIBRARY Model : public QObject
{
  Q_OBJECT
public:
   Model(QObject *parent = 0, GLHandler* iGLHandler = 0/*, MainWindow* iMainWindow = 0*/);
   QString modelName();
   Component* rootComponent();

   GLHandler* glHandler();
  // MainWindow* mainWindow();
   Instruction* createInstruction(QString cmd, QList<qreal> args);
   Component* createComponent(QObject *parent = 0);
   Component* newComponent;
   Instruction* newInstruction;
   QString _modelName;
   Component* _rootComponent;



   Component* getComponentById(int id);
   QList<Component*> findComponentsExcept(int id);
   GLHandler* _glHandler;
   //MainWindow* _mainWindow;
   int nextComponentId();
   Mesh* newMesh;
   Mesh* createMesh(QVector<QVector3D> i_grid);

   QString xml();
   //ModelTree* modelTree;
  // InstructionListEdit* instructionListEdit;

signals:
   void signalParamCount(int count);
   void signalParamName(int id, QString name);
   void signalParamValue(int id, qreal value);
public slots:
   void setModelName(QString newName);
   void setRootComponent(Component* component);
   void initRootComponent();
   void draw();
  // void initDrawTest();

   //void initModelTree();
 //  void setSelectedComponent(int id);
  // void clearSelection();
  // void setSelectedInstruction(int instructionId, int componentId);
  // void setParamValue(int paramId, qreal value);
  // void setModelSelected();
   void loadXML(QString xmlData);
   void parseComponentXML(QDomElement &componentElement, Component* targetComponent);
  // void setSelectedInstructionList(int componentId);
  // void updateModelTree();


private:
   Instruction* _selectedInstruction;

};

#endif // MODEL_H
