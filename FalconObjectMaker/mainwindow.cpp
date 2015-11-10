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

#include "falconmodelsharedlib.h"
#include "src_core/model.h"
#include "src_handlers/glhandler.h"
#include "src_core/instructionlist.h"
#include "src_core/component.h"
#include "src_core/instruction.h"
#include "src_core/mesh.h"
#include "src_core/subcomponentlist.h"
#include "src_ui/instructionlistedit.h"
#include "src_ui/subcomponentlistedit.h"
#include "mainwindow.h"
#include "src_menu/menuhandler.h"
#include "src_gfx/glviewer.h"
#include "src_ui/modeltree.h"


#include <glut.h>
MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent)
{


  //this->mdiArea = new QMdiArea(this);
  // mdiArea->resize(200, 800);
  //  this->setCentralWidget (this->mdiArea);



  this->_glHandler = new GLHandler(this);
  this->_model = new Model(this, _glHandler);
  //_model->initRootComponent ();




  this->m_menuHandler = new MenuHandler(this);
  this->connect (this->m_menuHandler, SIGNAL(signalSaveFile(QString)), this, SLOT(saveModel(QString)));
  this->connect (this->m_menuHandler, SIGNAL(signalSetGravity(bool)),this, SLOT(setGravityEnabled(bool)));
  this->connect (this->m_menuHandler, SIGNAL(signalOpenFile(QString)), this, SLOT(loadModel(QString)));
  this->m_menuBar = new QMenuBar(this);
  this->setMenuBar(m_menuBar);
  this->slot_create_topLevel_menu("File");
  this->create_action("New", this->find_menu("File"));
  this->create_action("Open", this->find_menu("File"));
  this->find_menu("File")->addSeparator();
  this->create_action("Save", this->find_menu("File"));
  this->find_menu("File")->addSeparator();
  this->create_action("Exit", this->find_menu("File"));
  this->slot_create_topLevel_menu("Edit");
  this->create_action("Undo", find_menu("Edit"));
  this->create_action("Redo", find_menu("Edit"));
  find_menu("Edit")->addSeparator();
  this->slot_create_topLevel_menu("Draw");
  this->create_action ("Cube", this->find_menu ("Draw"));
  this->slot_create_topLevel_menu ("Environment");
  this->create_action ("Enable Gravity", find_menu("Environment"));
  this->create_action ("Disable Gravity", find_menu("Environment"));
QFile lastFile(qApp->applicationDirPath ().append(QDir::separator ()).append("lastFile.dat"));
if (lastFile.exists ()) {
      this->loadModel (":/blank.pfm");
      _fileName = qApp->applicationDirPath ().append(QDir::separator()).append("models").append(QDir::separator()).append("blank.pfm");
  } else {
    this->loadModel (":/bird4.pfmdl");
    _fileName = qApp->applicationDirPath ().append(QDir::separator()).append("models").append(QDir::separator()).append("bird4.pfm");
  }

  this->m_menuHandler->_fileName = _fileName;
  this->m_menuBar->setEnabled (false);
  QTimer::singleShot(3000, this, SLOT(initViewer()));
}

MainWindow::~MainWindow()
{

}

Model* MainWindow::currentModel () {
  if (!_model) {
      _model = new Model(this, _glHandler);
    }
  return _model;
}

void MainWindow::slot_create_topLevel_menu(QString str_menu) {
  new_menu = new QMenu(str_menu, m_menuBar);
  int i = 1;
  while (this->m_menu_hash.keys().contains(i)) {
      i++;
    }
  this->m_menu_hash[i] = new_menu;
  this->m_menu_strings[str_menu] = new_menu;
  this->m_menuBar->addAction(new_menu->menuAction());
}
void MainWindow::create_action(QString text, QMenu* parent_menu) {
  new_action = new QAction(text, this);
  this->m_action_hash[new_action] = parent_menu;
  parent_menu->addAction(new_action);
  this->connect(new_action, SIGNAL(triggered()), this, SLOT(slot_action_triggered()));
}

