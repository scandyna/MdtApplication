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
#include "MyLibrary_NonQtApi.h"

namespace MyLibrary{

MyLibrary_NonQtApi::MyLibrary_NonQtApi(QObject *parent)
 : QObject(parent)
{
  connect(this, &MyLibrary_NonQtApi::invokeSendCommand, &mApp.worker(), &MyLibrary_NonQtApi_Worker::sendCommand, Qt::BlockingQueuedConnection);
  connect(&mApp.worker().libraryApi(), &MyLibrary_Api::responseReceived, this, &MyLibrary_NonQtApi::onResponseReceived, Qt::DirectConnection);

  connect(this, &MyLibrary_NonQtApi::invokeSetValue, &mApp.worker(), &MyLibrary_NonQtApi_Worker::setValue, Qt::BlockingQueuedConnection);
  connect(this, &MyLibrary_NonQtApi::invokeValue, &mApp.worker(), &MyLibrary_NonQtApi_Worker::value, Qt::BlockingQueuedConnection);
}

MyLibraryError MyLibrary_NonQtApi::sendCommand(const std::string & command)
{
  {
    LockGuard lock(mMutex);
    mResponse.clear();
  }
  MyLibraryError retVal;
  invokeSendCommand(retVal, command);
  return retVal;
}

} // namespace MyLibrary{
