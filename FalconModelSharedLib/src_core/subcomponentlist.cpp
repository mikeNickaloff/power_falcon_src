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

#include "subcomponentlist.h"
#include "component.h"
#include "model.h"
#include "instruction.h"
#include "instructionlist.h"
#include <QtOpenGL/qtopenglglobal.h>
#include "glut.h"
#include <gl/GL.h>
//#include <../src_xml/xmlbuilder.h>
#include <QMetaProperty>
#include <QMetaObject>
SubComponentList::SubComponentList(QObject *parent, Component *iComponent) :
  QObject(parent), _parentComponent(iComponent)
{
  isExpanded = false;
}

Component* SubComponentList::parentComponent () {
  if (!_parentComponent) {
      qDebug() << "FATAL: A call to the method  [ parentComponent() ]  was made to an  [ SubComponentList ] that did not have a Parent Component assigned in the constructor or via setParentComponent() ";
      qApp->exit (-1);
    }
  return _parentComponent;
}

QString SubComponentList::xml () {
  QString rv = QString("<SubComponentList parentComponent=\"%1\" expanded=\"%2\">").arg(parentComponent()->componentId ()).arg(isExpanded);
  //XMLBuilder* builder = new XMLBuilder(this, "SubComponentList");
  const QMetaObject *metaobject = this->metaObject();
  int count = metaobject->propertyCount();
  for (int i=0; i<count; ++i) {
      QMetaProperty metaproperty = metaobject->property(i);
      const char *name = metaproperty.name();
      QVariant value = this->property(name);
      //qDebug() << name << ":" << value;
  }
  foreach (Component* value, this->_components) {

      //builder->insertElement ("Component", QString("%1").arg(this->_components.key (value)), value->xml ());
      rv.append(QString("%1").arg(value->xml ()));

    }
  rv.append("</SubComponentList>");
  return rv;
}


void SubComponentList::setParentComponent (Component *iComponent) {
  _parentComponent = iComponent;
}
void SubComponentList::addComponent(Component* iComponent) {
  QList<int> keys; keys << _components.keys ();
  int newKey = 1;
  if (_components.count () > 0) {

     // qSort(keys.begin (), keys.end ());
      int lastKey = keys.last ();
      newKey = lastKey + 1;
    } else {
      newKey = 1;
    }
  while (keys.contains(newKey)) {
      newKey++;
    }
  _components[newKey] = iComponent;
}

void SubComponentList::removeComponent(Component* iComponent) {
  QMap<int, Component*>::iterator o = _components.begin ();
  while (o != _components.end ()) {
      Component* value = o.value ();

      if (value == iComponent) {
          o = _components.erase(o);
        } else {
          o++;
        }

    }
}
void SubComponentList::draw () {

 foreach (Component* value, _components) {
      glPushMatrix();
    value->draw ();
      glPopMatrix();
   }

}
