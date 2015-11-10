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

#include "menuhandler.h"
#include <QFileDialog>
MenuHandler::MenuHandler(QObject *parent) :
  QObject(parent)
{
}
void MenuHandler::slot_action_Exit() {
    QApplication::exit (0);
}
void MenuHandler::slot_action_Resize_Level () {
emit this->signalResizeLevelRequested ();
}
void MenuHandler::slot_action_Save () {
  QFileDialog::Options options;
  //options |= QFileDialog::DontUseNativeDialog;
  QString selectedFilter;
  QString fileName = QFileDialog::getSaveFileName(0,
                          tr("QFileDialog::getSaveFileName()"),
                         _fileName,
                          tr("All Files (*);;Power Falcon Level(*.pfl)"),
                          &selectedFilter,
                          options);
  if (!fileName.isEmpty()) {
    emit this->signalSaveFile (fileName);
  }
}
void MenuHandler::slot_action_Enable_Gravity () {
  emit this->signalSetGravity (true);
}
void MenuHandler::slot_action_Disable_Gravity () {
  emit this->signalSetGravity (false);
}
void MenuHandler::slot_action_Open () {

  QString fileName = QFileDialog::getOpenFileName(0, tr("Open File"),
                                                  qApp->applicationDirPath ().append(QDir::separator ()).append("models"),
                                                   tr("All Files (*);;Power Falcon Levels(*.pfl*)"));

  if (!fileName.isEmpty()) {
    emit this->signalOpenFile (fileName);
  }
}
void MenuHandler::slot_action_Add_New_Level_Object () {
  emit this->signalAddNewLevelObject ();
}
void MenuHandler::slot_action_Open_Level_Object_Editor () {
  emit this->signalOpenLevelObjectEditor ();
}
