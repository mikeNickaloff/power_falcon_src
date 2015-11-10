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

#ifndef LASERBEAM_H
#define LASERBEAM_H
#include <QObject>
#include "../falconmodelsharedlib_global.h"
#include <QString>
#include "gameobject.h"
#include <QDir>
#include <QCoreApplication>
class MODEL_LIBRARY GLHandler;
class MODEL_LIBRARY Model;
class MODEL_LIBRARY Component;
class MainWindow;
class LaserBeam : public GameObject
{
  Q_OBJECT
public:
  Q_PROPERTY(QString laserType READ laserType WRITE setLaserType)
  LaserBeam(QObject *parent = 0, GLHandler* i_handler = 0,  MainWindow* i_main = 0, QString laserTypeName = "laserbeam", int i_displayListIndex = 0, QString laserFilePath = qApp->applicationDirPath ().append (QDir::separator ()).append("models").append(QDir::separator ()).append("laserbeam.pfmdl"));
  QString laserType() { return _laserType; }



signals:

public slots:
void setLaserType(QString i_laserTypeName) { _laserType = i_laserTypeName; }
void checkForPendingXMLdata();
void initPath(QPoint pt);

private:
  QString _laserType;
  GLHandler* _glHandler;
  QString pendingXMLdata;

};

#endif // LASERBEAM_H
