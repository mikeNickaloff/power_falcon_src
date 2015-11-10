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

#ifndef SUBCOMPONENTLISTEDIT_H
#define SUBCOMPONENTLISTEDIT_H

#include "ui_subcomponentlistedit.h"
#include <QHash>
#include <QListWidget>
#include <QListWidgetItem>
#include <QObject>
#include <QWidget>
#include <QtDebug>
#include "falconmodelsharedlib_global.h"
class MODEL_LIBRARY Component;
class MODEL_LIBRARY Instruction;
class MODEL_LIBRARY InstructionList;
class MODEL_LIBRARY Model;
class MODEL_LIBRARY SubComponentList;
class MODEL_LIBRARY GLHandler;

class ModelTree;
class SubComponentListEdit : public QWidget
{
  Q_OBJECT

public:
  SubComponentListEdit(QWidget *parent = 0, SubComponentList* i_subComponentList = 0, Model* i_model = 0);
  SubComponentList* subComponentList() {
    if (_subComponentList) { return _subComponentList; }
    qDebug() << "Tried to return subComponentList() without assignment of _subComponentList";
    return 0;
  }
  SubComponentList* _subComponentList;
  Model* model() {
    if (_model) { return _model; }
    qDebug() << "Tried to return model() without assignment of _model";

    return 0;
  }
  Model* _model;
  QHash<int, Component*> _componentsHash;
  QHash<int, QListWidgetItem*> _itemsHash;
  QListWidgetItem* newItem;
  Component* newComponent;
protected:
  void changeEvent(QEvent *e);
public slots:
  void insertExistingComponent(int id, Component* component);
  void populateComponents();
signals:
  void updateModelTree();

private:
  Ui::SubComponentListEdit ui;
private slots:
  void on_buttonAddInstruction_clicked();

  void on_buttonDeleteInstruction_clicked();

  void on_toolButton_clicked();

  void on_toolButton_2_clicked();
};

#endif // SUBCOMPONENTLISTEDIT_H
