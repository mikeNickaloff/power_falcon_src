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

#ifndef FALCONMODELSHAREDLIB_GLOBAL_H
#define FALCONMODELSHAREDLIB_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(FALCONMODELSHAREDLIB_LIBRARY)
#  define MODEL_LIBRARY Q_DECL_EXPORT
#else
#  define MODEL_LIBRARY Q_DECL_IMPORT
#endif

#endif // FALCONMODELSHAREDLIB_GLOBAL_H
