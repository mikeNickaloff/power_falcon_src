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


#include <QMouseEvent>
#include <math.h>
#include "../mainwindow.h"
#include "src_handlers/glhandler.h"
#include "src_core/component.h"
#include "src_core/subcomponentlist.h"
#include "src_core/model.h"
#include "src_core/instruction.h"
#include "src_core/instructionlist.h"
#include "glviewer.h"
#include <QObject>
#include <QtDebug>
#include <manipulatedCameraFrame.h>




GLViewer::GLViewer(QWidget *parent, GLHandler *iGLHandler, MainWindow *iMainWindow) :
  QGLViewer(parent), _glHandler(iGLHandler), _mainWindow(iMainWindow)
{
  kfi_ = new KeyFrameInterpolator(new Frame());

  QObject::connect(kfi_, SIGNAL(interpolated()), this, SLOT(update()));
  QObject::connect(kfi_, SIGNAL(endReached()), this, SLOT(flipColor()));
  this->setAxisIsDrawn(false);
  this->setGridIsDrawn(true);
  this->setSceneRadius(50000.0);
  this->enableGravity = false;
  this->leftButtonPressed = false;

  this->camera()->setFlySpeed(20.1093f);

  this->camera()->setType(qglviewer::Camera::PERSPECTIVE);
  this->camera()->setViewDirection(qglviewer::Vec(1.0, 10.0, 8.0));
  resetTimer = false;
  if (enableGravity) {
      this->startTimer(150);
    } else {
      this->startTimer (150);
    }
  this->flipColor ();

}


void GLViewer::timerEvent (QTimerEvent *event) {
  if (this->leftButtonPressed) {
      this->_mainWindow->spawnLaser ("laserbeam", this->mapFromGlobal(QCursor::pos()));
    }
  if (resetTimer) {
      killTimer(event->timerId ());
      resetTimer = false;

      if (enableGravity) {
          this->startTimer(150);

        } else {
          this->startTimer (150);
        }
    }


  QPoint pt = mapFromGlobal(QCursor::pos ());

  Camera* cam = new Camera();
  cam->setOrientation (camera()->orientation ());
  cam->setPosition (camera()->position());
  cam->setViewDirection (camera()->viewDirection ());
  cam->lookAt(selectedPoint);
  cam->setPosition (camera()->position());
  if (this->geometry ().contains(pt, true)) {

  Vec flyDisp = Vec(0.0, 0.0, 0.0);
  flyDisp.z = -camera()->flySpeed () * 2.0;
  cam->frame ()->translate ( cam->frame()->localInverseTransformOf(flyDisp));
  camera()->interpolateTo (Frame(cam->frame ()->position (), cam->orientation ()), 1.0f);

    }

  camera()->convertClickToLine(pt, orig, dir);
  bool found;
  selectedPoint = camera()->pointUnderPixel(pt, found);
  selectedPoint -= 0.01f*dir;


  int u = 1;



//  if (resetKfi) {
//     this->laserFramesDirections[u] = selectedPoint;
//      this->laserFramesOrigins[u] = orig;

//      cam->setPosition(orig);
//      cam->setOrientation (camera()->orientation ());
//      cam->setViewDirection (camera()->viewDirection ());
//        cam->lookAt(selectedPoint);
//           cam->setPosition(orig);
//      Vec laserDisp = Vec(0.0, 0.0, 0.0);
//      laserDisp.z = -1000.12;
//         kfi_->deletePath ();
//         Vec midPt = selectedPoint;


//         midPt = orig;

//             midPt.x = (orig.x + selectedPoint.x) / 2.0;
//             midPt.y =  (orig.y + selectedPoint.y) / 2.0;
//             midPt.z =  (orig.z + selectedPoint.z) / 2.0;

//             cam->setPosition (midPt);
//             kfi_->addKeyFrame (Frame(cam->frame()->position(), cam->orientation ()), 0.55f);

//      //cam->frame ()->translate ( cam->frame()->localInverseTransformOf(laserDisp));



//      kfi_->addKeyFrame (Frame(cam->frame()->position(), cam->orientation ()), 0.85f);
//      cam->frame ()->translate ( cam->frame()->localInverseTransformOf(laserDisp * 2));
//      kfi_->addKeyFrame (Frame(cam->frame()->position(), cam->orientation ()), 1.55f);


//      kfi_->setInterpolationSpeed (3.0);
//      kfi_->startInterpolation (35);
//      resetKfi = false;
//    }
update();



}
float GLViewer::Distance(Vec vPoint1, Vec vPoint2)
{

	double distance = sqrt( (vPoint2.x - vPoint1.x) * (vPoint2.x - vPoint1.x) +
						    (vPoint2.y - vPoint1.y) * (vPoint2.y - vPoint1.y) +
						    (vPoint2.z - vPoint1.z) * (vPoint2.z - vPoint1.z) );


	return (float)distance;
}
Vec GLViewer::stepAmount(Vec vPoint1, Vec vPoint2, int numSteps) {
  Vec rv;
  rv.x = (vPoint2.x - vPoint1.x);
  rv.y = (vPoint2.y - vPoint1.y);
  rv.z = (vPoint2.z - vPoint1.z);
  return rv;
}

