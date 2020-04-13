/****************************************************************************
 **
 ** Copyright (C) 2020-2020 Philippe Steinmann.
 **
 ** This file is part of MdtApplication library.
 **
 ** MdtApplication is free software: you can redistribute it and/or modify
 ** it under the terms of the GNU Lesser General Public License as published by
 ** the Free Software Foundation, either version 3 of the License, or
 ** (at your option) any later version.
 **
 ** MdtApplication is distributed in the hope that it will be useful,
 ** but WITHOUT ANY WARRANTY; without even the implied warranty of
 ** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 ** GNU Lesser General Public License for more details.
 **
 ** You should have received a copy of the GNU Lesser General Public License
 ** along with MdtApplication. If not, see <http://www.gnu.org/licenses/>.
 **
 ****************************************************************************/
#ifndef MY_NON_QT_GUI_LIBRARY_CREATE_REPORT_ERROR_H
#define MY_NON_QT_GUI_LIBRARY_CREATE_REPORT_ERROR_H

#include "mynonqtguilibrary_export.h"
#include <QString>
#include <QByteArray>
#include <stdexcept>

namespace MyNonQtGuiLibrary{

  /*! \brief Create report error
   */
  class MYNONQTGUILIBRARY_EXPORT CreateReportError : public std::runtime_error
  {
   public:

    /*! \brief Create a report error
     */
    explicit CreateReportError(const QString & what)
     : runtime_error( what.toLocal8Bit().toStdString() )
    {
    }

  };

} // namespace MyNonQtGuiLibrary

#endif // #ifndef MY_NON_QT_GUI_LIBRARY_CREATE_REPORT_ERROR_H
