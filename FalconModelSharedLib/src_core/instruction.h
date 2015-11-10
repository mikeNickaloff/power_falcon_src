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

#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include <QObject>
#include <QMetaMethod>
#include <QMetaObject>
#include <QDomElement>
#include "../falconmodelsharedlib_global.h"

class GLHandler;
class MODEL_LIBRARY Instruction : public QObject
{
  Q_OBJECT
public:
   Instruction(QObject *parent = 0, GLHandler *inp_handler = 0);
  GLHandler* m_glHandler;
//    QGenericArgument get_arg(QList<qreal> arg_list, QStringList type_list, int target_arg_index);
  QStringList get_type_list(QString command_str);
  QString command() { return m_command(); }
  QString m_command();

  QList<qreal> args() { return m_args(); }
  QList<qreal> m_args();
  QString argsAsString() {
    QStringList list;
    foreach (qreal val, args()) {
        list.append(QString("%1").arg(val));
      }
    QString rv;
    rv = list.join (", ");
    return rv;
  }

  QString xml(int keyFromParent);
  int parentComponentId;
  QHash<int, QString> paramNames;
  QHash<int, int> paramTypes;
  void parseInstructionElementXML(QDomElement &instructionElement);
signals:
   void signal_data_changed();

public slots:
   void draw() { slot_execute(); }
  void slot_execute(QString command_str, QList<qreal> arg_list);
  void slot_execute();

  void setCommand(QString iCommand) { slot_set_command(iCommand); }
  void slot_set_command(QString inp_command);

  void setArgs(QList<qreal> iArgs) { slot_set_args(iArgs); }
  void slot_set_args(QList<qreal> inp_args);

  void addArg(qreal iArg) { slot_add_arg(iArg); }
  void slot_add_arg(qreal inp_arg);

private:
  QString _command;
  QList<qreal> _args;


};

#endif // INSTRUCTION_H
