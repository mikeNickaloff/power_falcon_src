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

#include "model.h"
#include "component.h"
#include "instruction.h"
#include "instructionlist.h"
#include "subcomponentlist.h"
#include "mesh.h"
#include "../src_handlers/glhandler.h"
//#include "../mainwindow.h"
#include <QtDebug>
#include <QtXmlPatterns/QtXmlPatterns>
#include <QXmlQuery>
//#include "../src_xml/qobjectxmlmodel.h"
//#include "../src_ui/modeltree.h"
//#include "../src_gfx/glviewer.h"
//#include "../src_ui/instructionlistedit.h"
Model::Model(QObject *parent, GLHandler *iGLHandler) :
  QObject(parent), _glHandler(iGLHandler)
{
}
QString Model::modelName () {
  if (this->_modelName.length () > 0) {
      return this->_modelName;
    }  else {
      return "No Name";
    }
}

Component* Model::rootComponent() {
  if (!_rootComponent) {
      initRootComponent();
    }
  return _rootComponent;
}

GLHandler* Model::glHandler () {
  {
    if (!_glHandler) {
        _glHandler = new GLHandler(this);
      }
    return _glHandler;
  }
}
//MainWindow* Model::mainWindow () {
//  {
//    if (!_mainWindow) {
//        // qApp->exit (0);
//      }
//    return _mainWindow;
//  }
//}

Instruction* Model::createInstruction(QString cmd, QList<qreal> args) {
  newInstruction = new Instruction(this, glHandler());
  if (cmd.left (5).toLower () != "slot_") {
      cmd.prepend ("slot_");
    }
  newInstruction->setCommand (cmd);
  newInstruction->setArgs (args);
  return newInstruction;
}

Component* Model::createComponent(QObject *parent)
{
  int nextid = nextComponentId();
  newComponent = new Component(parent, this, glHandler());
  newComponent->setComponentId (nextid);
  newComponent->setObjectName (QString("%1").arg(nextid));

  return newComponent;
}

int Model::nextComponentId () {
  if (!this->_rootComponent) {
      return 0;
    } else {
      QDomDocument doc;
      QString rootXml; rootXml.append("<model> \n");
      rootXml.append(rootComponent()->xml ());
      rootXml.append("\n</model>");
      doc.setContent (rootXml);

      int rv = doc.elementsByTagName ("Component").length ();
      int maxVal = 0;
      for (int i=0; i<doc.elementsByTagName ("Component").length (); i++) {
          QDomElement element = doc.elementsByTagName("Component").item(i).toElement ();
          if (element.hasAttribute ("id")) {
              int id = element.attribute ("id").toInt();
              if (id > maxVal) {
                  maxVal = id;
                }
            }
        }
      maxVal++; rv = maxVal;
      // qDebug() << "new component Id" << rv;
      return rv;
    }
  return -1;
}

Component* Model::getComponentById(int id) {
  if (id > this->nextComponentId ()) {
      qDebug() << "Invalid Component from GetComponentById" << "(" << id <<")";
      return 0;
    } else {
      if (id == 0) {
          return this->rootComponent ();
        } else {
          Component* component = this->rootComponent ()->findChild<Component*>(QString("%1").arg(id), Qt::FindChildrenRecursively);
          return component;
        }
    }
  return 0;
}

QList<Component*> Model::findComponentsExcept(int id) {
  QList<Component*> rv;
  for (int i=0; i<this->nextComponentId (); i++) {
      if (i < nextComponentId()) {
          Component* component = getComponentById(i);
          if (component != 0) {
              if (component->componentId () != id) {
                  rv << component;
                }
            }
        }
    }

  return rv;
}



Mesh* Model::createMesh (QVector<QVector3D> i_grid) {
  newMesh = new Mesh(this, this->glHandler ());
  if (i_grid.length () > 0) {
      //newMesh->slot_set_grid (i_grid);
    } else {
      //newMesh->slot_set_grid (newMesh->make3dVectorList (newMesh->grid6x6[0][0][0]&));
    }
  return newMesh;
}


QString Model::xml() {

  QDomDocument doc;
  QString rootXml; rootXml.append("<model> \n");
  rootXml.append(rootComponent()->xml ());
  rootXml.append("\n</model>");
  doc.setContent (rootXml);
  return doc.toString();

}

