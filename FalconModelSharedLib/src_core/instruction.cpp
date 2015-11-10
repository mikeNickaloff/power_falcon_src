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

#include "instruction.h"
#include "../src_handlers/glhandler.h"
#include <QtDebug>
Instruction::Instruction(QObject *parent, GLHandler *inp_handler) :
  QObject(parent), m_glHandler(inp_handler)
{
  this->_command = QString();
  this->parentComponentId = 0;
}
void Instruction::slot_execute() {
  this->slot_execute(m_command(), m_args());
}
void Instruction::slot_execute( QString command_str, QList<qreal> arg_list) {
  qreal vals[10];
  int invalid_ptr = 65535;
  if (arg_list.contains(invalid_ptr)) {
      while (arg_list.contains(invalid_ptr)) { invalid_ptr++; }
    }
  for (int i=1; i<10; ++i) {
      if (arg_list.size() > (i - 1)) { vals[i] = arg_list.at(i - 1); } else {
          vals[i] = invalid_ptr;
        }
    }
  // QStringList t_list; t_list << this->get_type_list(command_str);
  const QMetaObject* metaObject = qobject_cast<GLHandler*>(this->m_glHandler)->metaObject();
  // QMetaType::type(QString(t_list.at(0)).toLocal8Bit());
  //QMetaType* types[10];
  if (metaObject == 0) { /* metaobject fail */ }
  bool success =  metaObject->invokeMethod(
        m_glHandler, command_str.toLocal8Bit(), Qt::DirectConnection,
        vals[1] != invalid_ptr ? Q_ARG(qreal, vals[1]) : QGenericArgument(),
    vals[2] != invalid_ptr ? Q_ARG(qreal, vals[2]) : QGenericArgument(),
    vals[3] != invalid_ptr ? Q_ARG(qreal, vals[3]) : QGenericArgument(),
    vals[4] != invalid_ptr ? Q_ARG(qreal, vals[4]) : QGenericArgument(),
    vals[5] != invalid_ptr ? Q_ARG(qreal, vals[5]) : QGenericArgument(),
    vals[6] != invalid_ptr ? Q_ARG(qreal, vals[6]) : QGenericArgument(),
    vals[7] != invalid_ptr ? Q_ARG(qreal, vals[7]) : QGenericArgument(),
    vals[8] != invalid_ptr ? Q_ARG(qreal, vals[8]) : QGenericArgument());
  //   qDebug() << "Executing of routine" << "success = " << success;
  if (!success) { /*qDebug() << "Routine Failed to Execute!";*/ }
}

QStringList Instruction::get_type_list(QString command_str) {
  QStringList rv;
  const QMetaObject* metaObject = qobject_cast<GLHandler*>(this->m_glHandler)->metaObject();
  for(int i = metaObject->methodOffset(); i < metaObject->methodCount(); ++i) {
      QString property = QString::fromLatin1(metaObject->method(i).methodSignature());
      property.remove(")", Qt::CaseInsensitive);
      QStringList properties;
      properties << property.split("(", QString::KeepEmptyParts, Qt::CaseInsensitive);
      QStringListIterator o(properties);
      o.toFront();
      if (o.hasNext()) {
          QString cmd_str = o.next();
          if (cmd_str == command_str) {
              if (o.hasNext()) {
                  QString param_str = o.next();
                  rv << param_str.split(",", QString::SkipEmptyParts, Qt::CaseInsensitive);
                }
            }
        }


    }
  return rv;
}

QString Instruction::m_command() {
  if (this->_command.length() > 0) { return this->_command; } else {
      return QString("slot_none");
    }
}
QList<qreal> Instruction::m_args() {
  if (this->_args.size() > 0) { return this->_args; } else {
      QList<qreal> rv; return rv;
    }
}
QString Instruction::xml (int keyFromParent) {
  QString rv;
  rv.append(QString("<Instruction id=\"%1\" command=\"%2\" parentComponent=\"%3\">").arg(keyFromParent).arg(this->m_command ()).arg(this->parentComponentId));
  int paramIdx = 0;
  int mIdx = 0;
 this->paramNames.clear ();
  this->paramTypes.clear ();
  while (mIdx < m_glHandler->metaObject ()->methodCount ()) {
      QMetaMethod method = this->m_glHandler->metaObject ()->method (mIdx);

      if (m_command().toUpper () == QString::fromLocal8Bit (method.name ()).toUpper ()) {
          int pIdx = 0;
          foreach (QByteArray name, method.parameterNames ()) {
              paramNames[method.parameterNames ().indexOf (name)] = QString::fromLocal8Bit (name);
              paramTypes[method.parameterNames ().indexOf (name)] = method.parameterType (method.parameterNames ().indexOf (name));
            }
        }

      mIdx++;
    }
  foreach (qreal val, m_args()) {

      rv.append(QString("<param id=\"%1\" name=\"%3\" parentInstruction=\"%5\" parentComponent=\"%4\" paramType=\"%6\">%2</param>").arg(paramIdx).arg(val).arg(paramNames.value(paramIdx)).arg(this->parentComponentId).arg(keyFromParent).arg(paramTypes.value(paramIdx)));
      paramIdx++;
    }
  rv.append("</Instruction>");
  return rv;
}



void Instruction::parseInstructionElementXML(QDomElement &instructionElement) {
  QDomNodeList list = instructionElement.elementsByTagName ("param");
  for (int i=0; i<list.length (); i++) {
     QDomElement paramElement = list.item(i).toElement ();
     qreal argval;
     argval = (qreal) paramElement.text ().toFloat ();
     this->addArg (argval);
    }
}


void Instruction::slot_set_command(QString inp_command) {
  this->_command = inp_command;
  emit this->signal_data_changed();
}

void Instruction::slot_set_args(QList<qreal> inp_args) {
  // qDebug() << "ROUTINE ARGS CHANGED from " << _args << "to" << inp_args;
  this->_args.clear();
  this->_args << inp_args;
  emit this->signal_data_changed();

}

void Instruction::slot_add_arg(qreal inp_arg) {
  this->_args << inp_arg;
  emit this->signal_data_changed();
}
