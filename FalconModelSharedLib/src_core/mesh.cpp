#include "mesh.h"
#include <QVector>
#include <QVector3D>
#include <QOpenGLFunctions_3_1>
#include "glut.h"
#include "../src_handlers/glhandler.h"
Mesh::Mesh(QObject *parent, GLHandler *i_glHandler) :
    Instruction(parent, i_glHandler), glHandler(i_glHandler)
{
    gridSize = 20;
    uSize = 6;
    vSize = 6;



    QList<qreal> xorder; xorder << -2.0 << -1.0 << -0.5 << 0.5 << 1.0 << 2.0;
    QList<qreal> yorder; yorder << xorder;
    QList<qreal> zorder;
    QListIterator<qreal> xi(xorder);
    QListIterator<qreal> yi(yorder);
    QVector<QVector3D> vlist;
    yi.toFront();
    int q; q = 0;
    while (yi.hasNext()) {
	qreal yval; yval = yi.next();
	xi.toFront();
	while (xi.hasNext()) {
	    qreal xval; xval = xi.next();

	    QVector3D rv; rv = QVector3D(xval, yval, 0.0);
	    vlist << rv;
	   // this->m_point_positions[q] = rv;
	    q++;
	}

    }


    this->m_vectorList << make3dVectorList(&grid6x6[0][0][0]);
   // this->m_vectorList << vlist;
   // QVectorIterator<QVector3D> o(this->m_vectorList);
  //  this->slot_assign_grid(m_vectorList);
    //gridx = grid6x6[0][0][0];
    grid = &grid6x6[0][0][0];
    //this->slot_assign_grid(m_vectorList);
    qDebug() << "Size of Mesh Database is "  << this->m_point_positions.keys().size();
    this->slot_setupMesh();
    this->slot_draw_control_points(false);
    this->slot_set_command ("mesh");

}
QVector<QVector3D> Mesh::make3dVectorList(GLfloat *p_grid) {
    QVector<QVector3D> grid_vector;
    int z; z = 0;
    bool found_end; found_end = false;
    int i; i = 0;
    //for (int i = 0; i < (4 * 4 * 3); i++) {
    while (found_end == false) {
	 QVector3D vec;

	 vec.setX(p_grid[i]); i++;
	 vec.setY(p_grid[i]); i++;
	 vec.setZ(p_grid[i]); i++;
	 this->m_point_positions[z] = vec;
	 z++;
	 if (i < 108) {
	     grid_vector << vec;
	 } else {
	     found_end = true;
	 }
	// gridlist << QString("%1").arg(grid[i]);
     }
    //qDebug() << "Made Grid Vector from GLfloat" << grid_vector;
  //  qDebug() << "Transferring grid containing" << qreal(grid_vector.size() * 3) << "float values to mesheditor" << p_grid[48];
    return grid_vector;
}
void Mesh::slot_set_grid(QVector<QVector3D> i_grid) {
   // qDebug() << "Setting Mesh Grid Value to" << i_grid;
    this->m_vectorList.clear();
    this->m_vectorList << i_grid;
    this->slot_assign_grid(this->m_vectorList);

}
void Mesh::slot_assign_grid(QVector<QVector3D> input_grid) {
    int q; q = 0;
    int g; g = 0;
    foreach (QVector3D vec, input_grid) {
	this->m_point_positions[g] = vec;
	g++;
	grid[q] = (GLfloat) vec.x();
	q++;
	grid[q] = (GLfloat) vec.y();
	q++;
	grid[q] = (GLfloat) vec.z();
	q++;


    }
}
void Mesh::slot_setupMesh()
{
  glEnable(GL_MAP2_VERTEX_3);
  glMapGrid2f(gridSize, 0.0, 1.0, gridSize, 0.0, 1.0);

}

void Mesh::slot_evaluateGrid()
{
  //  qDebug() << "Evaluating Map2_vertex3";

    GLfloat* i_grid;
    i_grid = this->grid;
//    glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, uSize, 0, 1, uSize * 3, vSize, grid);

    glColor3f(1.0, 1.0, 1.0);
    glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, uSize, 0, 1, uSize * 3, vSize, i_grid);

    glEvalMesh2(GL_LINE, 0, gridSize, 0, gridSize);
   // glDisable(GL_MAP2_VERTEX_3);

}
void Mesh::slot_evaluateFill() {
    //qDebug() << "Evaluating Map2_vertex3";
    GLfloat* i_grid;
    i_grid = this->grid;
//    glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, uSize, 0, 1, uSize * 3, vSize, grid);

  //  glColor3f(0.1, 0.7, 0.1);
    glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, uSize, 0, 1, uSize * 3, vSize, i_grid);



    GLfloat ambient[] = { 0.2, 0.2, 0.2, 1.0 };
       GLfloat position[] = { 0.0, 0.0, 2.0, 1.0 };
       GLfloat mat_diffuse[] = { 0.6, 0.6, 0.6, 1.0 };
       GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
       GLfloat mat_shininess[] = { 50.0 };

       glEnable(GL_LIGHTING);
       glEnable(GL_LIGHT0);

       glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
       glLightfv(GL_LIGHT0, GL_POSITION, position);
       glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_diffuse);
       glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular);
       glMaterialfv(GL_FRONT_AND_BACK,GL_SHININESS, mat_shininess);
       glShadeModel(GL_FLAT);

       glEnable(GL_DEPTH_TEST);



    //glBegin(GL_POLYGON);
    glEnable(GL_AUTO_NORMAL);

    glPushMatrix();
    glEvalMesh2(GL_FILL, 0, gridSize, 0, gridSize);
    glPopMatrix();



    //glEvalMesh2(GL_LINE, 0, gridSize, 0, gridSize);
}

void Mesh::slot_draw_control_points(bool select_mode) {
    glPointSize(10.0);
    glColor3f(0.8f, 0.8f, 0.1f);
      glBegin(GL_POINTS);
    if (this->m_point_positions.keys().size() > 0) {
	QHashIterator<int, QVector3D> o(this->m_point_positions);
	o.toFront();
	int i; i = 0;
	while (o.hasNext()) {
	    o.next();
	    int q; q = o.key();
	    if (select_mode)
		glPushName(q);
	    glVertex3f(o.value().x(), o.value().y(), o.value().z());
	    if (select_mode)
		glPopName();
	    int i2; int i3; i2= i + 1; i3 = i + 2;
	   // qDebug() << "Vertex3f is" << QVector3D(grid[i], grid[i2], grid[i3]);
	    i++; i++; i++;
	  //  qDebug() << "Vertex3D is" << o.value();

	}
    }
    glEnd();

}
void Mesh::draw() {
  glPushMatrix();
  this->slot_setupMesh ();
  this->slot_set_grid(this->m_point_positions.values().toVector());
  this->slot_evaluateGrid();
 // this->slot_evaluateFill();
  glPopMatrix();
}


QString Mesh::xml (int keyFromParent) {
  QString rv;
  rv.append(QString("<Mesh id=\"%1\" parentComponent=\"%2\">").arg(keyFromParent).arg(this->parentComponentId));
  return rv;
}
