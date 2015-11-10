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

#include "xmlbuilder.h"
#include <QtXml/QtXml>
XMLBuilder::XMLBuilder(QObject *parent, QString tagName) :
  QObject(parent), m_tag(tagName)
{
  this->m_document = QDomDocument();
  m_root = m_document.createElement (tagName);
  m_document.appendChild (m_root);
}
void XMLBuilder::insertElement(QString tagName, QString attribute, QString i_text){
  QDomElement elem = m_document.createElement (tagName.replace(" ", "_"));
  elem.setAttribute ("attr", attribute);
  m_root.appendChild (elem);
  QDomText textNode = m_document.createTextNode(i_text);
  elem.appendChild(textNode);

}
QString XMLBuilder::string () {
 QString rv = m_document.toString (1);

 return rv;

}
void XMLBuilder::setRootElementAttribute(QString attribute, QString value) {
  m_root.setAttribute (attribute, value);
}
