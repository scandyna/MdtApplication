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
#include <catch2/catch.hpp>
#include "MyLibrary/MyLibrary_NonQtApi.h"
#include <chrono>
#include <thread>

using namespace MyLibrary;

TEST_CASE("sendCommandTest")
{
  using namespace std::chrono_literals;

  MyLibrary_NonQtApi lib;

  REQUIRE( lib.sendCommand("CMD") == MyLibraryError::NoError );

  while( !lib.hasReceivedResponse() ){
    std::this_thread::sleep_for(1ms);
  }
  REQUIRE( lib.response() == "RESPONSE" );
}

TEST_CASE("valueTest")
{
  MyLibrary_NonQtApi lib;

  lib.setValue("A");
  REQUIRE( lib.value() == std::string("A") );
}
