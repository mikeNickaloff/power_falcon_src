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

#ifndef GLVIEWER_H
#define GLVIEWER_H

#include <QMessageBox>
#include <QMainWindow>
#include <QWidget>
#include <QObject>
#include <QCoreApplication>
//#include <qglviewer.h>
#include <manipulatedCameraFrame.h>
#include "../falconmodelsharedlib_global.h"

class MODEL_LIBRARY MainWindow;
class MODEL_LIBRARY GLHandler;
class MODEL_LIBRARY Model;
class MODEL_LIBRARY Component;

using namespace qglviewer;

class GLViewer : public QGLViewer
{
   Q_OBJECT
public:
     GLViewer(QWidget *parent = 0, GLHandler* iGLHandler = 0, MainWindow* iMainWindow = 0);
  GLHandler* _glHandler;
  MainWindow* _mainWindow;
  qglviewer::ManipulatedFrame m_frame;
  AxisPlaneConstraint* m_camera_constraint;
 ManipulatedCameraFrame* m_camera_frame;
  AxisPlaneConstraint* m_world_constraint;
  double fallZOffset(double newZValue) { return double(oldZValue - newZValue); }
  double oldZValue;
  double gravityForce;
  double velocity;
  bool enableGravity;
  bool resetTimer;
  bool rebuildDisplayLists;

public slots:

  void timerEvent(QTimerEvent *event);
  void setStates();
  void setLights();
  void defaultStates();

protected :
  virtual void draw();
  virtual void drawWithNames();
  virtual void postSelection(const QPoint& point);
  virtual void init();
 // virtual QString helpString() const;

private :
  qglviewer::Vec orig, dir, selectedPoint;

};




#endif // GLVIEWER_H
