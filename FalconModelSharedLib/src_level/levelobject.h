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

#ifndef LEVELOBJECT_H
#define LEVELOBJECT_H

#include "../falconmodelsharedlib_global.h"

#include <QObject>
#include <QVector3D>
class Component;
class Instruction;
class InstructionList;
class Model;
class SubComponentList;
class GLHandler;
class Level;
class MODEL_LIBRARY LevelObject : public QObject
{
  Q_OBJECT
public:
   LevelObject(QObject *parent = 0, GLHandler* i_glHandler = 0);
  QString xml(int levelObjectID);
  GLHandler* m_glHandler;
  Model* _model;
  Model* model();
  QVector3D _translation;
  QVector3D _rotation;
  QVector3D _scale;
  QString vector3dxml(QVector3D i_vector, QString tagName);
signals:

public slots:
 void draw();
};

#endif // LEVELOBJECT_H
