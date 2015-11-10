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
#include <src_core/model.h>
#include <src_handlers/glhandler.h>
#include <src_core/instructionlist.h>
#include "mainwindow.h"
#include "src_gfx/glviewer.h"
#include <src_core/component.h>
#include <src_level/level.h>
#include <src_level/levelobject.h>
#include <QtDebug>
#include <QtOpenGL/QGLFormat>
#include <QStatusBar>
#include <QMenuBar>
#include <QMenu>
#include <QVector3D>
#include "src_menu/menuhandler.h"


#include "src_ui/addlevelobject.h"
#include "src_ui/levelobjecteditor.h"
#include <glut.h>
#include <QInputDialog>

MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent)
{
  this->_glHandler = new GLHandler(this);
  this->_model = new Model(this, _glHandler);
  _model->initRootComponent ();
  qDebug() << _model->xml ();
  QTimer::singleShot (50, this, SLOT(initViewer()));
  sb = new QStatusBar(this);
  this->connect (this, SIGNAL(sendMsgToSb(QString)), sb, SLOT(showMessage(QString)));
  this->setStatusBar (sb);

  this->m_menuHandler = new MenuHandler(this);
  this->connect (this->m_menuHandler, SIGNAL(signalSaveFile(QString)), this, SLOT(saveLevel(QString)));
  this->connect (this->m_menuHandler, SIGNAL(signalSetGravity(bool)),this, SLOT(setGravityEnabled(bool)));
  this->connect (this->m_menuHandler, SIGNAL(signalOpenFile(QString)), this, SLOT(loadLevel(QString)));
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
  this->slot_create_topLevel_menu("Level");
  this->create_action ("Add New Level Object", this->find_menu ("Level"));
  this->create_action ("Open Level Object Editor", this->find_menu ("Level"));
  this->find_menu ("Level")->addSeparator ();
  this->create_action ("Resize Level", this->find_menu ("Level"));
  this->slot_create_topLevel_menu ("Environment");
  this->create_action ("Enable Gravity", find_menu("Environment"));
  this->create_action ("Disable Gravity", find_menu("Environment"));

  connect(this->m_menuHandler, SIGNAL(signalResizeLevelRequested()), this, SLOT(showResizeLevelDialog()));
  connect(this->m_menuHandler, SIGNAL(signalAddNewLevelObject()), this, SLOT(showAddNewLevelObject()));
  connect(this->m_menuHandler, SIGNAL(signalOpenLevelObjectEditor()), this, SLOT(showLevelObjectEditor()));
  _level = new Level(this);
  //this->addLevelDialog = new AddLevelObject(this, _level);
}

MainWindow::~MainWindow()
{

}



