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

#include "addlevelobject.h"
#include "src_core/model.h"
#include "modelselectionui.h"
#include "src_level/level.h"
#include "src_level/levelobject.h"
#include <QtDebug>
AddLevelObject::AddLevelObject(QWidget *parent, Level *i_level) :
  QDialog(parent), _level(i_level)
{
  ui.setupUi(this);
  this->modelSelectionUI_ = new ModelSelectionUI(this);
  connect(modelSelectionUI_, SIGNAL(signalModelChanged(QString)), this, SLOT(setXML(QString)));
 // this->modelSelectionUI_->setParent (ui.modelSelectionUI);
 // this->modelSelectionUI_->show ();
}

void AddLevelObject::changeEvent(QEvent *e)
{
  QDialog::changeEvent(e);
  switch (e->type()) {
    case QEvent::LanguageChange:
      ui.retranslateUi(this);
      break;
    default:
      break;
    }
}
void AddLevelObject::setXML (QString xml) {
 qDebug() << "Loaded XML" << xml;
 emit this->xmlChanged (xml);
}

void AddLevelObject::on_button_close_clicked()
{
  disconnect(this->modelSelectionUI_, SIGNAL(signalModelChanged(QString)));
  delete this->modelSelectionUI_;
    this->accept();
}