QMenu* MainWindow::find_menu(QString text) {
  if (this->m_menu_strings.keys().contains(text)) {
      return m_menu_strings.value(text);
    } else {
      this->slot_create_topLevel_menu(text);
      return m_menu_strings.value(text);
    }
}
void MainWindow::slot_action_triggered() {
  QAction* action = qobject_cast<QAction*>(sender());
  if (this->m_action_hash.contains(action)) {
      qDebug() << "Action with Text" << action->text() << "Triggered!";

      const QMetaObject* metaObject = qobject_cast<MenuHandler*>(this->m_menuHandler)->metaObject();
      bool success =  metaObject->invokeMethod(
            m_menuHandler, QString("slot_action_%1").arg(QString(action->text()).replace(" ", "_", Qt::CaseInsensitive)).toLocal8Bit(), Qt::DirectConnection);
      if (!success) {
          qDebug() << "Failure to Invoke Action";
        }

    } else {
      qDebug() << "Unknown Action Triggered! ERROR!";
    }
}

void MainWindow::draw () {

 currentModel()->draw ();
//  if (_model) {
//      _model->draw ();
//    }

}


void MainWindow::initViewer () {
  //currentModel()->initDrawTest ();
if (_model) {
    //_model->initModelTree ();
  }
QTimer::singleShot(1000, this, SLOT(initModelTree()));



  QGLFormat fmt;
  // fmt.setOverlay(true);
  fmt.setDirectRendering(true);
  fmt.setSampleBuffers(true);
  fmt.setDoubleBuffer(true);
  fmt.setDepth(true);
  fmt.setSwapInterval(fmt.swapInterval() * 0.75);
  //fmt.setDepthBufferSize(fmt.depthBufferSize() * 1.25);
  fmt.setAccum (true);
  //fmt.setStencilBufferSize(fmt.stencilBufferSize() * 1.75);
  //fmt.setSamples(fmt.samples() * 1.75);
  this->m_viewer = new GLViewer(this, _glHandler, this);

  m_viewer->setMinimumWidth (( 0.75 * qApp->desktop ()->availableGeometry (this).width ()) - 510);
  m_viewer->setMinimumHeight (500);
  // m_viewer->resize(250, 250);
  m_viewer->setFormat(fmt);
  m_viewer->show ();
  m_viewer->makeCurrent();

  this->setCentralWidget(m_viewer);
}


void MainWindow::saveModel (QString fileName) {
  QFile file(fileName);
  if (file.open(QIODevice::WriteOnly)) {
      QTextStream out(&file);
      out << currentModel()->xml ();
      qDebug() << "No Compression Plain" << currentModel()->xml ().length ();
      for (int i=1; i<9; i++) {
          qDebug() << "Compression Plain Level" << i << ":" << qCompress(currentModel()->xml ().toLocal8Bit (), i).length ();
        }
      qDebug() << "No Compression Hex" << currentModel()->xml ().toLocal8Bit ().toHex ().length ();
      for (int i=1; i<9; i++) {
          qDebug() << "Compression Hex Level" << i << ":" << qCompress(currentModel()->xml ().toLocal8Bit ().toHex (), i).length ();
        }
      // printHex(currentModel()->xml().toLocal8Bit ());
    }
  file.close ();
  this->_fileName = fileName;
  this->m_menuHandler->_fileName = fileName;
  QFile settings(qApp->applicationDirPath ().append(QDir::separator ()).append("lastFile.dat"));
  if (settings.open(QIODevice::WriteOnly)) {
      QTextStream out(&settings);
      out << fileName;
      settings.close ();
    }

}
void MainWindow::setGravityEnabled(bool gravityEnabled) {
  if (this->m_viewer) {
      m_viewer->enableGravity = gravityEnabled;
      m_viewer->resetTimer = true;
    }
}


