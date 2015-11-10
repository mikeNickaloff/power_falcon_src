#ifndef MESH_H
#define MESH_H

#include <QObject>
#include <QVector>
#include <QVector3D>
#include <QtOpenGL/qgl.h>
#include <QHash>
#include <QtDebug>
#include "instruction.h"
static QVector<QVector3D> invert_grid(QVector<QVector3D> inp_grid, bool inv_x, bool inv_y, bool inv_z) {
 QVector<QVector3D> rv;
 foreach (QVector3D vec, inp_grid) {
     QVector3D new_vec; new_vec = vec;
     if (inv_x) { new_vec.setX(-vec.x()); }
     if (inv_y) { new_vec.setY(-vec.y()); }
     if (inv_z) { new_vec.setZ(-vec.z()); }
     rv << new_vec;
 }
 return rv;
}

static GLfloat grid6x6[6][6][3] =
{
    {
    { -2 , -2 , 0 },
    { -1 , -2 , 0 },
    { -0.5 , -2 , 0 },
    { 0.5 , -2 , 0 },
    { 1 , -2 , 0 },
    { 2 , -2 , 0 }},
    {
    { -2 , -1 , 0 },
    { -1 , -1 , 0 },
    { -0.5 , -1 , 0 },
    { 0.5 , -1 , 0 },
    { 1 , -1 , 0 },
    { 2 , -1 , 0 }},
    {
    { -2 , -0.5 , 0 },
    { -1 , -0.5 , 0 },
    { -0.5 , -0.5 , 0 },
    { 0.5 , -0.5 , 0 },
    { 1 , -0.5 , 0 },
    { 2 , -0.5 , 0 }},
    {
    { -2 , 0.5 , 0 },
    { -1 , 0.5 , 0 },
    { -0.5 , 0.5 , 0 },
    { 0.5 , 0.5 , 0 },
    { 1 , 0.5 , 0 },
    { 2 , 0.5 , 0 }},
    {
    { -2 , 1 , 0 },
    { -1 , 1 , 0 },
    { -0.5 , 1 , 0 },
    { 0.5 , 1 , 0 },
    { 1 , 1 , 0 },
    { 2 , 1 , 0 }},
    {
    { -2 , 2 , 0 },
    { -1 , 2 , 0 },
    { -0.5 , 2 , 0 },
    { 0.5 , 2 , 0 },
    { 1 , 2 , 0 },
    { 2 , 2 , 0 }}
};

#include "../falconmodelsharedlib_global.h"
class GLHandler;

class MODEL_LIBRARY Mesh : public Instruction
{
    Q_OBJECT
public:
    Mesh(QObject *parent = 0, GLHandler* i_glHandler = 0);
    GLHandler* glHandler;
    QVector<QVector3D> make3dVectorList(GLfloat* p_grid);
    QVector<QVector3D> m_vectorList;

     GLint gridSize;
     GLint uSize;
     GLint vSize;
     QHash<int, QVector3D> m_point_positions;
    // GLfloat gridx[6][6][3];
     QString xml(int keyFromParent);


signals:

public slots:
    void slot_set_grid(QVector<QVector3D> i_grid);
     void slot_assign_grid(QVector<QVector3D> input_grid);
     void slot_evaluateGrid();
     void slot_evaluateFill();
     void slot_setupMesh();
     void slot_draw_control_points(bool select_mode);
        void draw();
private:
       GLfloat *grid;
};

#endif // MESH_H
