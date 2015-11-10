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

#ifndef COMPONENT_H
#define COMPONENT_H

#include <QObject>
#include <QCoreApplication>
#include <QtDebug>
#include <QtXml/QtXml>
//#include <qglviewer.h>
#include <manipulatedFrame.h>
#include <camera.h>
#include "../falconmodelsharedlib_global.h"


class Model;
class SubComponentList;
class Instruction;
class InstructionList;
class GLHandler;
//class MainWindow;
//class XMLBuilder;
//class GLViewer;
#include "../falconmodelsharedlib_global.h"


class MODEL_LIBRARY Component : public QObject
{
  Q_OBJECT
    Q_PROPERTY(bool _drawSubComponentListFirst READ drawSubComponentListFirst WRITE setDrawSubComponentListFirst)
     Q_PROPERTY(int _componentId READ componentId WRITE setComponentId)
  Q_PROPERTY(bool _isSelected READ isSelected WRITE setSelected )

public:
   Component(QObject *parent = 0, Model* iModel = 0, GLHandler* iGLHandler = 0);
   Model* model();
   SubComponentList* subComponentList();
   InstructionList* instructionList();
   bool drawSubComponentListFirst();
   GLHandler* glHandler();
     SubComponentList* _subComponentList;

     Model* _model;

     InstructionList* _instructionList;
     bool _drawSubComponentListFirst;
     GLHandler* _glHandler;

     QString xml();
     int _componentId;
     int componentId() { if (_componentId) { return _componentId; } return 0; }
     bool _isSelected;
     bool isSelected() { return _isSelected; }
     qglviewer::ManipulatedFrame componentFrame;
     bool isExpanded;
signals:

public slots:
   void setModel(Model* iModel);
   void initSubComponentList();
   void initInstructionList();
   void setDrawSubComponentListFirst(bool value);
   void setComponentId(int id) { _componentId = id; }
   void draw();
   void setSelected(bool i_selected) { _isSelected = i_selected; }

private:


};

#endif // COMPONENT_H
