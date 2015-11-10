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

#include "instructionlistedit.h"
#include "src_core/instruction.h"
#include "src_core/model.h"
#include "src_core/instructionlist.h"
#include "src_handlers/glhandler.h"
#include "src_core/component.h"
#include "../src_ui/modeltree.h"
#include <QMapIterator>
#include <QMap>
#include <QtDebug>
#include <QMutableMapIterator>
#include "falconmodelsharedlib.h"
InstructionListEdit::InstructionListEdit(QWidget *parent, InstructionList *i_instructionList, Model *i_model) :
  QWidget(parent), _instructionList(i_instructionList), _model(i_model)
{
  ui.setupUi(this);
}

void InstructionListEdit::changeEvent(QEvent *e)
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
void InstructionListEdit::insertExistingInstruction (int id, Instruction *instruction) {
  this->newItem = new QListWidgetItem(instruction->m_command ().append(" [ %1 ] ").arg( instruction->argsAsString ()),  ui.listWidget, QListWidgetItem::UserType);
  this->_instructionsHash[id] = instruction;
  this->_itemsHash[id] = newItem;
  ui.listWidget->insertItem (id, newItem);
}
void InstructionListEdit::populateInstructions () {
  if (this->instructionList ()) {
      ui.listWidget->clear ();
      this->_instructionsHash.clear ();
      this->_itemsHash.clear ();
      QMapIterator<int, Instruction*> o(instructionList()->_instructions);
      o.toFront ();
      while (o.hasNext ()) {
          o.next ();
          int id = o.key ();
          Instruction* instruction = o.value ();
          this->insertExistingInstruction (id, instruction);
        }
    }
}

void InstructionListEdit::on_buttonAddInstruction_clicked()
{
  if (this->model ()) {
      QStringList items;
      const QMetaObject* metaObject = this->model ()->glHandler ()->metaObject ();
      for (int i=0; i< metaObject->methodCount (); i++) {
          QMetaMethod method = metaObject->method (i);
          if (method.name ().left (5).toLower () == "slot_")
            items << QString::fromUtf8 (method.name());

        }
      bool ok;
      QString item = QInputDialog::getItem(this, tr("Select Instruction Command"),
                                           tr("Instruction Command:"), items, 0, false, &ok);
      if (ok && !item.isEmpty()) {
          QList<qreal> args;
          const QMetaObject* metaObject = this->model ()->glHandler ()->metaObject ();
          for (int i=0; i< metaObject->methodCount (); i++) {
              QMetaMethod method = metaObject->method (i);
              if (method.name () == item) {
                  for (int e=0; e<method.parameterCount (); e++) {
                      args << 0.0;
                    }
                }
            }
          Instruction* instruction = this->model ()->createInstruction (item, args);
          this->instructionList ()->addInstruction (instruction);
          this->populateInstructions ();
          int instructionId = this->instructionList ()->_instructions.key(instruction, 1);
          emit this->addInstruction (this->instructionList ()->_component->componentId (), instruction, instructionId);

          // this->model ()->updateModelTree ();
        }
    }

}

void InstructionListEdit::on_buttonDeleteInstruction_clicked()
{
  if (ui.listWidget->selectedItems ().count () > 0) {
      int selIdx = this->_itemsHash.key(ui.listWidget->selectedItems ().first ());
      QMutableMapIterator<int, Instruction*> i (this->instructionList ()->_instructions);
      Instruction* instructRemoved;
      int idxRemoved;
      while (i.hasNext ()) {
          i.next ();
          int idx = i.key ();
          if (idx == selIdx) {
              instructRemoved = i.value();
              idxRemoved = i.key ();

              this->instructionList ()->removeInstruction (i.value ());
            }
          if (idx > selIdx) {
              Instruction* instruction = i.value ();
              idx--;
              this->instructionList ()->_instructions[idx] = instruction;
              this->instructionList()->_instructions.remove(idx + 1);
            }
          if (!i.hasNext ()) {
              this->instructionList ()->_instructions.remove (i.key ());
            }

        }
      this->populateInstructions ();
      emit this->removeInstruction (instructionList()->component ()->componentId (), instructRemoved, idxRemoved);
    }


}

void InstructionListEdit::on_toolButton_clicked()
{
  if (ui.listWidget->selectedItems ().count () > 0) {
      int selIdx = this->_itemsHash.key(ui.listWidget->selectedItems ().first ());
      qDebug() << "Moving" << selIdx << "to " << selIdx - 1;
      if (selIdx > 1) {
          Instruction* selectedInstruction;
          selectedInstruction = this->_instructionList->_instructions.value(selIdx);
          Instruction* swapInstruction;
          swapInstruction = this->_instructionList->_instructions.value(selIdx - 1);
          //            QListWidgetItem* selectedItem;
          //            selectedItem = this->_itemsHash.value(selIdx);
          //            QListWidgetItem* swapItem;
          //            selectedItem = this->_itemsHash.value(selIdx - 1);
          this->_instructionList->_instructions[selIdx] = swapInstruction;
          // this->_itemsHash[selIdx] = swapItem;
          this->_instructionList->_instructions[(selIdx - 1)] = selectedInstruction;

          emit this->swapInstructions (this->_instructionList->component ()->componentId (), selIdx, selIdx - 1);
          // this->_itemsHash[(selIdx - 1)] = selectedItem;
          this->populateInstructions ();
          //  this->model ()->updateModelTree ();
          emit this->updateModelTree ();
        }
    }
}

void InstructionListEdit::on_toolButton_2_clicked()
{
  if (ui.listWidget->selectedItems ().count () > 0) {
      int selIdx = this->_itemsHash.key(ui.listWidget->selectedItems ().first ());
      qDebug() << "Moving" << selIdx << "to " << selIdx + 1;
      if ((selIdx + 1) <= (ui.listWidget->count ())) {
          Instruction* selectedInstruction;
          selectedInstruction = this->_instructionList->_instructions.value(selIdx);
          Instruction* swapInstruction;
          swapInstruction = this->_instructionList->_instructions.value(selIdx + 1);

          this->_instructionList->_instructions[selIdx] = swapInstruction;
          this->_instructionList->_instructions[(selIdx + 1)] = selectedInstruction;
          //  emit this->swapInstructions (this->_instructionList, selectedInstruction, swapInstruction);
          emit this->swapInstructions (this->_instructionList->component ()->componentId (), selIdx, selIdx + 1);
          this->populateInstructions ();
          // this->model ()->updateModelTree ();
          emit this->updateModelTree ();
        }
    }
}
