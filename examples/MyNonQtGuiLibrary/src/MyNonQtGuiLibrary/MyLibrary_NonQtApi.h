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
#ifndef MY_NON_QT_GUI_LIBRARY_MY_LIBRARY_NON_QT_API_H
#define MY_NON_QT_GUI_LIBRARY_MY_LIBRARY_NON_QT_API_H

#include "ReportInformations.h"
#include "CreateReportError.h"
#include "MyLibrary_NonQtApi_Worker.h"
#include "Mdt/GuiApplicationForNonQtUsage"
#include "mynonqtguilibrary_export.h"
#include <QObject>
#include <QString>
#include <exception>
#include <stdexcept>

namespace MyNonQtGuiLibrary{

  /*! \brief Make MyLibrary_Api usable from a non Qt application
   */
  class MYNONQTGUILIBRARY_EXPORT MyLibrary_NonQtApi : public QObject
  {
    Q_OBJECT

   public:

    /*! \brief Constuctor
     *
     * Will also make signal and slot connections with the worker
     */
    explicit MyLibrary_NonQtApi(QObject *parent = nullptr);

    /*! \brief Create a report
     *
     * \sa MyLibrary_Api::createReport()
     */
    void createReport(const ReportInformations & info, const QString & reportDirectoryPath);

    /*! \brief Get the title of the report
     *
     * \sa MyLibrary_Api::reportTitle()
     */
    QString reportTitle() const
    {
      QString title;
      invokeReportTitle(title);
      return title;
    }

   signals:

    /*! \brief Call to invoke MyLibrary_Api::createReport() in its thread context
     */
    void invokeCreateReport(std::exception_ptr & eptr, const ReportInformations & info, const QString & reportDirectoryPath);

    /*! \brief Call to invoke MyLibrary_Api::reportTitle() in its thread context
     */
    void invokeReportTitle(QString & title) const;

   private:

    Mdt::GuiApplicationForNonQtUsage<MyLibrary_NonQtApi_Worker> mApp;
  };

} // namespace MyNonQtGuiLibrary

#endif // #ifndef MY_NON_QT_GUI_LIBRARY_MY_LIBRARY_NON_QT_API_H
