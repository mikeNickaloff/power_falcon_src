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
#include "mainwindow.h"
#include "src_gfx/glviewer.h"
#include "src_core/component.h"
#include "src_level/level.h"
#include "src_level/levelobject.h"
#include <QVector3D>
#include <QtDebug>
#include <QtOpenGL/QGLFormat>
#include "src_game/gameobject.h"
#include "src_game/laserbeam.h"

MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent)
{
  this->_glHandler = new GLHandler(this);
  this->_model = new Model(this, _glHandler);
  QFile file(qApp->applicationDirPath ().append (QDir::separator ()).append("models").append(QDir::separator ()).append("bird6.pfmdl"));
  if (file.open (QIODevice::ReadOnly)) {
      QDomDocument doc;
      doc.setContent (file.readAll (), false);
      this->_model->loadXML (doc.toString());

    }
  _model->initRootComponent ();
  qDebug() << _model->xml ();

  this->loadLevel (qApp->applicationDirPath ().append(QDir::separator ()).append("Levels").append(QDir::separator ()).append("MothershipBattle.lvl"));
  this->_nextDisplayListIndex = 10;
  QTimer::singleShot (500, this, SLOT(initViewer()));

}

MainWindow::~MainWindow()
{

}



void MainWindow::initViewer () {
  QFile file(qApp->applicationDirPath ().append (QDir::separator ()).append("models").append(QDir::separator ()).append("bird6.pfmdl"));
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
  fmt.setAccum (true);

  this->m_viewer = new GLViewer(this, _glHandler, this);

  m_viewer->setMinimumWidth (( 0.75 * qApp->desktop ()->availableGeometry (this).width ()) - 310);
  m_viewer->setMinimumHeight (600);
  m_viewer->setFormat(fmt);
  m_viewer->show ();
  m_viewer->makeCurrent();
  this->spawnLaser ("laserbeam", this->mapFromGlobal (QCursor::pos()));
  this->setCentralWidget(m_viewer);

}
void MainWindow::draw () {
  emit this->drawGameObjects ();
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
           //qDebug() << levelObject->xml (lvlObjElement.attribute("id").toInt());
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
void MainWindow::spawnLaser (QString laserString, QPoint pt) {
  laserObject = new LaserBeam(this, this->_glHandler, this, laserString, _nextDisplayListIndex, qApp->applicationDirPath ().append (QDir::separator ()).append("models").append(QDir::separator ()).append(QString("%1.pfmdl").arg(laserString)));

  this->gameObjects[_nextDisplayListIndex] = qobject_cast<GameObject*>(laserObject);
  _nextDisplayListIndex++;
  this->connect (laserObject, SIGNAL(displayListChanged(int)), this, SLOT(compileDisplayList(int)));
  this->connect (laserObject, SIGNAL(interpolationComplete(int)), this, SLOT(destroyGameObject(int)));
  laserObject->initPath (pt);

}
void MainWindow::compileDisplayList (int displayListIndex) {

  GameObject* gameobj = qobject_cast<GameObject*> (sender());
  gameobj->disconnect (this, SIGNAL(drawGameObjects()));
  glPushAttrib(GL_ALL_ATTRIB_BITS);
  glNewList(displayListIndex, GL_COMPILE);
  glScalef(6.0f, 4.0f, 6.0f);
  gameobj->draw ();
  glEndList();
  glPopAttrib();

  gameobj->connect (this, SIGNAL(drawGameObjects()), gameobj, SLOT(drawFromDisplayList()));
}
void MainWindow::destroyGameObject (int displayListIndex) {
  if (gameObjects.keys().contains(displayListIndex)) {
      GameObject* obj = this->gameObjects.value (displayListIndex);
      obj->disconnect (this, SIGNAL(drawGameObjects()));
      this->disconnect (obj, SIGNAL(displayListChanged(int)));
      this->disconnect (obj, SIGNAL(interpolationComplete(int)));
      this->gameObjects.remove (displayListIndex);
      delete obj;
    }

}
