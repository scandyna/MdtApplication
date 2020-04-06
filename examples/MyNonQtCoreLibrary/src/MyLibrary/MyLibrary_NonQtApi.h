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
#ifndef MYLIBRARY_MYLIBRARY_NON_QT_API_H
#define MYLIBRARY_MYLIBRARY_NON_QT_API_H

#include "MyLibraryError.h"
#include "MyLibrary_NonQtApi_Worker.h"
#include "mynonqtcorelibrary_export.h"
#include "Mdt/CoreApplicationForNonQtUsage"
#include <string>
#include <mutex>

namespace MyLibrary{

  /*! \brief API of the MyLibrary example
   *
   * Exposes the functionalities that can be used
   * from a application that has its own event loop
   * (or maybe no event loop at all).
   *
   * This class gives access to MyLibrary_Api
   */
  class MYNONQTCORELIBRARY_EXPORT MyLibrary_NonQtApi : public QObject
  {
    Q_OBJECT

    using LockGuard = const std::lock_guard<std::mutex>;

   public:

    explicit MyLibrary_NonQtApi(QObject *parent = nullptr);

    /*! \brief Send a command
     *
     * \sa MyLibrary_Api::sendCommand()
     */
    MyLibraryError sendCommand(const std::string & command);

    /*! \brief Check if a response has been received
     */
    bool hasReceivedResponse() const
    {
      LockGuard lock(mMutex);
      return !mResponse.empty();;
    }

    /*! \brief Get response
     *
     * \sa MyLibrary_Api::response()
     */
    const std::string & response() const
    {
      LockGuard lock(mMutex);
      return mResponse;
    }

    /*! \brief Set value
     *
     * \sa MyLibrary_Api::setValue()
     */
    void setValue(const std::string & val)
    {
      invokeSetValue(val);
    }

    /*! \brief Get value
     *
     * \sa MyLibrary_Api::value()
     */
    std::string value() const
    {
      std::string val;
      invokeValue(val);
      return val;
    }

   public slots:

    void onResponseReceived(const std::string & response)
    {
      LockGuard lock(mMutex);
      mResponse = response;
    }

   signals:

    void invokeSendCommand(MyLibraryError & retVal, const std::string & command);

    void invokeSetValue(const std::string & val);
    void invokeValue(std::string & value) const;

   private:

    mutable std::mutex mMutex;
    std::string mResponse;
    Mdt::CoreApplicationForNonQtUsage<MyLibrary_NonQtApi_Worker> mApp;
  };

} // namespace MyLibrary{

#endif // #ifndef MYLIBRARY_MYLIBRARY_NON_QT_API_H
