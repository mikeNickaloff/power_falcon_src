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

#ifndef XMLBUILDER_H
#define XMLBUILDER_H

#include <QObject>
#include <QStringList>
#include <QtXml/QtXml>
class XMLBuilder : public QObject
{
  Q_OBJECT
public:
   XMLBuilder(QObject *parent = 0, QString tagName = QString());
  QDomDocument m_document;
  QDomElement m_root;
  QString m_tag;
  QString string();
signals:

public slots:
  void insertElement(QString tagName, QString attribute, QString i_text);
  void setRootElementAttribute(QString attribute, QString value);
};

#endif // XMLBUILDER_H
