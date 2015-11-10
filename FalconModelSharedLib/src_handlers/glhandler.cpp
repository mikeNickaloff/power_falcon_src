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

#include "glhandler.h"

GLHandler::GLHandler(QObject *parent) :
    QObject(parent)
{
}
void GLHandler::slot_translatef(qreal x, qreal y, qreal z) {
    glTranslatef(x, y, z);
}
void GLHandler::slot_none() {

}
void GLHandler::slot_rotatef(qreal x, qreal y, qreal z) {
    glRotatef(x, 1.0f, 0, 0);
    glRotatef(y, 0, 1.0f, 0);
    glRotatef(z, 0, 0, 1.0f);
}
void GLHandler::slot_wiresphere(qreal radius, qreal slices, qreal stacks) {
    glutWireSphere(radius, (int) slices, (int) stacks);

}
void GLHandler::slot_color(qreal r, qreal g, qreal b) {
    glColor3f(r, g, b);

}
void GLHandler::slot_begin_polygon() {
    glBegin(GL_POLYGON);
}
void GLHandler::slot_insert_vertex(qreal x, qreal y, qreal z) {
    glVertex3f(x, y, z);
}
void GLHandler::slot_end_polygon() {
    glEnd();

}
