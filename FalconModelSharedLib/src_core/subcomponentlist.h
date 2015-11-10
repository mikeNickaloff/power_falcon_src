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

#ifndef SUBCOMPONENTLIST_H
#define SUBCOMPONENTLIST_H

#include <QObject>
#include <QCoreApplication>
#include <QtDebug>
#include "../falconmodelsharedlib_global.h"
class Component;
class Model;
class Instruction;
class InstructionList;
class XMLBuilder;
class MODEL_LIBRARY SubComponentList : public QObject
{
  Q_OBJECT
public:
  SubComponentList(QObject *parent = 0, Component* iComponent = 0);
  Component* parentComponent();
  QMap<int, Component*> _components;
   Component* _parentComponent;
   QString xml();
   bool isExpanded;
signals:

public slots:
  void setParentComponent(Component* iComponent);
  void addComponent(Component* iComponent);
  void removeComponent(Component* iComponent);
  void draw();
private:


};

#endif // SUBCOMPONENTLIST_H
