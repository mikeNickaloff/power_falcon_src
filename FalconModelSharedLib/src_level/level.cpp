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
#include "../src_core/model.h"
#include "../src_handlers/glhandler.h"
#include "../src_core/instructionlist.h"
#include "../src_core/component.h"
#include "level.h"
#include "levelobject.h"
#include <QObject>
#include <QHash>
#include <QHashIterator>
Level::Level(QObject *parent) :
  QObject(parent)
{
  _levelName = "";
  this->m_glHandler = new GLHandler(this);
}
QString Level::xml () {
  QString rv;
  rv.append(QString("<Level name=\"%1\">").arg(levelName()));
  QHashIterator<int, LevelObject*> o (this->levelObjects);
  o.toFront ();
  while (o.hasNext ()) {
      o.next ();
      LevelObject* obj = o.value ();
      int id = o.key ();
      rv.append(obj->xml (id));
    }
  rv.append("</Level>");
  return rv;

}
LevelObject* Level::createLevelObject () {
  newLevelObject = new LevelObject(this, this->m_glHandler);
  int i = 0;
  while ( levelObjects.keys ().contains(i)) {
      i++;

    }
  levelObjects[i] = newLevelObject;
//    assignmentID = i;
  return this->newLevelObject;
}
void Level::draw () {
foreach (LevelObject* obj, this->levelObjects.values ()) {
    glPushMatrix();
    obj->draw();
    glPopMatrix();
  }
}
