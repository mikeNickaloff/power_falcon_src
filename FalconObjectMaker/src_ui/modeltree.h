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

#ifndef MODELTREE_H
#define MODELTREE_H
#include <QDomDocument>
#include <QHash>
#include <QIcon>
#include <QTreeWidget>
#include <QtDebug>
#include "ui_modeltree.h"
#include <QObject>
#include <QTreeWidgetItem>
#include "falconmodelsharedlib_global.h"
class MODEL_LIBRARY Instruction;
class ModelTree : public QWidget
{
  Q_OBJECT

public:
  explicit ModelTree(QWidget *parent = 0);
  QTreeWidgetItem *createItem(const QDomElement &element, QTreeWidgetItem *parentItem = 0);

  QDomDocument domDocument;
  QHash<QTreeWidgetItem *, QDomElement> _itemElements;
  QHash<int, QPair<QDomElement,bool> > _elementExpandedState;
  int spinboxCount;
    Ui::ModelTree ui;
signals:
  void signalSelectedComponent(int componentId);
  void signalSelectedInstructionList(int componentId);
  void signalSelectedSubComponentList(int componentId);
  void signalSelectedInstruction(int instructionId, int componentId);
  void signalSelectedParam(int paramId, int instructionId, int componentId);
  void signalSelectCleared();
  void signalParamValueChanged(int paramId, qreal value);
  void signalSelectedModel();

  void signalExpandedComponent(int componentId);
  void updateXMLFromTree();
public slots:
  void populate();
  void parseElement(const QDomElement &element, QTreeWidgetItem *parentItem = 0);
  void processSelectedItem();
  void setParamCount(int paramCount);
  void setParamName(int paramId, QString paramName);
  void setParamValue(int paramId, qreal paramValue);
  void expandInstructionList(int componentId);
  void swapInstructions(int parentComponent, int selIdx, int swapIdx);
  void addInstruction(int parentComponent, Instruction* instruction, int instructionId);
  void updateSliders();
  void updateSpinBoxes();

protected:
  void changeEvent(QEvent *e);

private slots:
  void on_treeWidget_itemSelectionChanged();

  void on_treeWidget_itemClicked(QTreeWidgetItem *item, int column);

  void on_treeWidget_itemExpanded(QTreeWidgetItem *item);

  void on_treeWidget_itemCollapsed(QTreeWidgetItem *item);

  void on_doubleSpinBox_valueChanged(double arg1);

  void on_doubleSpinBox_2_valueChanged(double arg1);

    void on_doubleSpinBox_3_valueChanged(double arg1);

  void on_doubleSpinBox_4_valueChanged(double arg1);



  void on_sliderIncrement1_valueChanged(int value);

  void on_sliderIncrement2_valueChanged(int value);

  void on_sliderIncrement3_valueChanged(int value);

  void on_sliderIncrement4_valueChanged(int value);

private:

};

#endif // MODELTREE_H
