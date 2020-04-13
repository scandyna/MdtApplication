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
#ifndef MY_NON_QT_GUI_LIBRARY_MY_LIBRARY_NON_QT_API_WORKER_H
#define MY_NON_QT_GUI_LIBRARY_MY_LIBRARY_NON_QT_API_WORKER_H

#include "MyLibrary_Api.h"
#include "mynonqtguilibrary_export.h"
#include <QObject>
#include <QString>

namespace MyNonQtGuiLibrary{

  /*! \brief Worker for MyNonQtGuiLibrary::MyLibrary_NonQtApi
   *
   * The main goal of this worker is to call
   * the methods in the thread context of the application business logic.
   * This is done thanks to the signals and slot mechanism.
   *
   * Because signals and slots does not support return values,
   * they are mapped as first argument of the slots.
   *
   * \sa MyNonQtGuiLibrary::MyLibrary_NonQtApi
   */
  class MYNONQTGUILIBRARY_EXPORT MyLibrary_NonQtApi_Worker : public QObject
  {
    Q_OBJECT

   public slots:

    /*! \brief Maps MyLibrary_Api::createReport() to a slot signature
     *
     * \todo Exceptions !
     */
    void createReport(const ReportInformations & info)
    {
      mLib.createReport(info);
    }

    /*! \brief Maps MyLibrary_Api::reportTitle() to a slot signature
     */
    void reportTitle(QString & title)
    {
      title = mLib.reportTitle();
    }

   private:

    MyLibrary_Api mLib;
  };

} // namespace MyNonQtGuiLibrary

#endif // #ifndef MY_NON_QT_GUI_LIBRARY_MY_LIBRARY_NON_QT_API_WORKER_H
