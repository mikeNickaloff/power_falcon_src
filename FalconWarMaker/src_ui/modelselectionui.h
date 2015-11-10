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

#ifndef MODELSELECTIONUI_H
#define MODELSELECTIONUI_H

#include "ui_modelselectionui.h"
#include <QDomDocument>
#include <QObject>
class ModelSelectionUI : public QWidget
{
  Q_OBJECT

public:
  explicit ModelSelectionUI(QWidget *parent = 0);
  QDomDocument doc;
    Ui::ModelSelectionUI ui;
protected:
  void changeEvent(QEvent *e);

private slots:
  void on_pushButton_clicked();
signals:
  void signalModelChanged(QString xml);
private:

};

#endif // MODELSELECTIONUI_H
