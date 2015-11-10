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
//#include "falconmodelsharedlib.h"
#include "src_core/model.h"
#include "src_handlers/glhandler.h"
#include "src_core/instructionlist.h"
#include "src_core/component.h"
//#include "../falconwarzonesharedlibrary.h"
#include "level.h"
#include "levelobject.h"
#include "../GL/qglviewer.h"
LevelObject::LevelObject(QObject *parent, GLHandler *i_glHandler) :
  QObject(parent), m_glHandler(i_glHandler)
{

}
QString LevelObject::xml (int levelObjectID) {
  QString rv;
  rv.append(QString("<LevelObject id=\"%1\">").arg(levelObjectID));
  rv.append(model()->xml ());
  rv.append("</LevelObject>");
  return rv;
}
void LevelObject::draw () {
  model()->draw ();
}
