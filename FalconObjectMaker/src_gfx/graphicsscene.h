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

#ifndef GRAPHICSSCENE_H
#define GRAPHICSSCENE_H

#include <QGraphicsScene>
#include "../GL/glut.h"

class GraphicsScene : public QGraphicsScene
{
  Q_OBJECT
public:
  GraphicsScene(QObject *parent = 0);

signals:

public slots:
void drawBackground(QPainter *painter, const QRectF &rect);
};

#endif // GRAPHICSSCENE_H
