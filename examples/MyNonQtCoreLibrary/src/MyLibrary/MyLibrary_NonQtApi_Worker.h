/****************************************************************************
 **
 ** Copyright (C) 2019-2020 Philippe Steinmann.
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
#ifndef MYLIBRARY_MYLIBRARY_NON_QT_API_WORKER_H
#define MYLIBRARY_MYLIBRARY_NON_QT_API_WORKER_H

#include "MyLibrary_Api.h"
#include "MyLibraryError.h"
#include "mynonqtcorelibrary_export.h"
#include <QObject>
#include <string>

namespace MyLibrary{

  /*! \brief Worker for MyLibrary_NonQtApi
   *
   * The main goal of this worker is to call
   * the methods in the thread context of the application business logic.
   * This is done thanks to the signals and slot mechanism.
   *
   * Because signals and slots does not support return values,
   * they are mapped as first argument of the slots.
   *
   * \sa MyLibrary_NonQtApi
   */
  class MYNONQTCORELIBRARY_EXPORT MyLibrary_NonQtApi_Worker : public QObject
  {
    Q_OBJECT

   public:

    explicit MyLibrary_NonQtApi_Worker(QObject *parent = nullptr);

    MyLibrary_Api & libraryApi()
    {
      return mLib;
    }

   public slots:

    void sendCommand(MyLibraryError & retVal, const std::string & command);

    void setValue(const std::string & val)
    {
      mLib.setValue(val);
    }

    void value(std::string & val)
    {
      val = mLib.value();
    }

   private:

    MyLibrary_Api mLib;
  };

} // namespace MyLibrary{

#endif // #ifndef MYLIBRARY_MYLIBRARY_NON_QT_API_WORKER_H
