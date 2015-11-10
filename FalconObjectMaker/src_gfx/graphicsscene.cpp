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

#include "gfx.h"
#include "glviewer.h"
GraphicsScene::GraphicsScene(QObject *parent) :
  QGraphicsScene(parent)
{
}
void GraphicsScene::drawBackground(QPainter *painter, const QRectF &rect) {
  QBrush brush(QColor(Qt::black), Qt::CrossPattern);
  painter->setBrush (brush);
  painter->fillRect (rect, brush);
  painter->beginNativePainting ();
  GLViewer viewer;
  viewer.makeCurrent ();
  //viewerspiral (true);
  painter->endNativePainting ();


}
