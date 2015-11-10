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

#include "modeltree.h"
#include <QLinkedList>
#include "../falconmodelsharedlib.h"
#include "src_core/instruction.h"
#include "src_core/instructionlist.h"

ModelTree::ModelTree(QWidget *parent) :
  QWidget(parent)
{
  ui.setupUi(this);
}

void ModelTree::changeEvent(QEvent *e)
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
QTreeWidgetItem *ModelTree::createItem(const QDomElement &element,
                                       QTreeWidgetItem *parentItem)
{
  QTreeWidgetItem *item;
  if (!_itemElements.values ().contains(element)) {
      if (parentItem) {
          item = new QTreeWidgetItem(parentItem);
          parentItem->addChild (item);
        } else {
          item = new QTreeWidgetItem(ui.treeWidget);
        }
      _itemElements.insert(item, element);

    } else {
      item = _itemElements.key(element);

    }
  if (element.hasAttribute ("expanded")) {
  if (element.attribute ("expanded", "0").toInt() == 1) {

      parentItem->setExpanded (true);
      ui.treeWidget->expandItem (parentItem);
      item->setExpanded (true);
      ui.treeWidget->expandItem (item);
      //         QTreeWidgetItem* parent = item->parent ();
      //         if (parent) {
      //             parent->setExpanded (true);
      //             ui.treeWidget->expandItem (parent);
      //           }

    }
    }



  return item;
}
void ModelTree::parseElement (const QDomElement &element, QTreeWidgetItem *parentItem) {
  QString tag = element.tagName ();
  QTreeWidgetItem* currentItem;
  currentItem = createItem(element, parentItem);
  currentItem->setText (0, tag);
  if (tag == "model") {
      currentItem->setExpanded (true);
    }
  if (tag == "Component") {
      if ((element.attribute ("id").toInt() == 0) || (element.attribute("expanded").toInt()== 1)) {
          currentItem->setExpanded (true);
        }
    }
  if (element.hasAttribute ("attr")) {

      currentItem->setText(0, element.attribute ("attr"));

    }
  if (tag == "param" ) {
      currentItem->setText (0, element.attribute ("name"));
    } else {
      if (tag == "Instruction") {
          currentItem->setText (0, element.attribute ("command").right(element.attribute ("command").length () - 5));

        }
      QDomNodeList childElements = element.elementsByTagName (QString());
      for (int i=0; i<childElements.length (); i++) {
          parseElement(childElements.item(i).toElement (), currentItem);
        }

    }
}
void ModelTree::populate () {
  this->_itemElements.clear();
  ui.treeWidget->blockSignals (true);
ui.treeWidget->setEnabled (false);
  ui.treeWidget->clear ();
  parseElement(this->domDocument.documentElement (), 0);
  ui.treeWidget->blockSignals (false);
  ui.treeWidget->setEnabled (true);
}

void ModelTree::on_treeWidget_itemSelectionChanged()
{
  processSelectedItem();
}

void ModelTree::on_treeWidget_itemClicked(QTreeWidgetItem *item, int column)
{
  processSelectedItem();
}
void ModelTree::processSelectedItem () {
  if (ui.treeWidget->selectedItems ().count () > 0)
    {
      QDomElement element;
      QTreeWidgetItem* item = ui.treeWidget->selectedItems ().first ();
      qDebug() << "Selected Item has" << item->childCount () << "children";
      item->setExpanded (true);

      if (this->_itemElements.keys ().contains(item)) {
          element = this->_itemElements.value(item);
          element.setAttribute ("expanded", 1);
          int componentId = 0;
          if (element.tagName () != "model") {
              if (element.tagName () == "Component") {
                  componentId = element.attribute ("id").toInt();
                  emit this->signalSelectedComponent (componentId);
                } else {
                  QString tag = element.tagName ();
                  componentId = element.attribute ("parentComponent").toInt();
                  int elementId = 0;
                  if (tag == "Instruction") {
                      elementId = element.attribute ("id").toInt();
                      emit this->signalSelectedInstruction (elementId, componentId);
                    } else {
                      if (tag == "param") {
                          elementId = element.attribute ("id").toInt();
                          int instructionId = element.attribute("parentInstruction").toInt();
                          emit this->signalSelectedParam (elementId, instructionId, componentId);
                          //  qDebug() << "Selected" << element.tagName () << elementId << "from Instruction" << instructionId << "from Component" << componentId;
                        } else {
                          if (tag == "InstructionList") {
                              emit this->signalSelectedInstructionList (componentId);
                            } else {

                              if (tag == "SubComponentList") {
                                  emit this->signalSelectedSubComponentList (componentId);

                                }
                            }
                          //qDebug() << "Selected" << element.tagName () << elementId << "from Component" << componentId;
                        }
                    }


                }

            } else {

              emit this->signalSelectedModel ();
            }
        }
    } else {
      emit this->signalSelectCleared();
    }
}
void ModelTree::setParamCount(int paramCount) {
  QList<QLabel*> labels;
  labels << ui.label_1 << ui.label_2 << ui.label_3 << ui.label_4;
  QList<QDoubleSpinBox*> spinboxes;
  spinboxes << ui.doubleSpinBox << ui.doubleSpinBox_2 << ui.doubleSpinBox_3 << ui.doubleSpinBox_4;
  int i = 0;
  foreach (QLabel* label, labels) {
      if (label)
        label->setVisible (false);
    }
  foreach (QDoubleSpinBox* box, spinboxes) {
      if (box)
        box->setVisible(false);
    }

  while (i < paramCount) {
      if (labels.at(i))
        labels.at(i)->setVisible (true);
      if (spinboxes.at(i))
        spinboxes.at(i)->setVisible (true);
      i++;
    }

}

