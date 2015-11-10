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
#include "src_level/levelobject.h"
#include "glviewer.h"
#include <QObject>
#include <QtDebug>
#include <QGLViewer/qglviewer.h>
#include <QGLViewer/manipulatedCameraFrame.h>
#include "../src_math/3DMath.h"




GLViewer::GLViewer(QWidget *parent, GLHandler *iGLHandler, MainWindow *iMainWindow) :
  QGLViewer(parent), _glHandler(iGLHandler), _mainWindow(iMainWindow)
{
  this->setAxisIsDrawn(false);
  this->setGridIsDrawn(true);
  this->setSceneRadius(50000.0);
  this->enableGravity = false;



  this->camera()->setFlySpeed(0.0093f);

  this->camera()->setViewDirection(qglviewer::Vec(1.0, 10.0, 8.0));
resetTimer = false;

kfi_ = new KeyFrameInterpolator(new Frame());

QObject::connect(kfi_, SIGNAL(interpolated()), this, SLOT(update()));
QObject::connect(kfi_, SIGNAL(endReached()), this, SLOT(resetKfi()));
this->resetKfi ();

  if (enableGravity) {
      this->startTimer(200);
    } else {
      this->startTimer (200);
    }
}

void GLViewer::resetKfi () {

  QPoint point = mapFromGlobal(QCursor::pos ());
  camera()->convertClickToLine(point, orig, dir);


  bool found;
  selectedPoint = camera()->pointUnderPixel(point, found);
  selectedPoint -= 0.01f*dir; // Small offset to make point clearly visible.


  m_frame.setPosition (kfi_->frame ()->position ());
//  m_frame.setOrientation (Quaternion(kfi_->frame()->position(), selectedPoint));
  Camera* camera_ = new Camera();
  camera_->setPosition (m_frame.position ());
  camera_->lookAt (selectedPoint);
  m_frame.setOrientation (camera_->orientation ());

     kfi_->deletePath ();

 // kfi_->setFrame (const this->m_frame.referenceFrame ());
  //kfi_->addKeyFrame (Frame(m_frame.position (), m_frame.orientation ()), 0.07f);

  kfi_->addKeyFrame (Frame(m_frame.position (), m_frame.orientation ()));

  kfi_->addKeyFrame (Frame(selectedPoint, m_frame.orientation ()));
  kfi_->setInterpolationSpeed (0.75);
 // kfi_->startInterpolation (40);
}

void GLViewer::timerEvent (QTimerEvent *event) {
  if (resetTimer) {
   killTimer(event->timerId ());
resetTimer = false;

  if (enableGravity) {
      this->startTimer(200);

    } else {
      this->startTimer (200);
    }
  }

  QPoint point = mapFromGlobal(QCursor::pos ());
  camera()->convertClickToLine(point, orig, dir);

  // Find the selectedPoint coordinates, using camera()->pointUnderPixel().
  bool found;
  selectedPoint = camera()->pointUnderPixel(point, found);
  selectedPoint -= 0.01f*dir; // Small offset to make point clearly visible.

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
  }
QString msg;

msg.append("[OrientAxis->Viewdir, OrientAngle] Angle: ");
msg.append(QString("%1").arg(AngleBetweenVectors (fromVec(camera()->orientation().axis ()), fromVec(camera()->viewDirection ()))));
msg.append(" , ");
msg.append(QString("%1").arg(camera()->orientation ().angle ()));
msg.append(" | [Cam] Orient Axis [View Dir]: ");
msg.append(stringFromVector3d(fromVec(camera()->orientation ().axis ())));
msg.append(QString(" [%1]").arg(stringFromVector3d(fromVec(camera()->viewDirection ()))));
//camera()->setOrientation (Quaternion(camera()->orientation ().axis (),  AngleBetweenVectors (fromVec(selectedPoint), fromVec(orig))));

emit this->sbMsg (msg);
  this->update ();

}


void GLViewer::drawWithNames()
{
  setStates();
  this->m_frame.stopSpinning ();
  camera()->frame ()->stopSpinning ();
  glPushMatrix();
      glScalef(2.0, 2.0, 2.0);
      glPushMatrix();
      _mainWindow->drawNames ();
      glPopMatrix();
  glPopMatrix();
}

