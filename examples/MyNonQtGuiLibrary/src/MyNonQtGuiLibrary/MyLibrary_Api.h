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
#ifndef MY_NON_QT_GUI_LIBRARY_MY_LIBRARY_API_H
#define MY_NON_QT_GUI_LIBRARY_MY_LIBRARY_API_H

#include "ReportInformations.h"
#include "CreateReportError.h"
#include "mynonqtguilibrary_export.h"
#include <QObject>
#include <QTextDocument>
#include <QString>

namespace MyNonQtGuiLibrary{

  /*! \brief Some API to the business logic
   */
  class MYNONQTGUILIBRARY_EXPORT MyLibrary_Api : public QObject
  {
    Q_OBJECT

   public:

    /*! \brief Create a report
     *
     * \exception CreateReportError
     */
    void createReport(const ReportInformations & info, const QString & reportDirectoryPath);

    /*! \brief Get the title of the report
     */
    QString reportTitle() const;

   private:

    QTextDocument mDocument;
  };

} // namespace MyNonQtGuiLibrary

#endif // #ifndef MY_NON_QT_GUI_LIBRARY_MY_LIBRARY_API_H
