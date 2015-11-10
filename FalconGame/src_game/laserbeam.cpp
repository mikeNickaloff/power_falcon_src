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

#include "laserbeam.h"
#include "gameobject.h"
#include "src_core/model.h"
#include "src_core/component.h"
#include <QDomDocument>
#include <QFile>
#include "../mainwindow.h"
#include "../src_gfx/glviewer.h"


LaserBeam::LaserBeam(QObject *parent, GLHandler* i_handler, MainWindow* i_main, QString laserTypeName, int i_displayListIndex, QString laserFilePath) :
  GameObject(parent, i_main, i_handler, i_displayListIndex )
{
  this->setLaserType (laserTypeName);

  QFile file(laserFilePath);
  if (file.open (QIODevice::ReadOnly)) {
      QDomDocument doc;
      doc.setContent (file.readAll (), false);
      this->pendingXMLdata = doc.toString();

    }
  file.close ();
  QTimer::singleShot (1, this, SLOT(checkForPendingXMLdata()));


}
void LaserBeam::checkForPendingXMLdata () {
  if (this->pendingXMLdata.length () > 0) {
      Model* model_;
      model_ = this->model();
      model_->loadXML (this->pendingXMLdata);


      this->pendingXMLdata = "";
      foreach (Component* component, model_->findComponentsExcept (0)) {
          component->setSelected (true);


        }
      model_->getComponentById (0)->setSelected (true);

        emit this->displayListChanged (this->displayListIndex ());
    }
}
void LaserBeam::initPath (QPoint pt) {
    Camera* cam = new Camera();
  m_main->m_viewer->camera()->convertClickToLine(pt, orig, dir);
  bool found;
  selectedPoint = m_main->m_viewer->camera()->pointUnderPixel(pt, found);
  selectedPoint -= 0.01f*dir;
  float maxDistance = -5000;
  float distanceStep = -750;
      cam->setPosition(m_main->m_viewer->camera()->position());
      cam->setOrientation (m_main->m_viewer->camera()->orientation ());
      cam->setViewDirection (m_main->m_viewer->camera()->viewDirection ());
        cam->lookAt(selectedPoint);
           cam->setPosition(m_main->m_viewer->camera()->position());
           kfi_->deletePath ();
      Vec laserDisp = Vec(0.0, 0.0, 0.0);
      while (laserDisp.z > maxDistance) {
          laserDisp.z += distanceStep;
           cam->frame ()->translate ( cam->frame()->localInverseTransformOf(laserDisp));
              kfi_->addKeyFrame (Frame(cam->frame()->position(), cam->orientation ()), 0.35 * (laserDisp.z / distanceStep));


          }
      kfi_->setInterpolationSpeed (3.0);
      kfi_->startInterpolation (35);
      this->connect (kfi_, SIGNAL(endReached()), this, SLOT(endInterpolation()));
              //         Vec midPt = selectedPoint;


//         midPt = orig;

//             midPt.x = (orig.x + selectedPoint.x) / 2.0;
//             midPt.y =  (orig.y + selectedPoint.y) / 2.0;
//             midPt.z =  (orig.z + selectedPoint.z) / 2.0;

//             cam->setPosition (midPt);
//             kfi_->addKeyFrame (Frame(cam->frame()->position(), cam->orientation ()), 0.55f);

 //    cam->frame ()->translate ( cam->frame()->localInverseTransformOf(laserDisp));



    //  kfi_->addKeyFrame (Frame(cam->frame()->position(), cam->orientation ()), 0.85f);
    //  cam->frame ()->translate ( cam->frame()->localInverseTransformOf(laserDisp * 2));
   //   kfi_->addKeyFrame (Frame(cam->frame()->position(), cam->orientation ()), 1.55f);



     // resetKfi = false;
   // }

}