void GLViewer::postSelection(const QPoint& point)
{
  // Compute orig and dir, used to draw a representation of the intersecting line
  camera()->convertClickToLine(point, orig, dir);

  // Find the selectedPoint coordinates, using camera()->pointUnderPixel().
  bool found;
  selectedPoint = camera()->pointUnderPixel(point, found);
  selectedPoint -= 0.01f*dir; // Small offset to make point clearly visible.
  // Note that "found" is different from (selectedObjectId()>=0) because of the size of the select region.

    if (selectedName() != -1)
      QMessageBox::information(this, "Selection",
                               "Spiral number " + QString::number(selectedName()) + " selected under pixel " +
                               QString::number(point.x()) + "," + QString::number(point.y()));
}

void GLViewer::init()
{
  oldZValue = 0.0;
  gravityForce = 1.6666;
  // restoreStateFromFile();
  setMouseTracking(true);
  glLineWidth(3.0);
  glPointSize(10.1);
  camera()->setZClippingCoefficient (1.0f);
  camera()->setIODistance (20.0f);


  // m_camera_frame = new ManipulatedCameraFrame();
  this->m_camera_constraint = new CameraConstraint(camera());
  // m_camera_constraint->setTranslationConstraintType(AxisPlaneConstraint::PLANE);
  //m_camera_constraint->setTranslationConstraintDirection(Vec(1.0f, 1.0f, 1.0f));
  m_camera_constraint->setRotationConstraintType(AxisPlaneConstraint::PLANE);
  m_camera_constraint->setRotationConstraintDirection(Vec(0.001f ,0.001f, 0.0f));
  camera()->frame ()->setSpinningSensitivity (0.0);
  //camera()->frame ()->setSpinningSensitivity(0);
  camera()->frame ()->setRotationSensitivity(0.25f);
  camera()->frame ()->setTranslationSensitivity(0.25f);
  camera()->frame ()->setConstraint(m_camera_constraint);
  camera()->frame()->setOrientation (0.714989,-0.0573572,-0.00334217,-0.696771);
  camera()->frame()->setPosition (0.181669,6.60265,-1.25621);
  // camera()->setFrame(m_camera_frame);
  this->m_world_constraint = new WorldConstraint();
  //  m_world_constraint->setTranslationConstraintType(AxisPlaneConstraint::AXIS);
  //  m_world_constraint->setTranslationConstraintDirection(Vec(1.0f, 0.0, 0.0));
  m_world_constraint->setRotationConstraintType(AxisPlaneConstraint::AXIS);
  m_world_constraint->setRotationConstraintDirection(Vec(0.0, 0.0, 1.0f));



  m_frame.setTranslationSensitivity(1.0f);
  //m_frame.setOrientation(0.312498, 0.0328202, -0.054013, 0.947813);
  m_frame.setOrientation (0.714989,-0.0573572,-0.00334217,-0.696771);

  m_frame.setRotationSensitivity(0.75f);
  m_frame.setSpinningSensitivity(0.75f);

  m_frame.setConstraint(m_world_constraint);

  //camera()->frame()->setOrientation(-0.308071, -0.774754, 0.510504, 0.21032 );
  // camera()->frame()->setOrientation(0.0268112, -0.900378, 0.430649, 0.0560555);


  // m_camera_frame->setConstraint(m_camera_constraint);
  //m_camera_frame->setPosition(Vec(-1339.98, -2474.59, -2001.8 ));
  // camera()->setPosition(Vec(-1339.98, -1474.59, -2001.8 ));
  // camera()->setViewDirection(Vec(-0.0956168, 0.783527, 0.613957));
  // camera()->setPosition(Vec(0, 0, 0));

  //    QWheelEvent* wheelevent = new QWheelEvent(QPoint(0, 0), 5, Qt::NoButton, Qt::NoModifier, Qt::Vertical);
  //    QGLViewer::wheelEvent(wheelevent);
  //camera()->frame()->setSpinningSensitivity(0.0);
  //  camera()->frame()->setOrientation(0.312498, 0.0328202, -0.054013, 0.947813);
  setManipulatedFrame(&m_frame);
  // this->camera()->frame()->setConstraint(m_world_constraint);
  //  m_frame.setConstraint(m_world_constraint);
  setMouseBinding(Qt::NoModifier, Qt::LeftButton, CAMERA, ROTATE, false);
  //setMouseBinding(Qt::NoModifier, Qt::LeftButton, CAMERA, ROTATE, false);
  setMouseBinding(Qt::NoModifier, Qt::RightButton, CAMERA, TRANSLATE, false);

  /* setMouseBinding(Qt::RightButton, CAMERA, NO_MOUSE_ACTION);
  setWheelBinding(Qt::ControlModifier, CAMERA, NO_MOUSE_ACTION);
  setWheelBinding(Qt::ShiftModifier, CAMERA, NO_MOUSE_ACTION);
  setWheelBinding(Qt::AltModifier, CAMERA, NO_MOUSE_ACTION);
  setMouseBinding(Qt::LeftButton, FRAME, NO_MOUSE_ACTION);
  setMouseBinding(Qt::MidButton | Qt::LeftButton, CAMERA, NO_MOUSE_ACTION);
  setMouseBinding(Qt::MidButton, FRAME, NO_MOUSE_ACTION); */
  //  setMouseBinding(Qt::MidButton, CAMERA, true, NO_MOUSE_ACTION);
  //this->camera()->setViewDirection(qglviewer::Vec(1.0, 10.0, 8.0));

  this->showEntireScene();
  // this->update();
}

