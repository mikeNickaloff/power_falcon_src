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
#include "subcomponentlistedit.h"
#include "src_core/component.h"
#include "src_core/model.h"
#include "src_core/subcomponentlist.h"
#include "src_handlers/glhandler.h"
#include "modeltree.h"
#include <QMapIterator>
#include <QMap>
#include "falconmodelsharedlib.h"

SubComponentListEdit::SubComponentListEdit(QWidget *parent, SubComponentList *i_subComponentList, Model *i_model) :
  QWidget(parent), _subComponentList(i_subComponentList), _model(i_model)
{
  ui.setupUi(this);
}

void SubComponentListEdit::changeEvent(QEvent *e)
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





void SubComponentListEdit::insertExistingComponent (int id, Component *component) {
 this->newItem = new QListWidgetItem(QString("Component #: %1").arg(component->componentId ()),  ui.listWidget, QListWidgetItem::UserType);
  this->_componentsHash[id] = component;
  this->_itemsHash[id] = newItem;
  ui.listWidget->insertItem (id, newItem);
}
void SubComponentListEdit::populateComponents () {
  if (this->subComponentList ()) {
      ui.listWidget->clear ();
      this->_componentsHash.clear ();
      this->_itemsHash.clear ();
      QMapIterator<int, Component*> o(subComponentList()->_components);
      o.toFront ();
      while (o.hasNext ()) {
          o.next ();
          int id = o.key ();
          Component* component = o.value();
          this->insertExistingComponent (id, component);
        }
    }
}

void SubComponentListEdit::on_buttonAddInstruction_clicked()
{
  if (this->model ()) {

          Component* new_component;
          int nextId = model()->nextComponentId ();
          new_component = new Component(model()->rootComponent (), model(), this->model ()->glHandler ());
          new_component->setComponentId (nextId);
            new_component->setObjectName (QString("%1").arg(nextId));
          subComponentList()->addComponent (new_component);
        //  QTimer::singleShot (50, model(), SLOT(clearSelection()));
          //    QTimer::singleShot (110, model(), SLOT(updateModelTree()));
          this->populateComponents ();
          emit this->updateModelTree ();
//          newComponent->initInstructionList ();
//          newComponent->initSubComponentList ();
//          if (this->subComponentList ()) {
//              this->subComponentList ()->addComponent (newComponent);
//              this->populateComponents ();
//              this->model ()->updateModelTree ();
//            }

        }

}

void SubComponentListEdit::on_buttonDeleteInstruction_clicked()
{
  if (ui.listWidget->selectedItems ().count () > 0) {
      int selIdx = this->_itemsHash.key(ui.listWidget->selectedItems ().first ());
      Component* selectedComponent;
      selectedComponent = this->_subComponentList->_components.value(selIdx);
      this->subComponentList ()->removeComponent (selectedComponent);
      //this->model ()->updateModelTree ();
       this->populateComponents ();
      emit this->updateModelTree ();


    }
}

void SubComponentListEdit::on_toolButton_clicked()
{
    if (ui.listWidget->selectedItems ().count () > 0) {
        int selIdx = this->_itemsHash.key(ui.listWidget->selectedItems ().first ());
        qDebug() << "Moving" << selIdx << "to " << selIdx - 1;
        if (selIdx > 1) {
            Component* selectedComponent;
            selectedComponent = this->_subComponentList->_components.value(selIdx);
            Component* swapComponent;
            swapComponent = this->_subComponentList->_components.value(selIdx - 1);
//            QListWidgetItem* selectedItem;
//            selectedItem = this->_itemsHash.value(selIdx);
//            QListWidgetItem* swapItem;
//            selectedItem = this->_itemsHash.value(selIdx - 1);
           this->_subComponentList->_components[selIdx] = swapComponent;
           // this->_itemsHash[selIdx] = swapItem;
           this->_subComponentList->_components[(selIdx - 1)] = selectedComponent;
            this->populateComponents ();
           // this->_itemsHash[(selIdx - 1)] = selectedItem;
         //   this->populateComponents ();
           // this->model ()->updateModelTree ();
            emit this->updateModelTree ();

          }
      }
}

void SubComponentListEdit::on_toolButton_2_clicked()
{
  if (ui.listWidget->selectedItems ().count () > 0) {
      int selIdx = this->_itemsHash.key(ui.listWidget->selectedItems ().first ());
      qDebug() << "Moving" << selIdx << "to " << selIdx + 1;
      if (selIdx < ui.listWidget->count ()) {
          Component* selectedComponent;
          selectedComponent = this->subComponentList()->_components.value(selIdx);
          Component* swapComponent;
          swapComponent = this->_subComponentList->_components.value(selIdx + 1);

         this->_subComponentList->_components[selIdx] = swapComponent;
         this->_subComponentList->_components[(selIdx + 1)] = selectedComponent;

          this->populateComponents ();
          emit this->updateModelTree ();

          //this->model ()->updateModelTree ();
        }
    }
}