void Model::setModelName (QString newName) {
  this->_modelName = newName;
}
void Model::setRootComponent (Component *component) {
  this->_rootComponent = component;

}

void Model::initRootComponent () {
  newComponent = new Component(this, this, glHandler());
  newComponent->setComponentId (0);
  newComponent->setObjectName (QString("0"));

  // newComponent = createComponent(this);
  setRootComponent(newComponent);

}
void Model::draw () {
  Component* component = this->rootComponent ();

  component->draw ();
}



/* DRAW TEST --  Creates the basic elements that a model would have to verify they are working
 *
 * Probably should be removed once the test is completed */

//void Model::initDrawTest () {









//  QFile file(qApp->applicationDirPath ().append (QDir::separator ()).append("models").append(QDir::separator ()).append("enemybird.pfmdl"));
//  if (file.open (QIODevice::ReadOnly)) {
//      QDomDocument doc;
//      doc.setContent (file.readAll (), false);
//      this->loadXML (doc.toString());
//      this->initModelTree ();

//    }

//  newComponent = this->createComponent (0);
//  this->getComponentById (0)->subComponentList ()->addComponent (newComponent);
//  newComponent = this->createComponent (0);
//  this->getComponentById (0)->subComponentList ()->addComponent (newComponent);
//  newComponent = this->createComponent (0);
//  this->getComponentById (0)->subComponentList ()->addComponent (newComponent);
//  newComponent = this->createComponent (0);
//  this->getComponentById (0)->subComponentList ()->addComponent (newComponent);
//this->updateModelTree ();



//}
//void Model::initModelTree () {

//  QDomDocument doc;
//  QString rootXml; rootXml.append("<model> \n");
//  rootXml.append(rootComponent()->xml ());
//  rootXml.append("\n</model>");
//  doc.setContent (rootXml);
//  qDebug() << doc.toString (1);
//  modelTree = new ModelTree(0);
//  modelTree->show ();
//  modelTree->domDocument.setContent (doc.toString ());
//  modelTree->populate ();
//  this->connect (modelTree, SIGNAL(signalSelectedComponent(int)), this, SLOT(setSelectedComponent(int)));
//  this->connect (modelTree, SIGNAL(signalSelectCleared()), this, SLOT(clearSelection()));
//  this->connect (this, SIGNAL(signalParamCount(int)), modelTree, SLOT(setParamCount(int)));
//  this->connect (this, SIGNAL(signalParamName(int,QString)), modelTree, SLOT(setParamName(int,QString)));
//  this->connect (this, SIGNAL(signalParamValue(int,qreal)), modelTree, SLOT(setParamValue(int,qreal)));
//  this->connect (modelTree, SIGNAL(signalSelectedInstruction(int,int)), this, SLOT(setSelectedInstruction(int,int)));
//  this->connect (modelTree, SIGNAL(signalParamValueChanged(int,qreal)), this, SLOT(setParamValue(int,qreal)));
//  this->connect (modelTree, SIGNAL(signalSelectedModel()), this, SLOT(setModelSelected()));
//  this->connect (modelTree, SIGNAL(signalSelectedInstructionList(int)), this, SLOT(setSelectedInstructionList(int)));
//  QDockWidget* dockWidget = new QDockWidget(mainWindow());
//  dockWidget->setWidget (modelTree);
//  this->mainWindow ()->addDockWidget (Qt::RightDockWidgetArea, dockWidget);
//  instructionListEdit = new InstructionListEdit(modelTree->ui.scrollArea, this->getComponentById (0)->instructionList (), this);
//  instructionListEdit->setVisible (false);

//}

//void Model::setSelectedComponent (int id) {
//  foreach (Component* component, this->findComponentsExcept (id)) {
//      component->setSelected (false);


//    }
//  this->getComponentById (id)->setSelected (true);




//}
//void Model::clearSelection () {
//  setSelectedComponent(0);
//  emit this->signalParamCount (0);

