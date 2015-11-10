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

#ifndef MENUHANDLER_H
#define MENUHANDLER_H

#include <QObject>
#include <QApplication>

class MenuHandler : public QObject
{
  Q_OBJECT
public:
   MenuHandler(QObject *parent = 0);
   QString _fileName;
signals:
void signalSaveFile(QString fileName);
void signalSetGravity(bool gravityEnabled);
void signalOpenFile(QString fileName);
public slots:
  void slot_action_Exit();
  void slot_action_Cube();
  void slot_action_Save();
  void slot_action_Enable_Gravity();
  void slot_action_Disable_Gravity();
  void slot_action_Open();



};

#endif // MENUHANDLER_H
