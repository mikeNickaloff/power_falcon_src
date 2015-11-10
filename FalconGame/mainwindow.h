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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "falconmodelsharedlib_global.h"
#include <QMainWindow>
#include <QMap>
#include <QMetaObject>
#include <QtDebug>
#include <QDesktopWidget>
#include <QDomElement>
#include <QVector3D>
#include <QtOpenGL/QGLFormat>
class MODEL_LIBRARY Component;
class MODEL_LIBRARY Instruction;
class MODEL_LIBRARY InstructionList;
class MODEL_LIBRARY Model;
class MODEL_LIBRARY SubComponentList;
class MODEL_LIBRARY GLHandler;
class MODEL_LIBRARY Level;
class MODEL_LIBRARY LevelObject;
class GLViewer;
class GameObject;
class LaserBeam;
class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  MainWindow(QWidget *parent = 0);
  ~MainWindow();
  GLHandler* _glHandler;
  Model* _model;
    GLViewer* m_viewer;
      Level* _level;
        QHash<int, LevelObject*> levelObjects;
        QHash<int, GameObject*> gameObjects;
        LaserBeam* laserObject;
        int _nextDisplayListIndex;
      //  QHash<int, GLdouble*> gameObjectMatrices;
signals:
        void drawGameObjects();

public slots:
    void initViewer();
    void draw();
    void loadLevel(QString fn);
    QVector3D elementToVector3D(QDomElement &elem);
    void spawnLaser(QString laserString, QPoint pt);
     void compileDisplayList(int displayListIndex);
     void destroyGameObject(int displayListIndex);
};

#endif // MAINWINDOW_H
