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
#ifndef MYLIBRARY_MYLIBRARY_API_H
#define MYLIBRARY_MYLIBRARY_API_H

/// Try CI

#include "MyLibraryError.h"
#include "mynonqtcorelibrary_export.h"
#include <QObject>
#include <string>

namespace MyLibrary{

  /*! \brief API to the business logic
   */
  class MYNONQTCORELIBRARY_EXPORT MyLibrary_Api : public QObject
  {
    Q_OBJECT

   public:

    /*! \brief Send a command
     */
    MyLibraryError sendCommand(const std::string & command);

    /*! \brief Set value
     */
    void setValue(const std::string & val);

    /*! \brief Get value
     */
    const std::string & value() const
    {
      return mValue;
    }

   signals:

    void responseReceived(const std::string & response);

   private slots:

    void onResponseReceived();

   private:

    std::string mValue;
  };

} // namespace MyLibrary{

#endif // #ifndef MYLIBRARY_MYLIBRARY_API_H
