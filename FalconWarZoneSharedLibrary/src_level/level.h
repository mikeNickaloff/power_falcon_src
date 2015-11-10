/**************************************************************************
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

#ifndef LEVEL_H
#define LEVEL_H

#include <QObject>
#include "falconmodelsharedlib_global.h"
#include "../falconwarzonesharedlibrary_global.h"
#include "../falconwarzonesharedlibrary.h"
//#include "levelobject.h"
#include <QHash>
class MODEL_LIBRARY Component;
class MODEL_LIBRARY Instruction;
class MODEL_LIBRARY InstructionList;
class MODEL_LIBRARY Model;
class MODEL_LIBRARY SubComponentList;
class MODEL_LIBRARY GLHandler;
class LevelObject;
class LEVEL_LIBRARY Level : public QObject
{
  Q_OBJECT
public:
  Level(QObject *parent = 0);
  QHash<int, LevelObject*> levelObjects;
 // QHash<int, Model*> models;
  QString xml();
  QString levelName() { if (_levelName.length() > 0) { return _levelName; } return "No Name"; }
  QString _levelName;
  LevelObject* newLevelObject;
  GLHandler* m_glHandler;
  LevelObject* createLevelObject();
signals:

public slots:
  void draw();
};

#endif // LEVEL_H
