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

#ifndef ADDLEVELOBJECT_H
#define ADDLEVELOBJECT_H

#include "ui_addlevelobject.h"
#include "../falconmodelsharedlib_global.h"
#include <QObject>
#include <QDockWidget>
#include <QtDebug>
#include <QDialog>
class MODEL_LIBRARY Model;
class MODEL_LIBRARY Level;
class MODEL_LIBRARY LevelObject;
class ModelSelectionUI;
class AddLevelObject : public QDialog
{
  Q_OBJECT

public:
  AddLevelObject(QWidget *parent = 0, Level* i_level = 0);
  Level* level() { if (!_level) { qDebug() << "FATAL: No level specified in AddLevelObject Constructor"; qApp->exit (0); } return _level; }
  ModelSelectionUI* modelSelectionUI_;
  Level* _level;
    Ui::AddLevelObject ui;
signals:
    void xmlChanged(QString xml);
protected:
  void changeEvent(QEvent *e);
public slots:
  void setXML(QString xml);
private slots:
  void on_button_close_clicked();

private:

};

#endif // ADDLEVELOBJECT_H
