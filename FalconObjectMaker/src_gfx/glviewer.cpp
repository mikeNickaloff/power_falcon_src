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
#include <windows.h>
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
#include <qglviewer.h>
#include <manipulatedCameraFrame.h>
//#include <aux_ulib.h>
/* derived from QGLViewer library*/


GLViewer::GLViewer(QWidget *parent, GLHandler *iGLHandler, MainWindow *iMainWindow) :
  QGLViewer(parent), _glHandler(iGLHandler), _mainWindow(iMainWindow)
{
  this->setAxisIsDrawn(false);
  this->setGridIsDrawn(true);
  this->setSceneRadius(1000.0);
  this->enableGravity = true;

  // qDebug() << "Frame size is" << this->frameSize();

  this->camera()->setFlySpeed(0.0093f);

  //this->camera()->setType(qglviewer::Camera::PERSPECTIVE);
  this->camera()->setViewDirection(qglviewer::Vec(1.0, 10.0, 8.0));
  resetTimer = true;
  if (enableGravity) {
      this->startTimer(100);
    } else {
      this->startTimer (100);
    }
}


void GLViewer::timerEvent (QTimerEvent *event) {
  if (resetTimer) {
      QPoint pt = mapFromGlobal(QCursor::pos ());
      killTimer(event->timerId ());
      resetTimer = false;

      if (enableGravity) {
          this->startTimer(100);
          QGLViewer::select (pt);

        } else {
          this->startTimer (100);
        }
    }

  QPoint pt = mapFromGlobal(QCursor::pos ());

  if (!enableGravity)
    GLViewer::select (pt);
  if (this->sceneRadius () > 5000) {
      this->setSceneRadius(10.0 + camera()->distanceToSceneCenter () + fabs(camera()->frame ()->coordinatesOf (m_frame.position ()).z));
    } else {
      if (sceneRadius() != 5000) {
          setSceneRadius(5000);
        }
    }


  if (enableGravity) {
      if ((qAbs(m_frame.translation ().z) > velocity) && (m_frame.translation ().z < 0)) {
          double liftAmount = fallZOffset(m_frame.translation ().z);
          this->oldZValue = m_frame.translation ().z;
          if (!m_frame.isManipulated ()) {
              if (liftAmount > 0) {
                  m_frame.translate (0.0f, 0.0f, (float) gravityForce);
                  velocity = 0 - liftAmount + gravityForce;
                }
              if (liftAmount < 0) {
                  velocity += gravityForce;
                  m_frame.translate (0.0f, 0.0f, (float) velocity);
                }
            }
        } else {

          m_frame.setTranslation ( m_frame.translation ().x,  m_frame.translation ().y, 0.0f);
          this->oldZValue = m_frame.translation ().z;
          velocity = (-1 * (velocity - qAbs(m_frame.translation ().z)));
          if (qAbs(velocity) > gravityForce) {
              m_frame.translate (0.0f, 0.0f, (float) velocity);
            } else {
              m_frame.setTranslation ( m_frame.translation ().x,  m_frame.translation ().y, 0.0f);
              velocity = 0;
              this->oldZValue = m_frame.translation ().z;
            }

        }
      setSceneCenter(m_frame.position ());
      camera()->lookAt (m_frame.position ());
    }

  this->update();
  this->rebuildDisplayLists = true;

}


void GLViewer::drawWithNames()
{

  glPushMatrix();
  glScalef(2.0, 2.0, 2.0);

  glPushMatrix();
  glMultMatrixd(manipulatedFrame()->matrix ());

  if (_mainWindow) {
      glPushName(1);
      _mainWindow->draw ();
      glPopName();
      glPopMatrix();
      glPopMatrix();
    }
}

void GLViewer::postSelection(const QPoint& point)
{
  camera()->convertClickToLine(point, orig, dir);

  bool found;
  selectedPoint = camera()->pointUnderPixel(point, found);
  selectedPoint -= 0.1f*dir; // Small offset to make point clearly visible.
  if ((selectedName() != -1) || (this->enableGravity)) {

      setMouseBinding(Qt::NoModifier, Qt::RightButton, FRAME, TRANSLATE, false);
      if (enableGravity) {
          setMouseBinding(Qt::NoModifier, Qt::LeftButton, FRAME, TRANSLATE, false);
        } else {
          setMouseBinding(Qt::NoModifier, Qt::LeftButton, FRAME, ROTATE, false);

        }


      qDebug() << "Model is Selected";

    } else {
      setMouseBinding(Qt::NoModifier, Qt::RightButton, CAMERA, TRANSLATE, false);
      setMouseBinding(Qt::NoModifier, Qt::LeftButton, CAMERA, ROTATE, false);





    }

}

