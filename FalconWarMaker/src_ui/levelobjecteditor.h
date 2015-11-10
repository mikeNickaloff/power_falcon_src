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

#ifndef LEVELOBJECTEDITOR_H
#define LEVELOBJECTEDITOR_H

#include "ui_levelobjecteditor.h"
#include <QVector3D>
#include <QLinkedList>
#include <QDoubleSpinBox>
#include <QObject>
class LevelObjectEditor : public QDockWidget
{
  Q_OBJECT

public:
  explicit LevelObjectEditor(QWidget *parent = 0);
  QVector3D mtranslation();
  QVector3D mrotation();
  QVector3D mscale();
  QVector3D getSpannedValue(QDoubleSpinBox* xbox, QDoubleSpinBox* ybox, QDoubleSpinBox* zbox);
public slots:
  void setTranslation(QVector3D _xyz);
  void setRotation(QVector3D _xyz);
  void setScale(QVector3D _xyz);
  void addLevelObjectById(int objectId);
  void updateLevelObjectProperties(QVector3D translation, QVector3D rotation, QVector3D scale);
  void spanSpinboxes(QVector3D i_vec, QDoubleSpinBox* xbox, QDoubleSpinBox* ybox, QDoubleSpinBox* zbox);

signals:
void requestPropertiesForLevelObject(int objectIdx);
void announcePropertiesChanged(QVector3D translation, QVector3D rotation, QVector3D scale);
protected:
  void changeEvent(QEvent *e);

private slots:
  void on_list_levelObjects_currentTextChanged(const QString &currentText);

  void on_list_levelObjects_itemSelectionChanged();

  void on_spinbox_translateX_valueChanged(double arg1);

  void on_spinbox_translateY_valueChanged(double arg1);

  void on_spinbox_translateZ_valueChanged(double arg1);

  void on_spinbox_rotateY_valueChanged(double arg1);

  void on_spinbox_rotateX_valueChanged(double arg1);

  void on_spinbox_rotateZ_valueChanged(double arg1);

  void on_spinbox_scaleX_valueChanged(double arg1);

  void on_spinbox_scaleY_valueChanged(double arg1);

  void on_spinbox_scaleZ_valueChanged(double arg1);

private:
  Ui::LevelObjectEditor ui;
};

#endif // LEVELOBJECTEDITOR_H
