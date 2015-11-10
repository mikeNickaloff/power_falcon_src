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

#include "instructionlist.h"
#include "model.h"
#include "component.h"
#include "instruction.h"
//#include "../src_xml/xmlbuilder.h"
#include "mesh.h"
InstructionList::InstructionList(QObject *parent, Component *iComponent) :
  QObject(parent), _component(iComponent)
{
  isExpanded = false;
}
Component* InstructionList::component () {
  if (!_component) {
      qDebug() << "FATAL: A call to the method  [ component() ]  was made to an  [ InstructionList ] that did not have a Component assigned in the constructor or via setComponent() ";
      qApp->exit (-1);

    }
  return _component;
}


QString InstructionList::xml () {
  QString rv;
  //  XMLBuilder* builder = new XMLBuilder(this, "InstructionList");
  //builder->setRootElementAttribute ("parentComponent", component());
  //  foreach (Instruction* value, this->_instructions) {
  //      QStringList args;
  //      foreach (qreal arg, value->m_args ()) {
  //          args << QString("%1").arg(arg);
  //        }

  //      builder->insertElement ("Instruction", QString("%1").arg(_instructions.key (value)), args.join (" , "));

  //    }
  //  rv = builder->string ();

  rv.append(QString("<InstructionList parentComponent=\"%1\" expanded=\"%2\">").arg(component()->componentId ()).arg(isExpanded));
  foreach (Instruction* value, this->_instructions) {
      if (value->m_command () == "mesh") {
          Mesh* mesh = qobject_cast<Mesh*>(value);
          rv.append(mesh->xml(_instructions.key(value)));
        } else {
          rv.append(value->xml (_instructions.key(value)));
        }
    }
  rv.append("</InstructionList>");

  return rv;
}

void InstructionList::setComponent (Component *iComponent) {
  _component = iComponent;
}
void InstructionList::addInstruction(Instruction* instruction) {
  QList<int> keys; keys << _instructions.keys ();
  int newKey = 1;
  if (keys.count () > 0) {
      //  qSort(keys.begin (), keys.end ());
      int lastKey = keys.last ();
      newKey = lastKey + 1;
    }
  while (keys.contains(newKey)) {
      newKey++;
    }
  _instructions[newKey] = instruction;
  instruction->parentComponentId = component()->componentId ();
}

void InstructionList::removeInstruction(Instruction* instruction) {
  QMap<int, Instruction*>::iterator o = _instructions.begin ();
  while (o != _instructions.end ()) {
      Instruction* value = o.value ();
      if (value == instruction) {
          o = _instructions.erase (o);
        } else {
          o++;
        }

    }
}
void InstructionList::draw () {
  foreach (Instruction* value, this->_instructions) {
      if (value->m_command () == "mesh") {
          Mesh* mesh = qobject_cast<Mesh*>(value);
          mesh->draw ();
        } else {
          value->draw ();
        }
    }
}


void InstructionList::parseInstructionListElementXML(QDomElement &instructionListElement, Component* parentComponent) {
  QDomNodeList list = instructionListElement.elementsByTagName ("Instruction");
  for (int i=0; i<list.length (); i++) {
     QDomElement instructionElement = list.item(i).toElement ();
     Instruction* instruction = new Instruction(component()->model(), component()->glHandler ());

    instruction->setCommand (instructionElement.attribute ("command"));
    instruction->parseInstructionElementXML (instructionElement);
    instruction->parentComponentId = parentComponent->componentId ();
    this->addInstruction (instruction);
    }
}