void GLViewer::drawWithNames()
{


      glPushMatrix();

      glPopMatrix();


}

void GLViewer::postSelection(const QPoint& point)
{

  camera()->convertClickToLine(point, orig, dir);
  bool found;
  selectedPoint = camera()->pointUnderPixel(point, found);
  selectedPoint -= 0.01f*dir; // Small offset to make point clearly visible.
}

void GLViewer::init()
{
  oldZValue = 0.0;
  gravityForce = 1.6666;

  setMouseTracking(true);
  glLineWidth(2.0);
  glPointSize(10.1);


  camera()->setFieldOfView (1.25);
  camera()->setFlySpeed (camera()->flySpeed() * 10.0);

  this->m_camera_constraint = new CameraConstraint(camera());

  m_camera_constraint->setRotationConstraintType(AxisPlaneConstraint::PLANE);
  m_camera_constraint->setRotationConstraintDirection(Vec(0.001f ,0.001f, 0.0f));
  camera()->frame ()->setSpinningSensitivity (0.0);

  camera()->frame ()->setRotationSensitivity(0.25f);
  camera()->frame ()->setTranslationSensitivity(0.25f);
  camera()->frame ()->setConstraint(m_camera_constraint);

  this->m_world_constraint = new WorldConstraint();

  m_world_constraint->setRotationConstraintType(AxisPlaneConstraint::AXIS);
  m_world_constraint->setRotationConstraintDirection(Vec(0.0, 0.0, 1.0f));



  m_frame.setTranslationSensitivity(1.0f);

  m_frame.setRotationSensitivity(0.75f);
  m_frame.setSpinningSensitivity(0.75f);


  setManipulatedFrame(&m_frame);

//  glPushAttrib(GL_ALL_ATTRIB_BITS);
//  glNewList(1, GL_COMPILE);
//  Model* laserModel = new Model(this, _glHandler);
//  QFile file(qApp->applicationDirPath ().append (QDir::separator ()).append("models").append(QDir::separator ()).append("laserbeam.pfmdl"));
//  if (file.open (QIODevice::ReadOnly)) {
//      QDomDocument doc;
//      doc.setContent (file.readAll (), false);
//      laserModel->loadXML (doc.toString());

//    }
//  file.close ();

//  foreach (Component* component, laserModel->findComponentsExcept (0)) {
//      component->setSelected (true);


//    }
//  laserModel->getComponentById (0)->setSelected (true);
//  glScalef(6.0f, 4.0f, 6.0f);
//  laserModel->draw ();
//  glEndList();
//  glPopAttrib();

  glPushAttrib(GL_ALL_ATTRIB_BITS);
    glNewList(2, GL_COMPILE);

  glPushMatrix();
      glLineWidth (0.75f);

  drawGrid(sceneRadius(), 60);
  glPopMatrix();
    glEndList();
  glPopAttrib();
camera()->setPosition(this->sceneCenter ());
glNewList(3, GL_COMPILE);
 glPushAttrib(GL_ALL_ATTRIB_BITS);
for (int i=0; i<256; i++) {
    int rx1 = (qrand()%(int)sceneRadius())+1;
    int ry1 = (qrand()%(int)sceneRadius())+1;
    int rz1 = (qrand()%(int)sceneRadius())+1;
    int rx2 = (qrand()%(int)sceneRadius())+1;
    int ry2 = (qrand()%(int)sceneRadius())+1;
    int rz2 = (qrand()%(int)sceneRadius())+1;
    int rx = rx1 - rx2 * 1.5;
    int ry = ry1 - ry2 * 1.5;
    int rz = rz1 - rz2 * 1.5;

    glPushMatrix();
    glTranslatef(rx, ry, rz);
    glPushMatrix();
    glScalef(100.0, 100.0, 100.0);
    glutSolidTetrahedron ();
    glPopMatrix();
    glPopMatrix();


  }
   glPopAttrib();
glEndList();
}

