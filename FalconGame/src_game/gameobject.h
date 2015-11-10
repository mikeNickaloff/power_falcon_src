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

#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <QObject>
#include "../falconmodelsharedlib_global.h"
#include <keyFrameInterpolator.h>
#include <camera.h>
class GLViewer;
class MainWindow;
class MODEL_LIBRARY GLHandler;
class MODEL_LIBRARY Model;
class MODEL_LIBRARY Component;
class GameObject : public QObject
{
  Q_OBJECT
  Q_PROPERTY(int displayListIndex READ displayListIndex WRITE setDisplayListIndex )
public:
  explicit GameObject(QObject *parent = 0, MainWindow* i_main = 0, GLHandler* i_handler = 0, int i_displayListIndex = 0, QString modelData = "<model><Component id=\"0\" expanded=\"0\"><InstructionList parentComponent=\"0\" expanded=\"0\"/><SubComponentList parentComponent=\"0\" expanded=\"0\"/></Component></model>");
  Model* model() { return _model; }
  int displayListIndex() { return _displayListIndex; }
  qglviewer::KeyFrameInterpolator* kfi_;
   qglviewer::Vec orig, dir, selectedPoint;
   MainWindow* m_main;
signals:
  void displayListChanged(int myIndex);
  void displayListIndexChanged(int oldIndex, int myIndex);
  void interpolationComplete(int myIndex);

public slots:
  void setDisplayListIndex(int newIndex) { int oldIndex = displayListIndex(); _displayListIndex = newIndex; emit displayListIndexChanged(oldIndex, newIndex); }
  void draw();
  void drawFromDisplayList();
  void endInterpolation();
private:
  Model* _model;
  GLHandler* _glHandler;
  int _displayListIndex;


};

#endif // GAMEOBJECT_H