void ModelTree::setParamName(int paramId, QString paramName) {
  QList<QLabel*> labels;
  labels << ui.label_1 << ui.label_2 << ui.label_3 << ui.label_4;
  if (labels.at(paramId))
    labels.at(paramId)->setText (paramName);
}

void ModelTree::setParamValue(int paramId, qreal paramValue) {
  QList<QDoubleSpinBox*> spinboxes;
  spinboxes << ui.doubleSpinBox << ui.doubleSpinBox_2 << ui.doubleSpinBox_3 << ui.doubleSpinBox_4;
  if (spinboxes.at(paramId)) {
      if (spinboxes.at(paramId)->value () != paramValue) {
          spinboxes.at(paramId)->setValue (paramValue);
        }
    }
   this->updateSliders ();
}

void ModelTree::on_treeWidget_itemExpanded(QTreeWidgetItem *item)
{
  QDomElement element;
  ui.treeWidget->clearSelection ();
  ui.treeWidget->setItemSelected (item, true);
  if (this->_itemElements.keys ().contains(item)) {
      element = this->_itemElements.value(item);
      int componentId = 0;
      if (element.tagName () == "model") {

        }
      if (element.tagName () == "Component") {
          componentId = element.attribute ("id").toInt();
          //  emit this->signalExpandedComponent (componentId);


        }
      QTreeWidgetItem *ancestor = item->parent();
      while (ancestor) {
          if (ancestor->text (0) == "Component") {
              ui.treeWidget->expandItem (ancestor);
            }
          if (ancestor->isExpanded ()) {
              ancestor = 0;
            } else {
              ancestor = item->parent ();
            }
        }
    }
  //  if (this->_itemElements.keys().contains(item)) {
  //      QDomElement element = this->_itemElements.value (item);

  //      QList< QPair<QDomElement, bool> > elementPairs;

  //      elementPairs << this->_elementExpandedState.values();
  //      bool found = false;
  //      for (int i = 0; i<elementPairs.count ();i++) {
  //          QPair<QDomElement, bool> pair = elementPairs.at(i);
  //          if (pair.first == element) {
  //              pair.second = true;
  //              this->_elementExpandedState[this->_elementExpandedState.key(pair)] = pair;
  //              found = true;
  //            }
  //        }
  //      if (!found) {
  //          this->_elementExpandedState[this->_elementExpandedState.count () + 1] = qMakePair(element, true);
  //        }


  //      // this->_elementExpandedState[element] = true;
  //      ui.treeWidget->setItemSelected (item, true);
  //      this->on_treeWidget_itemSelectionChanged ();
  //    }
}

void ModelTree::on_treeWidget_itemCollapsed(QTreeWidgetItem *item)
{
  //  if (this->_itemElements.keys().contains(item)) {
  //      QDomElement element = this->_itemElements.value (item);
  //this->_elementExpandedState[element] = false;
  // }
  // ui.treeWidget->clearSelection ();
  // ui.treeWidget->setItemSelected (item, false);
  //  this->on_treeWidget_itemSelectionChanged ();
}

void ModelTree::on_doubleSpinBox_valueChanged(double arg1)
{
  emit this->signalParamValueChanged (0, (qreal) arg1);
}

void ModelTree::on_doubleSpinBox_2_valueChanged(double arg1)
{
  emit this->signalParamValueChanged (1, (qreal) arg1);

}
void ModelTree::on_doubleSpinBox_3_valueChanged(double arg1)
{
  emit this->signalParamValueChanged (2, (qreal) arg1);

}

void ModelTree::on_doubleSpinBox_4_valueChanged(double arg1)
{
  emit this->signalParamValueChanged (3, (qreal) arg1);

}


