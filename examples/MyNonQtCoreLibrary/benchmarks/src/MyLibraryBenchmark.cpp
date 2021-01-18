/****************************************************************************
 **
 ** Copyright (C) 2019-2021 Philippe Steinmann.
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
#include "MyLibraryBenchmark.h"
#include "MyLibrary/MyLibrary_Api.h"

using namespace MyLibrary;

void MyLibraryBenchmark::sendCommandBenchmark()
{
  MyLibrary_Api lib;

  QBENCHMARK{
    QVERIFY( lib.sendCommand("CMD") == MyLibraryError::NoError );
  }
}

void MyLibraryBenchmark::valueBenchmark()
{
  MyLibrary_Api lib;

  lib.setValue("A");
  std::string result;
  QBENCHMARK{
    result = lib.value();
  }
  QCOMPARE( result, std::string("A") );
}

QTEST_GUILESS_MAIN(MyLibraryBenchmark)
