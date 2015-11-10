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

#ifndef INSTRUCTIONLISTEDIT_H
#define INSTRUCTIONLISTEDIT_H

#include "ui_instructionlistedit.h"
#include <QHash>
#include <QListWidget>
#include <QListWidgetItem>
#include <QMetaObject>
#include <QMetaMethod>
#include <QInputDialog>
#include "falconmodelsharedlib_global.h"
class MODEL_LIBRARY Component;
class MODEL_LIBRARY Instruction;
class MODEL_LIBRARY InstructionList;
class MODEL_LIBRARY Model;
class MODEL_LIBRARY SubComponentList;
class MODEL_LIBRARY GLHandler;
class ModelTree;
class InstructionListEdit : public QWidget
{
  Q_OBJECT

public:
   InstructionListEdit(QWidget *parent = 0, InstructionList* i_instructionList = 0, Model* i_model = 0);
   InstructionList* instructionList() {
     if (_instructionList) { return _instructionList; }
     return 0;
   }
   InstructionList* _instructionList;
   Model* model() {
     if (_model) { return _model; }
     return 0;
   }
   Model* _model;
   QHash<int, Instruction*> _instructionsHash;
   QHash<int, QListWidgetItem*> _itemsHash;
   QListWidgetItem* newItem;
   Ui::InstructionListEdit ui;

protected:
  void changeEvent(QEvent *e);
public slots:
  void insertExistingInstruction(int id, Instruction* instruction);
  void populateInstructions();

signals:
  //void swapInstructions(InstructionList* i_instructionList, Instruction* selectedInstruction, Instruction* swapInstruction);
  void swapInstructions(int parentComponent, int selIdx, int swapIdx);
void addInstruction(int parentComponent, Instruction* instruction, int instructionId);
void removeInstruction(int parentComponent, Instruction* instruction, int instructionId);
void updateModelTree();

private slots:
  void on_buttonAddInstruction_clicked();

  void on_buttonDeleteInstruction_clicked();

  void on_toolButton_clicked();

  void on_toolButton_2_clicked();

private:
};

#endif // INSTRUCTIONLISTEDIT_H