void GLViewer::draw()
{
 setStates();
  this->m_frame.stopSpinning ();
  camera()->frame ()->stopSpinning ();
  glPushMatrix();
 glMultMatrixd(manipulatedFrame()->matrix ());
      glPushMatrix();
       _mainWindow->draw ();
      glPopMatrix();
  glPopMatrix();
  glPushMatrix();
  glCallList(3);
  glPopMatrix();
//  glPushAttrib(GL_ALL_ATTRIB_BITS);
//  glPushMatrix();
//  glMultMatrixd(kfi_->frame()->matrix());
//  glCallList(1);
//  glPopMatrix();
//  glPopAttrib();

}

void GLViewer::setStates()
{
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);
  glEnable(GL_LIGHTING);
  glEnable(GL_COLOR_MATERIAL);
  glEnable(GL_TEXTURE_2D);
  glEnable(GL_NORMALIZE);

  glMatrixMode(GL_PROJECTION);
  glPushMatrix();


  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();


  setLights();

  float materialSpecular[] = {0.5f, 0.5f, 0.5f, 1.0f};
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, materialSpecular);
  glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 32.0f);


}

void GLViewer::setLights()
{
  glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
  float lightColour[] = {1.0f, 0.8f, 1.0f, 1.0f};
  float lightDir[] = {0.0f, 0.0f, 1.0f, 0.0f};
  glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColour);
  glLightfv(GL_LIGHT0, GL_SPECULAR, lightColour);
  glLightfv(GL_LIGHT0, GL_POSITION, lightDir);
  glLightModelf(GL_LIGHT_MODEL_LOCAL_VIEWER, 1.0f);
  glEnable(GL_LIGHT0);
}

void GLViewer::defaultStates()
{
  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

  glDisable(GL_DEPTH_TEST);
  glDisable(GL_CULL_FACE);
  glDisable(GL_LIGHTING);
  glDisable(GL_COLOR_MATERIAL);
  glDisable(GL_TEXTURE_2D);
  glDisable(GL_LIGHT0);
  glDisable(GL_NORMALIZE);

  glMatrixMode(GL_MODELVIEW);
  glPopMatrix();

  glMatrixMode(GL_PROJECTION);
  glPopMatrix();

  glLightModelf(GL_LIGHT_MODEL_LOCAL_VIEWER, 0.0f);
  float defaultMaterialSpecular[] = {0.0f, 0.0f, 0.0f, 1.0f};
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, defaultMaterialSpecular);
  glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 0.0f);
}
void GLViewer::mousePressEvent (QMouseEvent *event) {
  if (event->button () == Qt::LeftButton) {
      this->leftButtonPressed = true;
    }
}
void GLViewer::mouseReleaseEvent (QMouseEvent *event) {
  if (event->button () == Qt::LeftButton) {
      this->leftButtonPressed = false;
    }
}
