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

#include "modelselectionui.h"
#include <QFileDialog>
#include <QFile>
#include <QObject>
#include <QDomDocument>

ModelSelectionUI::ModelSelectionUI(QWidget *parent) :
  QWidget(parent)
{
  ui.setupUi(this);
}

void ModelSelectionUI::changeEvent(QEvent *e)
{
  QWidget::changeEvent(e);
  switch (e->type()) {
    case QEvent::LanguageChange:
      ui.retranslateUi(this);
      break;
    default:
      break;
    }
}

void ModelSelectionUI::on_pushButton_clicked()
{
  QString fileName = QFileDialog::getOpenFileName(0, tr("Open File"),
                                                  qApp->applicationDirPath ().append(QDir::separator ()).append("models"),
                                                  tr("All Files (*);;Power Falcon Models(*.pfm*)"));

  if (!fileName.isEmpty()) {
      QString str;
      QFile file(fileName);
      if (file.open (QIODevice::ReadOnly)) {
          QString errorMsg;
          int errorLine;
          int errorColumn;
          doc.setContent (file.readAll (), false , &errorMsg, &errorLine, &errorColumn);
          ui.pushButton->setText ("Change...");
          emit this->signalModelChanged (doc.toString (0));
        }
      file.close ();
    }
}
