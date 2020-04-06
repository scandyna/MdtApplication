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
#include "MyLibraryTest.h"
#include "MyLibrary/MyLibrary_Api.h"

using namespace MyLibrary;

void MyLibraryTest::sendCommandTest()
{
  MyLibrary_Api lib;

  QVERIFY( lib.sendCommand("CMD") == MyLibraryError::NoError );
}

void MyLibraryTest::valueTest()
{
  MyLibrary_Api lib;

  lib.setValue("A");
  QCOMPARE( lib.value(), std::string("A") );
}

QTEST_GUILESS_MAIN(MyLibraryTest)
