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
#include "MyLibrary_Api.h"
#include <QTimer>

namespace MyLibrary{

MyLibraryError MyLibrary_Api::sendCommand(const std::string & command)
{
  if( command != "CMD" ){
    return MyLibraryError::UnknownCommand;
  }
  QTimer::singleShot(10, this, &MyLibrary_Api::onResponseReceived);

  return MyLibraryError::NoError;
}

void MyLibrary_Api::setValue(const std::string & val)
{
  mValue = val;
}

void MyLibrary_Api::onResponseReceived()
{
  emit responseReceived("RESPONSE");
}

} // namespace MyLibrary{