void ModelTree::expandInstructionList (int componentId) {
  QHash<QTreeWidgetItem*, QDomElement>::const_iterator o;
  o = this->_itemElements.constBegin ();
  while (o != this->_itemElements.constEnd ()) {
      QDomElement element = o.value ();
      QTreeWidgetItem* item = o.key ();
      if (element.tagName () == "InstructionList") {
          if (element.attribute ("parentComponent").toInt() == componentId) {
              element.setAttribute ("expanded", 1);
              item->setExpanded (true);
            }
        }
      if (element.tagName () == "Component") {
          if ((element.attribute ("id").toInt() == componentId) || (element.attribute ("id").toInt() == 0)) {
              item->setExpanded (true);
              element.setAttribute ("expanded", 1);
            }
        }
      if (element.tagName () == "model") {
          item->setExpanded (true);
          element.setAttribute ("expanded", 1);
        }
      o++;
    }
  // emit this->updateXMLFromTree ();
}
void ModelTree::swapInstructions (int parentComponent, int selIdx, int swapIdx) {
  QHash<QTreeWidgetItem*, QDomElement>::const_iterator o;
  o = this->_itemElements.constBegin ();
  //QTreeWidgetItem* item = ui.treeWidget->selectedItems ().first ();
 // qDebug() << "Selected Item has" << item->childCount () << "children";
  while (o != this->_itemElements.constEnd ()) {
      QDomElement element = o.value ();
      QTreeWidgetItem* item = o.key ();
      if (element.tagName () == "InstructionList") {
          if (element.attribute ("parentComponent").toInt() == parentComponent) {
              qDebug() << "Found instructionList with parent Component" << parentComponent;
              qDebug() << "Item has "<< item->childCount () << "children";
              QTreeWidgetItem* selItem = item->child (selIdx - 1);
              qDebug() << "selected item is at index" << item->indexOfChild (selItem);
              int oldIdx = item->indexOfChild (selItem);
              item->takeChild (oldIdx);
              if (swapIdx > selIdx) {
                  oldIdx++;
                } else {
                  oldIdx--;
                }
              //qDebug() << "Selected item" << selItem->text (0) << item->indexOfChild (selItem);
              // QTreeWidgetItem* swapItem = item->takeChild (swapIdx - 1);


              // qDebug() << "Swap item" << swapItem->text (0) << item->indexOfChild (swapItem);
              //                   item->insertChild (swapIdx - 1, selItem);

              item->insertChild (oldIdx, selItem);



              ui.treeWidget->repaint ();
              //ui.treeWidget->reexpand ();

            }

        }
      o++;
    }
  this->populate ();

}
void ModelTree::addInstruction (int parentComponent, Instruction *instruction,int instructionId) {
  QDomDocument frag;
  frag.setContent (instruction->xml(instructionId));

  qDebug() << frag.toString ();
  QHash<QTreeWidgetItem*, QDomElement>::const_iterator o;
  o = this->_itemElements.constBegin ();
  while (o != this->_itemElements.constEnd ()) {
      QDomElement element = o.value ();
      QTreeWidgetItem* item = o.key ();
      if (element.tagName () == "InstructionList") {
          if (element.attribute ("parentComponent").toInt() == parentComponent) {
              element.appendChild (frag);

            }
        }
      o++;

    }
  QDomDocument newDoc;
  newDoc.setContent (domDocument.toString ());
  domDocument.setContent (newDoc.toString ());
  this->_elementExpandedState.clear ();
  this->_itemElements.clear ();
  ui.treeWidget->clear ();
  this->populate ();

  o = this->_itemElements.constBegin ();
  while (o != this->_itemElements.constEnd ()) {
      QDomElement element = o.value ();
      QTreeWidgetItem* item = o.key ();

     if (element.attribute ("expanded").toInt() == 1) {
         item->setExpanded (true);
         ui.treeWidget->expandItem (item);
       }

      o++;
    }


}
void ModelTree::updateSliders () {
  QList<QDoubleSpinBox*> spinboxes;
  spinboxes << ui.doubleSpinBox << ui.doubleSpinBox_2 << ui.doubleSpinBox_3 << ui.doubleSpinBox_4;
  QList<QSlider*> sliders;
  sliders << ui.sliderIncrement1 << ui.sliderIncrement2 << ui.sliderIncrement3 << ui.sliderIncrement4;
  for (int i=0; i<sliders.count ();i++) {
      QDoubleSpinBox* sb = spinboxes.at(i);
      QSlider* sl = sliders.at(i);
      qreal sbInc = sb->singleStep ();
      sbInc *= 1000;
      sbInc = 1000 - sbInc;
      sl->setValue (qRound(sbInc));
    }
}
void ModelTree::updateSpinBoxes () {
  QList<QDoubleSpinBox*> spinboxes;
  spinboxes << ui.doubleSpinBox << ui.doubleSpinBox_2 << ui.doubleSpinBox_3 << ui.doubleSpinBox_4;
  QList<QSlider*> sliders;
  sliders << ui.sliderIncrement1 << ui.sliderIncrement2 << ui.sliderIncrement3 << ui.sliderIncrement4;
  for (int i=0; i<sliders.count ();i++) {
      QDoubleSpinBox* sb = spinboxes.at(i);
      QSlider* sl = sliders.at(i);
      qreal sbInc = sl->value ();
      sbInc = 10.0 / sbInc;
      sb->setSingleStep (sbInc);
    }
}

void ModelTree::on_sliderIncrement1_valueChanged(int value)
{
    this->updateSpinBoxes ();
}

void ModelTree::on_sliderIncrement2_valueChanged(int value)
{
       this->updateSpinBoxes ();
}

void ModelTree::on_sliderIncrement3_valueChanged(int value)
{
       this->updateSpinBoxes ();
}

void ModelTree::on_sliderIncrement4_valueChanged(int value)
{
       this->updateSpinBoxes ();
}
