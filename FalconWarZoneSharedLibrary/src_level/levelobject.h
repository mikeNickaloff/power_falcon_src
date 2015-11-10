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

#include <QObject>
#include "falconmodelsharedlib_global.h"
#include "../falconwarzonesharedlibrary_global.h"

#include <src_core/model.h>
class MODEL_LIBRARY Component;
class MODEL_LIBRARY Instruction;
class MODEL_LIBRARY InstructionList;
class MODEL_LIBRARY Model;
class MODEL_LIBRARY SubComponentList;
class MODEL_LIBRARY GLHandler;
class Level;
class LEVEL_LIBRARY LevelObject : public QObject
{
  Q_OBJECT
public:
  explicit LevelObject(QObject *parent = 0, GLHandler* i_glHandler = 0);
  QString xml(int levelObjectID);
  GLHandler* m_glHandler;
  Model* _model;
  Model* model() { if (_model) { return _model; } _model = new Model(this, m_glHandler); return _model;  }
signals:

public slots:
 void draw();
};

#endif // LEVELOBJECT_H