void MainWindow::loadModel (QString fileName) {
  QFile file(fileName);
  if (file.open (QIODevice::ReadOnly)) {
      this->_fileName = fileName;
      this->m_menuHandler->_fileName = fileName;
      QDomDocument doc;
      QString errorMsg;
      int errorLine;
      int errorColumn;
      doc.setContent (file.readAll (), false , &errorMsg, &errorLine, &errorColumn);
      //this->currentModel ()->loadXML (doc.toString());
      qDebug() << "Trying to Load" << doc.toString () << "to model" << qobject_cast<QObject*>(_model);
      //Model* model = new Model(this, this->_glHandler);
      //this->_model = model;
      QThread::msleep (500);
      _model->loadXML (doc.toString (0));
      QThread::msleep (1000);
      if (this->_fileName.left(1) != ":") {
          this->_modelTree->domDocument.setContent (_model->xml ());
          QThread::msleep (1000);
          this->_modelTree->populate ();
          this->m_viewer->rebuildDisplayLists = true;

        }
    // this->currentModel ()->updateModelTree ();

    }
  file.close ();
  QFile settings(qApp->applicationDirPath ().append(QDir::separator ()).append("lastFile.dat"));
  if (settings.open(QIODevice::WriteOnly)) {
      QTextStream out(&settings);
      out << fileName;
      settings.close ();
    }

}
void MainWindow::initModelTree () {
  this->_modelTree = new ModelTree(this);
  this->_modelTree->setWindowFlags(Qt::Window);
  this->_modelTree->domDocument.setContent (this->_model->xml());
  //this->_modelTree->show ();

  QDockWidget* dockWidget = new QDockWidget(this);
  dockWidget->setWidget (this->_modelTree);
  this->addDockWidget (Qt::RightDockWidgetArea, dockWidget);
  instructionListEdit = new InstructionListEdit(_modelTree->ui.scrollArea, _model->getComponentById (0)->instructionList (), _model);
      this->connect(instructionListEdit, SIGNAL(swapInstructions(int,int,int)), _modelTree, SLOT(swapInstructions(int,int,int)));
  instructionListEdit->setVisible (false);
  subComponentListEdit = new SubComponentListEdit(_modelTree->ui.scrollArea, _model->getComponentById (0)->subComponentList (), _model);
  subComponentListEdit->setVisible (false);
  this->_modelTree->populate ();
  this->connect (_modelTree, SIGNAL(signalSelectedComponent(int)), this, SLOT(setSelectedComponent(int)));
  this->connect (_modelTree, SIGNAL(signalSelectCleared()), this, SLOT(clearSelection()));
  this->connect (this, SIGNAL(signalParamCount(int)), _modelTree, SLOT(setParamCount(int)));
  this->connect (this, SIGNAL(signalParamName(int,QString)), _modelTree, SLOT(setParamName(int,QString)));
  this->connect (this, SIGNAL(signalParamValue(int,qreal)), _modelTree, SLOT(setParamValue(int,qreal)));
  this->connect (_modelTree, SIGNAL(signalSelectedInstruction(int,int)), this, SLOT(setSelectedInstruction(int,int)));
  this->connect (_modelTree, SIGNAL(signalParamValueChanged(int,qreal)), this, SLOT(setParamValue(int,qreal)));
  this->connect (_modelTree, SIGNAL(signalSelectedModel()), this, SLOT(setModelSelected()));
  this->connect (_modelTree, SIGNAL(signalSelectedInstructionList(int)), this, SLOT(setSelectedInstructionList(int)));
  this->connect (_modelTree, SIGNAL(signalSelectedSubComponentList(int)), this, SLOT(setSelectedSubComponentList(int)));
  this->connect (instructionListEdit, SIGNAL(addInstruction(int,Instruction*,int)), _modelTree, SLOT(addInstruction(int,Instruction*,int)));
  this->connect (instructionListEdit, SIGNAL(removeInstruction(int,Instruction*,int)), this, SLOT(removeInstruction(int,Instruction*,int)));
  this->connect (subComponentListEdit, SIGNAL(updateModelTree()), this, SLOT(updateModelTree()));
   this->connect (instructionListEdit, SIGNAL(updateModelTree()), this, SLOT(updateModelTree()));
  this->m_menuBar->setEnabled (true);
}
void MainWindow::setSelectedComponent (int id) {
  foreach (Component* component, _model->findComponentsExcept (id)) {
      component->setSelected (false);


    }
  _model->getComponentById (id)->setSelected (true);
  _model->getComponentById (id)->isExpanded = true;




}
void MainWindow::clearSelection () {
  setSelectedComponent(0);
  emit this->signalParamCount (0);

}
void MainWindow::setSelectedInstruction (int instructionId, int componentId) {
  _modelTree->ui.scrollAreaWidgetContents->setVisible (true);
  this->instructionListEdit->setVisible (false);
  this->subComponentListEdit->setVisible(false);
  this->setSelectedComponent (componentId);
  Component* component = _model->getComponentById(componentId);
  InstructionList* instructionList = component->instructionList ();
  Instruction* instruction = instructionList->_instructions.value (instructionId);
  this->_selectedInstruction = instruction;
  emit this->signalParamCount (instruction->args ().count ());
  for (int i=0; i<instruction->args ().count(); i++) {
      qreal value = instruction->args ().at(i);
      QString name = instruction->paramNames.value(i, "No Name");
      emit this->signalParamName (i, name);
      emit this->signalParamValue (i, value);

    }
}
void MainWindow::setParamValue (int paramId, qreal value) {
  if (this->_selectedInstruction != 0) {
      QList<qreal> args;
      args << _selectedInstruction->args ();
      QList<qreal> newArgs;
      for (int i=0; i<args.count (); i++) {
          if (i != paramId) {
              newArgs << args.at(i);
            } else {
              newArgs << value;
            }
        }
      this->_selectedInstruction->slot_set_args (newArgs);
    }
}
void MainWindow::setModelSelected () {
  foreach (Component* component, _model->findComponentsExcept (0)) {
      component->setSelected (true);


    }
  _model->getComponentById (0)->setSelected (true);
}
void MainWindow::setSelectedInstructionList (int componentId) {
  if (this->_modelTree)  {
      if (this->instructionListEdit) {
          _modelTree->ui.scrollAreaWidgetContents->setVisible (false);
          instructionListEdit->_instructionList = _model->getComponentById(componentId)->instructionList ();
          instructionListEdit->populateInstructions ();
          subComponentListEdit->setVisible (false);
          instructionListEdit->resize(_modelTree->ui.scrollArea->size ());
          instructionListEdit->_instructionList->isExpanded = true;
          instructionListEdit->setVisible (true);

          //modelTree->ui.scrollArea->setWidget (instructionListEdit);
          // instructionListEdit->ui.setupUi (instructionListEdit);
        }
    }

}
void MainWindow::removeInstruction (int parentComponent, Instruction *instruction, int instructionId) {
 this->_modelTree->domDocument.setContent(_model->xml());
  QThread::msleep(500);
  this->_modelTree->populate ();
}
 void MainWindow::setSelectedSubComponentList(int componentId) {
   if (this->_modelTree)  {
       if (this->subComponentListEdit) {
           _modelTree->ui.scrollAreaWidgetContents->setVisible (false);
           instructionListEdit->setVisible (false);
           subComponentListEdit->resize(_modelTree->ui.scrollArea->size ());
           subComponentListEdit->_subComponentList = _model->getComponentById (componentId)->subComponentList ();
           subComponentListEdit->populateComponents ();
           subComponentListEdit->setVisible (true);
           subComponentListEdit->_subComponentList->isExpanded = true;
         }
     }
 }
void MainWindow::updateModelTree () {
  this->_modelTree->domDocument.setContent(_model->xml());
   QThread::msleep(500);
   this->_modelTree->populate ();
   this->m_viewer->rebuildDisplayLists = true;
}