void MainWindow::initViewer () {
  QFile file(qApp->applicationDirPath ().append (QDir::separator ()).append("models").append(QDir::separator ()).append("enemybird.pfmdl"));
  if (file.open (QIODevice::ReadOnly)) {
      QDomDocument doc;
      doc.setContent (file.readAll (), false);
      this->_model->loadXML (doc.toString());

    }

  foreach (Component* component, this->_model->findComponentsExcept (0)) {
      component->setSelected (true);


    }
  this->_model->getComponentById (0)->setSelected (true);


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
  m_viewer->enableGravity = true;
  m_viewer->resetTimer = true;
  this->connect (m_viewer, SIGNAL(sbMsg(QString)), this, SLOT(sbMsg(QString)));
}
void MainWindow::draw () {

  QHash<int, LevelObject*>::const_iterator o;
  o = this->levelObjects.constBegin ();
  while (o != levelObjects.constEnd ()) {
      LevelObject* obj = o.value ();
      int key = o.key ();


      glPushAttrib(GL_ALL_ATTRIB_BITS);
      glPushMatrix();
      QVector3D _translation = obj->_translation;
      QVector3D _rotation = obj->_rotation;
      QVector3D _scale = obj->_scale;
      glTranslatef(_translation.x(), _translation.y(), _translation.z());
      glPushMatrix();
      glRotatef(_rotation.x (), 1.0, 0.0, 0.0);
      glRotatef(_rotation.y (), 0.0, 1.0, 0.0);
      glRotatef(_rotation.z (), 0.0, 0.0, 1.0);
      glScalef(_scale.x(), _scale.y(), _scale.z());
      glPushMatrix();

      obj->_model->draw ();

      glPopMatrix();
      glPopMatrix();
      glPopMatrix();
      glPopAttrib();

      o++;
    }

}
void MainWindow::drawNames () {

  QHash<int, LevelObject*>::const_iterator o;
  o = this->levelObjects.constBegin ();
  while (o != levelObjects.constEnd ()) {
      LevelObject* obj = o.value ();
      int key = o.key ();
      glPushMatrix();
      glPushName((GLuint)key);
      glPushAttrib(GL_ALL_ATTRIB_BITS);
      glPushMatrix();
      QVector3D _translation = obj->_translation;
      QVector3D _rotation = obj->_rotation;
      QVector3D _scale = obj->_scale;
      glTranslatef(_translation.x(), _translation.y(), _translation.z());
      glPushMatrix();
      glRotatef(_rotation.x (), 1.0, 0.0, 0.0);
      glRotatef(_rotation.y (), 0.0, 1.0, 0.0);
      glRotatef(_rotation.z (), 0.0, 0.0, 1.0);
      glScalef(_scale.x(), _scale.y(), _scale.z());
      glPushMatrix();



      obj->_model->draw ();

      glPopMatrix();
      glPopMatrix();
      glPopMatrix();
      glPopAttrib();

      glPopName();
      glPopMatrix();
      o++;
    }

}
void MainWindow::sbMsg (QString msg) {
  emit this->sendMsgToSb (msg);
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
void MainWindow::showResizeLevelDialog () {
  QInputDialog* dialog = new QInputDialog(this);
  dialog->setInputMode(QInputDialog::IntInput);
  dialog->setIntMinimum (10);
  dialog->setIntMaximum (999999);

  dialog->setIntStep (50);
  dialog->setIntValue ((int)this->m_viewer->sceneRadius ());
  //this->connect (dialog, SIGNAL(doubleValueChanged(double)), m_viewer, SLOT(slot_resizeScene(double)));
  this->connect (dialog, SIGNAL(intValueChanged(int)), m_viewer, SLOT(slot_resizeScene(int)));
  dialog->show ();
}
void MainWindow::showAddNewLevelObject () {
  // int assignmentID;



  qDebug() << "Added new Object" << _level->levelObjects.count();
  LevelObject* levelObject = new LevelObject(this, this->_glHandler);

  levelObject->_model = new Model(this, this->_glHandler);
  levelObject->_model->loadXML (this->_model->xml ());


  qDebug() << "Set Default Model";
  qDebug() << levelObject->_model->xml ();
  int objCount = levelObjects.count ();
  this->levelObjects[objCount] = levelObject;
  //if (!addLevelDialog) {
  AddLevelObject* addLevelDialog;

  addLevelDialog = new AddLevelObject(this, _level);
  // disconnect (addLevelDialog, SIGNAL(xmlChanged(QString)));
  qDebug() << "Created new Dialog";
  //this->addDockWidget (Qt::RightDockWidgetArea, addLevelDialog);
  // }

  connect(addLevelDialog, SIGNAL(xmlChanged(QString)), levelObject->_model, SLOT(loadXML(QString)));
  qDebug() << "Connected Level Object to Dialog";
  addLevelDialog->show ();
}
void MainWindow::showLevelObjectEditor () {
  LevelObjectEditor* objEditor = new LevelObjectEditor(this);
  this->connect (objEditor, SIGNAL(requestPropertiesForLevelObject(int)), this, SLOT(requestedLevelObjectProperties(int)));
  this->connect (this, SIGNAL(announcelevelObjectProperties(QVector3D,QVector3D,QVector3D)), objEditor, SLOT(updateLevelObjectProperties(QVector3D,QVector3D,QVector3D)));
  this->connect(objEditor, SIGNAL(announcePropertiesChanged(QVector3D,QVector3D,QVector3D)), this, SLOT(informPropertiesChanged(QVector3D,QVector3D,QVector3D)));
  this->m_objectEditorSelectedLevelObjectIdx = -1;
  this->addDockWidget (Qt::RightDockWidgetArea, objEditor);
  QHash<int, LevelObject*>::const_iterator o;
  o = levelObjects.constBegin();
  while (o != levelObjects.constEnd ()) {
      int key = o.key ();
      objEditor->addLevelObjectById (key);
      o++;
    }
}
void MainWindow::requestedLevelObjectProperties (int objIdx) {
  if (objIdx == -1) {
      this->m_objectEditorSelectedLevelObjectIdx = -1;
    } else {
      QHash<int, LevelObject*>::const_iterator o;
      o = levelObjects.constBegin();
      while (o != levelObjects.constEnd ()) {
          int key = o.key ();
          if (key == objIdx) {
              LevelObject* obj = o.value();
              QVector3D trans = obj->_translation;
              QVector3D rot = obj->_rotation;
              QVector3D scale = obj->_scale;
              emit this->announcelevelObjectProperties (trans, rot, scale);
              this->m_objectEditorSelectedLevelObjectIdx = key;
            }
          o++;
        }
    }
}
void MainWindow::informPropertiesChanged (QVector3D trans, QVector3D rot, QVector3D scale) {
  if (this->m_objectEditorSelectedLevelObjectIdx != -1) {
      int objIdx = this->m_objectEditorSelectedLevelObjectIdx;
      QHash<int, LevelObject*>::const_iterator o;
      o = levelObjects.constBegin();
      while (o != levelObjects.constEnd ()) {
          int key = o.key ();
          if (key == objIdx) {
              LevelObject* obj = o.value();
              obj->_translation = trans;
              obj->_rotation = rot;
              obj->_scale = scale;
            }
          o++;
        }
    }
}
void MainWindow::saveLevel (QString fn) {
  QFile file(fn);
  if (file.open(QIODevice::WriteOnly)) {
      QTextStream out(&file);
      out << "<level>";
      QHash<int, LevelObject*>::const_iterator o;
      o = levelObjects.constBegin();
      while (o != levelObjects.constEnd ()) {
          int key = o.key ();

              LevelObject* obj = o.value();
              out << obj->xml (key);
              o++;
            }

      out << "</level>";

    }
  file.close ();
  //this->_fileName = fileName;
  this->m_menuHandler->_fileName = fn;
  QFile settings(qApp->applicationDirPath ().append(QDir::separator ()).append("lastFile.dat"));
  if (settings.open(QIODevice::WriteOnly)) {
      QTextStream out(&settings);
      out << fn;
      settings.close ();
    }
}
void MainWindow::loadLevel (QString fn) {
  QFile file(fn);
  if (file.open(QIODevice::ReadOnly)) {
      QDomDocument doc;
      file.seek(0);
      doc.setContent (file.readAll ());
      QDomNodeList list = doc.elementsByTagName ("LevelObject");
      for (int i=0; i<list.length (); i++) {
          QDomElement lvlObjElement = list.item (i).toElement ();
          QDomElement transElement = lvlObjElement.firstChildElement ("translation");
          QVector3D translationVal = elementToVector3D(transElement);
          QDomElement rotElement = lvlObjElement.firstChildElement ("rotation");
          QVector3D rotationVal = elementToVector3D(rotElement);
          QDomElement scaleElement = lvlObjElement.firstChildElement ("scale");
          QVector3D scaleVal = elementToVector3D(scaleElement);
          QDomDocument mdoc;
          QDomElement modelElem = mdoc.createElement ("model");
          QDomElement modelElement = lvlObjElement.firstChildElement ("model");
          mdoc.appendChild (modelElement);
           LevelObject* levelObject = new LevelObject(this, this->_glHandler);
           levelObject->_translation = translationVal;
           levelObject->_rotation = rotationVal;
           levelObject->_scale = scaleVal;
           levelObject->_model = new Model(this, this->_glHandler);
           levelObject->_model->loadXML (mdoc.toString (0));
           qDebug() << "Loaded Level ID" << lvlObjElement.attribute ("id");
           qDebug() << levelObject->xml (lvlObjElement.attribute("id").toInt());
           this->levelObjects[lvlObjElement.attribute("id").toInt()] = levelObject;

        }
    }
}
QVector3D MainWindow::elementToVector3D(QDomElement &elem) {
  QVector3D rv;
  if (elem.elementsByTagName ("x").count() != 0) {
      rv.setX(elem.firstChildElement ("x").text ().toFloat ());
    } else {
      rv.setX(0);
    }
  if (elem.elementsByTagName ("y").count() != 0) {
      rv.setY(elem.firstChildElement ("y").text ().toFloat ());
    } else {
      rv.setY(0);
    }
  if (elem.elementsByTagName ("z").count() != 0) {
      rv.setZ(elem.firstChildElement ("z").text ().toFloat ());
    } else {
      rv.setZ(0);
    }
  return rv;
}
