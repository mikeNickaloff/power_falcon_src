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

#include "mainwindow.h"
#include "src_gfx/gfx.h"
#include <QApplication>
#include <QGraphicsScene>
#include <QTextEdit>
#include <QPushButton>
#include <QGraphicsLayout>
#include <QGraphicsLinearLayout>
#include <QGraphicsWidget>
#include <QGraphicsItem>
#include <QGraphicsProxyWidget>
#include <QGLViewer/qglviewer.h>
#include "src_gfx/glviewer.h"
int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  MainWindow w;

  w.show ();
  w.resize (250, 250);
  //GraphicsScene scene;
  //scene.setSceneRect (50,-50, 800, 800);
  // QGraphicsTextItem* textObj = scene.addText("GraphicsView rotated clockwise");
//  QGraphicsEllipseItem* ellipseObj = scene.addEllipse (42,62, 200, 200, QPen(QColor(Qt::red)), QBrush(Qt::green, Qt::DiagCrossPattern));

  //QGraphicsProxyWidget *textEdit = scene.addWidget(new QTextEdit);
  // QGraphicsProxyWidget *pushButton = scene.addWidget(new QPushButton);
  //QGraphicsProxyWidget *mainWindow = scene.addWidget (w);


  // QGraphicsProxyWidget* glViewer = scene.addWidget (qobject_cast<QWidget*>(m_viewer));





  //  scene.addWidget (glWidget);

  //  glWidget->setGeometry (0, 0, 500, 500);
  //  glWidget->show ();
  //  glWidget->update ();
  // m_viewer->show ();
  //QGraphicsLinearLayout *layout = new QGraphicsLinearLayout;
  //layout->addItem(textEdit);
  // layout->addItem(pushButton);
  //  glViewer->resize(500, 500);
  //  glViewer->setPos(scene.sceneRect ().topLeft ());
  //  scene.addWidget (m_viewer);
 // layout->addItem(mainWindow);


  //layout->setAlignment (pushButton, Qt::AlignRight);
  //layout->setAlignment (mainWindow, Qt::AlignBottom);
//  QGraphicsWidget *form = new QGraphicsWidget;
//  form->setLayout(layout);
//  form->resize(200, 600);
//  form->setPos(scene.sceneRect ().topRight ().x () - 200, scene.sceneRect ().topLeft ().y ());
//  scene.addItem(form);



 // GraphicsView view;

//  QGLFormat glf = QGLFormat::defaultFormat();
//  glf.setSamples(8);
//  QGLFormat::setDefaultFormat(glf);
//  GLViewer* glWidget = new GLViewer;
//  glWidget->setFormat (glf);
//  glWidget->resize(500, 500);
//  glWidget->makeCurrent();
//view.setViewport (glWidget);
 // view.setViewportUpdateMode( QGraphicsView::FullViewportUpdate );
  //   view.setScene( (scene = new Scene(this)) );
//  view.setAlignment(Qt::AlignLeft | Qt::AlignTop);
//  view.setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
//  view.setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
//  view.setRenderHint(QPainter::HighQualityAntialiasing, true);
//  view.setRenderHint(QPainter::SmoothPixmapTransform, true);
//glWidget->showNormal ();

//  view.resize(820, 668);

//  view.setScene (&scene);
  //  view.rotate (90);

  // m_viewer->setParent(&view);
  //w->setCentralWidget (m_viewer);
  //glViewer->resize (400, 400);
  // glWidget->show ();
  // m_viewer->showEntireScene ();

 // view.show ();
 // scene.invalidate (scene.sceneRect (), GraphicsScene::BackgroundLayer);


  return a.exec();
}
