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

#ifndef GLHANDLER_H
#define GLHANDLER_H

#include <QObject>
#include <windows.h>
#include "glut.h"
#include <QApplication>
//#include <GL/glsmap.h>
#include "../falconmodelsharedlib_global.h"

class MODEL_LIBRARY  GLHandler : public QObject
{
    Q_OBJECT
public:
     GLHandler(QObject *parent = 0);

signals:

public slots:
      void slot_none();
      void slot_pushmatrix() { glPushMatrix(); }
      void slot_popmatrix() { glPopMatrix(); }
      void slot_loadIdentity() { glLoadIdentity(); }
      void slot_color(qreal r, qreal g, qreal b);
      void slot_translatef(qreal x, qreal y, qreal z);
      void slot_rotatef(qreal x, qreal y, qreal z);
      void slot_wirecube(qreal size) { glutWireCube((GLdouble)size); }
      void slot_solidcube(qreal size) { glutSolidCube((GLdouble)size); }
      void slot_wire_dodecahedron() { glutWireDodecahedron(); }
      void slot_solid_dodecahedron() { glutSolidDodecahedron(); }
      void slot_solidsphere(qreal radius, qreal slices, qreal stacks) { glutSolidSphere(radius, slices, stacks); }
      void slot_wiresphere(qreal radius, qreal slices, qreal stacks);
      void slot_solidtorus(qreal iRad, qreal oRad, qreal sides, qreal rings) { glutSolidTorus(iRad, oRad, sides, rings); }
      void slot_wiretorus(qreal iRad, qreal oRad, qreal sides, qreal rings) { glutWireTorus(iRad, oRad, sides, rings); }
      void slot_solidcone(qreal base, qreal height, qreal slices, qreal stacks) { glutSolidCone(base, height, (GLint)slices,(GLint) stacks); }
      void slot_wirecone(qreal base, qreal height, qreal slices, qreal stacks) { glutWireCone(base, height, slices, stacks); }
      void slot_scalef(qreal x_pct, qreal y_pct, qreal z_pct) { glScalef(x_pct, y_pct, z_pct); }
      void slot_begin_polygon();
      void slot_insert_vertex(qreal x, qreal y, qreal z);
      void slot_end_polygon();








};

#endif // GLHANDLER_H