//}
//void Model::setSelectedInstruction (int instructionId, int componentId) {
//  modelTree->ui.scrollAreaWidgetContents->setVisible (true);
//  this->instructionListEdit->setVisible (false);
//  this->setSelectedComponent (componentId);
//  Component* component = getComponentById(componentId);
//  InstructionList* instructionList = component->instructionList ();
//  Instruction* instruction = instructionList->_instructions.value (instructionId);
//  this->_selectedInstruction = instruction;
//  emit this->signalParamCount (instruction->args ().count ());
//  for (int i=0; i<instruction->args ().count(); i++) {
//      qreal value = instruction->args ().at(i);
//      QString name = instruction->paramNames.value(i, "No Name");
//      emit this->signalParamName (i, name);
//      emit this->signalParamValue (i, value);

//    }
//}
//void Model::setParamValue (int paramId, qreal value) {
//  if (this->_selectedInstruction != 0) {
//      QList<qreal> args;
//      args <<_selectedInstruction->args ();
//      QList<qreal> newArgs;
//      for (int i=0; i<args.count (); i++) {
//          if (i != paramId) {
//              newArgs << args.at(i);
//            } else {
//              newArgs << value;
//            }
//        }
//      this->_selectedInstruction->slot_set_args (newArgs);
//    }
//}
//void Model::setModelSelected () {
//  foreach (Component* component, this->findComponentsExcept (0)) {
//      component->setSelected (true);


//    }
//  this->getComponentById (0)->setSelected (true);
//}
void Model::loadXML (QString xmlData) {
  QDomDocument doc;
  doc.setContent (xmlData);
  if (doc.isDocument ()) {
      QDomElement modelElement = doc.firstChildElement("model");
      QDomElement rootElement = modelElement.firstChildElement ("Component");
      this->initRootComponent ();
      this->parseComponentXML (rootElement, this->rootComponent ());

    }
}
void Model::parseComponentXML(QDomElement &componentElement, Component* targetComponent) {
  QDomElement instructionListElement = componentElement.firstChildElement ("InstructionList");
  targetComponent->initInstructionList ();
  targetComponent->initSubComponentList ();
  // newComponent->initInstructionList ();
  targetComponent->instructionList ()->parseInstructionListElementXML (instructionListElement, targetComponent);
  // newComponent->initSubComponentList ();
  QDomElement subComponentListElement = componentElement.firstChildElement ("SubComponentList");
  //QDomNodeList subComponentElements = subComponentListElement.elementsByTagName ("Component");
  //for (int i=0; i<subComponentElements.length(); i++) {
  for(QDomNode n = subComponentListElement.firstChild(); !n.isNull(); n = n.nextSibling())
    {
      QDomElement subComponentElement = n.toElement();
      SubComponentList* list = targetComponent->subComponentList ();
      newComponent = this->createComponent (rootComponent());
      list->addComponent (newComponent);
      this->parseComponentXML (subComponentElement, newComponent);
    }
  //  targetComponent->subComponentList ()->addComponent (newComponent);

}
//void Model::setSelectedInstructionList (int componentId) {
//  if (this->modelTree)  {
//      if (this->instructionListEdit) {
//          modelTree->ui.scrollAreaWidgetContents->setVisible (false);
//          instructionListEdit->_instructionList = getComponentById(componentId)->instructionList ();
//          instructionListEdit->populateInstructions ();

//          instructionListEdit->resize(modelTree->ui.scrollArea->size ());

//          instructionListEdit->setVisible (true);

//          //modelTree->ui.scrollArea->setWidget (instructionListEdit);
//          // instructionListEdit->ui.setupUi (instructionListEdit);
//        }
//    }

//}
//void Model::updateModelTree () {
//  QDomDocument doc;
//  QString rootXml; rootXml.append("<model> \n");
//  rootXml.append(rootComponent()->xml ());
//  rootXml.append("\n</model>");
//  doc.setContent (rootXml);
// // qDebug() << doc.toString (1);
//  //  modelTree = new ModelTree(0);
//  modelTree->show ();
//  modelTree->domDocument.setContent (doc.toString ());
//  modelTree->populate ();

// // if (instructionListEdit->instructionList()) {
// //     int componentId = instructionListEdit->_instructionList->component ()->componentId ();
// //     modelTree->expandInstructionList (componentId);
// //   }

//}
