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
#ifndef MY_NON_QT_GUI_LIBRARY_REPORT_INFORMATIONS_H
#define MY_NON_QT_GUI_LIBRARY_REPORT_INFORMATIONS_H

#include "mynonqtguilibrary_export.h"
#include <QDate>
#include <QString>

namespace MyNonQtGuiLibrary{

  /*! \brief Holds informations to generate a report
   */
  class MYNONQTGUILIBRARY_EXPORT ReportInformations
  {
   public:

    /*! \brief Get this report date
     */
    QDate date() const
    {
      return mDate;
    }

    /*! \brief Set the title
     */
    void setTitle(const QString & title)
    {
      mTitle = title;
    }

    /*! \brief Get the title
     */
    QString title() const
    {
      return mTitle;
    }

   private:

    QDate mDate = QDate::currentDate();
    QString mTitle;
  };

} // namespace MyNonQtGuiLibrary

#endif // #ifndef MY_NON_QT_GUI_LIBRARY_REPORT_INFORMATIONS_H
