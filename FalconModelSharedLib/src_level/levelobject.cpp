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
LevelObject::LevelObject(QObject *parent, GLHandler *i_glHandler) :
  QObject(parent), m_glHandler(i_glHandler)
{
  _scale = QVector3D(1.0, 1.0, 1.0);
  _translation = QVector3D(0.0, 0.0, 0.0);
  _rotation = QVector3D(0.0, 0.0, 0.0);
_model = 0;
}
QString LevelObject::xml (int levelObjectID) {
  QString rv;
  rv.append(QString("<LevelObject id=\"%1\">").arg(levelObjectID));
  rv.append(this->vector3dxml (_translation,"translation"));
  rv.append(this->vector3dxml (_rotation,"rotation"));
  rv.append(this->vector3dxml (_scale,"scale"));
  rv.append(model()->xml ());
  rv.append("</LevelObject>");
  return rv;
}
void LevelObject::draw () {
  glPushAttrib(GL_ALL_ATTRIB_BITS);
  glPushMatrix();
  glTranslatef(_translation.x(), _translation.y(), _translation.z());
  glPushMatrix();
  glRotatef(_rotation.x (), 1.0, 0.0, 0.0);
  glRotatef(_rotation.y (), 0.0, 1.0, 0.0);
  glRotatef(_rotation.z (), 0.0, 0.0, 1.0);
  glScalef(_scale.x(), _scale.y(), _scale.z());

 _model->rootComponent ()->draw ();

 glPopMatrix();
 glPopMatrix();
 glPopAttrib();
}
Model* LevelObject::model () {
  if (m_glHandler == 0) { m_glHandler = new GLHandler(this); }
  if (_model == 0) {
      _model = new Model(this, m_glHandler);
    }
  return _model;


}
QString LevelObject::vector3dxml (QVector3D i_vector, QString tagName) {
  QString rv;
  rv.append(QString("<%1>").arg(tagName));
  rv.append(QString("<x>%1</x>").arg(i_vector.x()) );
  rv.append(QString("<y>%1</y>").arg(i_vector.y()) );
  rv.append(QString("<z>%1</z>").arg(i_vector.z()) );
  rv.append(QString("</%1>").arg(tagName));
  return rv;
}
