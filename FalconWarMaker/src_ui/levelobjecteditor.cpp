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

#include "levelobjecteditor.h"

LevelObjectEditor::LevelObjectEditor(QWidget *parent) :
  QDockWidget(parent)
{
  ui.setupUi(this);
}

QVector3D LevelObjectEditor::mtranslation() {
  return getSpannedValue ( ui.spinbox_translateX, ui.spinbox_translateY, ui.spinbox_translateZ);

}

QVector3D LevelObjectEditor::mrotation() {
  return getSpannedValue(ui.spinbox_rotateX, ui.spinbox_rotateY, ui.spinbox_rotateZ);

}

QVector3D LevelObjectEditor::mscale() {
   return getSpannedValue( ui.spinbox_scaleX, ui.spinbox_scaleY, ui.spinbox_scaleZ);
}

QVector3D LevelObjectEditor::getSpannedValue( QDoubleSpinBox* xbox, QDoubleSpinBox* ybox, QDoubleSpinBox* zbox) {
  QVector3D rv;
  qreal x_;
  qreal y_;
  qreal z_;
  x_ = xbox->value();
  y_ = ybox->value();
  z_ = zbox->value();
  rv  = QVector3D(x_, y_, z_);
  return rv;
}
void LevelObjectEditor::changeEvent(QEvent *e)
{
  QDockWidget::changeEvent(e);
  switch (e->type()) {
    case QEvent::LanguageChange:
      ui.retranslateUi(this);
      break;
    default:
      break;
    }
}
void LevelObjectEditor::setTranslation(QVector3D _xyz) {
  QLinkedList<float> vec;
  QLinkedList<QDoubleSpinBox*> boxes;
  vec << _xyz.x () << _xyz.y () << _xyz.z ();
  boxes << ui.spinbox_translateX << ui.spinbox_translateY << ui.spinbox_translateZ;
  for (int i=0; i<3; ++i) {
      QDoubleSpinBox* box = boxes.takeFirst ();
      float val = vec.takeFirst ();
      box->setValue ((double) val);
    }
}

void LevelObjectEditor::setRotation(QVector3D _xyz) {
  QLinkedList<float> vec;
  QLinkedList<QDoubleSpinBox*> boxes;
  vec << _xyz.x () << _xyz.y () << _xyz.z ();
  boxes << ui.spinbox_rotateX << ui.spinbox_rotateY << ui.spinbox_rotateZ;
  for (int i=0; i<3; ++i) {
      QDoubleSpinBox* box = boxes.takeFirst ();
      float val = vec.takeFirst ();
      box->setValue ((double) val);
    }
}

void LevelObjectEditor::setScale(QVector3D _xyz) {
  QLinkedList<float> vec;
  QLinkedList<QDoubleSpinBox*> boxes;
  vec << _xyz.x () << _xyz.y () << _xyz.z ();
  boxes << ui.spinbox_scaleX << ui.spinbox_scaleY << ui.spinbox_scaleZ;
  for (int i=0; i<3; ++i) {
      QDoubleSpinBox* box = boxes.takeFirst ();
      float val = vec.takeFirst ();
      box->setValue ((double) val);
    }
}
void LevelObjectEditor::addLevelObjectById(int objectId) {
  ui.list_levelObjects->insertItem (ui.list_levelObjects->count (), QString("%1").arg(objectId));
}

void LevelObjectEditor::on_list_levelObjects_currentTextChanged(const QString &currentText)
{
this->on_list_levelObjects_itemSelectionChanged ();
}

void LevelObjectEditor::on_list_levelObjects_itemSelectionChanged()
{
    if (ui.list_levelObjects->selectedItems ().count () > 0) {
        ui.group_levelObjectProperties->setEnabled (true);
        int objIdx = 0;
        objIdx += ui.list_levelObjects->selectedItems ().first ()->text ().toInt();
        emit this->requestPropertiesForLevelObject (objIdx);
      } else {
        ui.group_levelObjectProperties->setEnabled (false);
        emit this->requestPropertiesForLevelObject (-1);
      }
}
void LevelObjectEditor::updateLevelObjectProperties (QVector3D translation, QVector3D rotation, QVector3D scale) {
  this->blockSignals (true);
  spanSpinboxes (translation, ui.spinbox_translateX, ui.spinbox_translateY, ui.spinbox_translateZ);
  spanSpinboxes(rotation, ui.spinbox_rotateX, ui.spinbox_rotateY, ui.spinbox_rotateZ);
  spanSpinboxes(scale, ui.spinbox_scaleX, ui.spinbox_scaleY, ui.spinbox_scaleZ);
  this->blockSignals (false);
}
void LevelObjectEditor::spanSpinboxes(QVector3D i_vec, QDoubleSpinBox* xbox, QDoubleSpinBox* ybox, QDoubleSpinBox* zbox) {
  qreal x_;
  qreal y_;
  qreal z_;
  x_ = i_vec.x ();
  y_ = i_vec.y ();
  z_ = i_vec.z ();
  xbox->setValue (x_);
  ybox->setValue(y_);
  zbox->setValue(z_);
}

void LevelObjectEditor::on_spinbox_translateX_valueChanged(double arg1)
{
  emit this->announcePropertiesChanged (mtranslation(), mrotation(), mscale());

}

void LevelObjectEditor::on_spinbox_translateY_valueChanged(double arg1)
{
    emit this->announcePropertiesChanged (mtranslation(), mrotation(), mscale());
}

void LevelObjectEditor::on_spinbox_translateZ_valueChanged(double arg1)
{
    emit this->announcePropertiesChanged (mtranslation(), mrotation(), mscale());
}

void LevelObjectEditor::on_spinbox_rotateY_valueChanged(double arg1)
{
  emit this->announcePropertiesChanged (mtranslation(), mrotation(), mscale());

}

void LevelObjectEditor::on_spinbox_rotateX_valueChanged(double arg1)
{
    emit this->announcePropertiesChanged (mtranslation(), mrotation(), mscale());
}

void LevelObjectEditor::on_spinbox_rotateZ_valueChanged(double arg1)
{
    emit this->announcePropertiesChanged (mtranslation(), mrotation(), mscale());
}

void LevelObjectEditor::on_spinbox_scaleX_valueChanged(double arg1)
{
    emit this->announcePropertiesChanged (mtranslation(), mrotation(), mscale());
}

void LevelObjectEditor::on_spinbox_scaleY_valueChanged(double arg1)
{
    emit this->announcePropertiesChanged (mtranslation(), mrotation(), mscale());
}

void LevelObjectEditor::on_spinbox_scaleZ_valueChanged(double arg1)
{
    emit this->announcePropertiesChanged (mtranslation(), mrotation(), mscale());
}
