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

#ifndef INSTRUCTIONLIST_H
#define INSTRUCTIONLIST_H

#include <QObject>
#include <QCoreApplication>
#include <QMap>
#include <QtXml/QDomElement>
#include "../falconmodelsharedlib_global.h"
class Model;
class Component;
class Instruction;
class Mesh;
class MODEL_LIBRARY InstructionList : public QObject
{
  Q_OBJECT
public:
   InstructionList(QObject *parent = 0, Component* iComponent = 0);
   Component* component();
   Component* _component;
   QMap<int, Instruction*> _instructions;
   QString xml();
   bool isExpanded;
signals:

public slots:
   void setComponent(Component* iComponent);
   void addInstruction(Instruction* instruction);
   void removeInstruction(Instruction* instruction);
   void draw();
   void parseInstructionListElementXML(QDomElement &instructionListElement, Component* parentComponent);
private:


};

#endif // INSTRUCTIONLIST_H