void GLViewer::draw()
{
  // Draw ten spirals
  //  const int nb = 5;
  //  for (int i=0; i<nb; ++i)
  //    {
  //      glPushMatrix();
  //      glTranslatef(cos(2.0*i*M_PI/nb), sin(2.0*i*M_PI/nb), 0.0);
  //     // drawSpiral(i == selectedName());
  //     _mainWindow->draw ();
  //      glPopMatrix();
  //    }

  const int nb = 1;
  setStates();
//  this->setLights();
  //glClearColor(0.25f, 0.25f, 0.5f, 1.0f);

  this->m_frame.stopSpinning ();
  camera()->frame ()->stopSpinning ();

  //glPushMatrix();
  //glMultMatrixd(manipulatedFrame()->matrix ());
//  glMultMatrixd(kfi_->frame ()->matrix ());
 // this->m_frame.setOrientation (Quaternion(m_frame.position(), kfi_->frame()->position()));
  //this->m_frame.setPosition (kfi_->frame ()->position ());

//  for (int i=0; i<nb; ++i)
//    {
    //  glScalef(2.0, 2.0, 2.0);

      glPushMatrix();
      //glTranslatef(cos(2.0*i*M_PI/nb) * 5.0, sin(2.0*i*M_PI/nb) * 3.0 , 8.0);

      // glPushMatrix();
      //  glRotatef(90.0 * (qreal) i, 0.0, 1.0, 0.0);
      //glScalef(2.0, 2.0, 2.0);
      // glTranslatef(4.0, 2.0, 0.0);

      _mainWindow->draw ();

      // glPopMatrix();

      glPopMatrix();

  //  }
  //glPopMatrix();

  // Draw the intersection line
  //glBegin(GL_LINES);
  //glVertex3fv(orig);
  //glVertex3fv(orig + 100.0*dir);
  //glEnd();

  // Draw (approximated) intersection point on selected object
  //  if (selectedName() >= 0)
  //    {
  //      glColor3f(0.9f, 0.2f, 0.1f);
  //      glBegin(GL_POINTS);
  //      glVertex3fv(selectedPoint);
  //      glEnd();
  //    }
//   defaultStates();
}
void GLViewer::spiral(const bool specialColor)
{
  const float nbSteps = 20.0;
  glBegin(GL_QUAD_STRIP);
  for (float i=0; i<nbSteps; ++i)
    {
      float ratio = i/nbSteps;
      float angle = 21.0*ratio;
      float c = cos(angle);
      float s = sin(angle);
      float r1 = 0.5 - 0.3*ratio;
      float r2 = 0.3 - 0.3*ratio;
      float alt = ratio - 0.5;
      const float nor = .5;
      const float up = sqrt(1.0-nor*nor);
      if (specialColor)
        glColor3f(1.0-ratio, 0.8f , ratio/2.0);
      else
        glColor3f(1.0-ratio, 0.2f, ratio);
      glNormal3f(nor*c, nor*s, up);
      glVertex3f(r2*c, r2*s, alt+0.05f);
      glVertex3f(r1*c, r1*s, alt);
    }
  glEnd();
}
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