void GLViewer::init()
{
  oldZValue = 0.0;
  gravityForce = 2.6666;

  setMouseTracking(true);
  glLineWidth(3.0);
  glPointSize(3.1);

  //setSceneRadius(200.0f);


  this->m_camera_constraint = new CameraConstraint(camera());

  m_camera_constraint->setRotationConstraintType(AxisPlaneConstraint::PLANE);
  m_camera_constraint->setRotationConstraintDirection(Vec(0.001f ,0.001f, 0.0f));
  camera()->frame ()->setSpinningSensitivity (0.0);

  camera()->frame ()->setRotationSensitivity(0.25f);
  camera()->frame ()->setTranslationSensitivity(0.25f);
  camera()->frame ()->setConstraint(m_camera_constraint);
  camera()->frame()->setOrientation (0.714989,-0.0573572,-0.00334217,-0.696771);
  camera()->frame()->setPosition (0.181669,6.60265,-1.25621);

  this->m_world_constraint = new WorldConstraint();

  m_world_constraint->setRotationConstraintType(AxisPlaneConstraint::AXIS);
  m_world_constraint->setRotationConstraintDirection(Vec(0.0, 0.0, 1.0f));



  m_frame.setTranslationSensitivity(1.0f);

  m_frame.setOrientation (0.714989,-0.0573572,-0.00334217,-0.696771);

  m_frame.setRotationSensitivity(0.75f);
  m_frame.setSpinningSensitivity(0.75f);

  m_frame.setConstraint(m_world_constraint);



  setManipulatedFrame(&m_frame);

 // this->showEntireScene ();
  this->rebuildDisplayLists = true;


}

void GLViewer::draw()
{
  setStates();

  this->m_frame.stopSpinning ();
  camera()->frame ()->stopSpinning ();

  glPushMatrix();
  setLights();

  glMultMatrixd(manipulatedFrame()->matrix ());


      glScalef(2.0, 2.0, 2.0);

      glPushMatrix();
      //glBegin(GL_LINE_LOOP);
      if (_mainWindow) {
          if (this->rebuildDisplayLists) {
              glDeleteLists(1, 1);
              glNewList(1, GL_COMPILE);
              _mainWindow->draw ();
              glEndList();
              glCallList(1);
              this->rebuildDisplayLists = false;

            } else {
              glCallList(1);

            }
        }
     // glEnd();


    glPopMatrix();


  glPopMatrix();
 // this->defaultStates ();


//  glBegin(GL_LINES);
//  glVertex3fv(orig);
//  glVertex3fv(orig + 100.0*dir);
//  glEnd();
//  if (selectedName() >= 0)
//    {
//      glColor3f(0.9f, 0.2f, 0.1f);
//      glBegin(GL_POINTS);
//      glVertex3fv(selectedPoint);
//      glEnd();
//    }
}

  //  defaultStates();


void GLViewer::setStates()
{
  glClearColor(0.25f, 0.25f, 0.5f, 1.0f);

  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);
  glEnable(GL_LIGHTING);
  glEnable(GL_COLOR_MATERIAL);
  glEnable(GL_TEXTURE_2D);
  glEnable(GL_NORMALIZE);

  glMatrixMode(GL_PROJECTION);
  glPushMatrix();
  //glLoadIdentity();

  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();
  // glLoadIdentity();

  setLights();

  float materialSpecular[] = {0.5f, 0.5f, 0.5f, 1.0f};
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, materialSpecular);
  glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 32.0f);


}

void GLViewer::setLights()
{
  glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
  float lightColour[] = {1.0f, 0.8f, 1.0f, 1.0f};
  Vec vd = camera()->viewDirection ();
  float lightDir[] = {vd.x, vd.y, vd.z, 5.0f};
  glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColour);
  glLightfv(GL_LIGHT0, GL_SPECULAR, lightColour);
  bool found = true;
  Vec mfp = camera()->worldCoordinatesOf (this->camera ()->pointUnderPixel (mapFromGlobal(QCursor::pos ()), found));
  float lightPos[] = {mfp.x, mfp.y, mfp.z, 2.0f};
  glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
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
