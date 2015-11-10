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
#include "falconmodelsharedlib.h"
#include "gameobject.h"
#include "src_handlers/glhandler.h"
#include "src_core/model.h"
#include "../src_gfx/glviewer.h"
#include "../mainwindow.h"
#include <QtDebug>
GameObject::GameObject(QObject *parent, MainWindow* i_main, GLHandler *i_handler, int i_displayListIndex, QString modelData) :
  QObject(parent), _glHandler(i_handler), _displayListIndex(i_displayListIndex), m_main(i_main)
{
   kfi_ = new KeyFrameInterpolator(new Frame());
  _model = new Model(this, i_handler);
  _model->loadXML (modelData);
}
void GameObject::draw () {

  this->model ()->draw ();

}
void GameObject::drawFromDisplayList() {
  glPushMatrix();
  glMultMatrixd(kfi_->frame()->matrix());
  glPushMatrix();
  glCallList(displayListIndex());
  glPopMatrix();
  glPopMatrix();
}
void GameObject::endInterpolation () {
  emit this->interpolationComplete (this->displayListIndex ());
}
