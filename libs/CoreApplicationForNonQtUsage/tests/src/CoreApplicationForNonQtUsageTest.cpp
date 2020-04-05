/****************************************************************************
 **
 ** Copyright (C) 2019-2020 Philippe Steinmann.
 **
 ** This file is part of QCoreApplicationForNonQtUsage library.
 **
 ** QCoreApplicationForNonQtUsage is free software: you can redistribute it and/or modify
 ** it under the terms of the GNU Lesser General Public License as published by
 ** the Free Software Foundation, either version 3 of the License, or
 ** (at your option) any later version.
 **
 ** QCoreApplicationForNonQtUsage is distributed in the hope that it will be useful,
 ** but WITHOUT ANY WARRANTY; without even the implied warranty of
 ** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 ** GNU Lesser General Public License for more details.
 **
 ** You should have received a copy of the GNU Lesser General Public License
 ** along with QCoreApplicationForNonQtUsage. If not, see <http://www.gnu.org/licenses/>.
 **
 ****************************************************************************/
#include "CoreApplicationForNonQtUsageTest.h"
#include "Mdt/CoreApplicationForNonQtUsage.h"
#include <catch2/catch.hpp>
#include <QLatin1String>

class BasicToyWorker
{
};

TEST_CASE("ConstructDestructTest")
{
  Mdt::CoreApplicationForNonQtUsage<BasicToyWorker> app;
}

TEST_CASE("ConstructDestructMultipleTimeTest")
{
  for(int i = 0; i < 5; ++i){
    Mdt::CoreApplicationForNonQtUsage<BasicToyWorker> app;
  }
}


TEST_CASE("Basic test")
{
  MyPlugin plugin;

  plugin.setValue(6);
  REQUIRE( plugin.value() == 6 );

  REQUIRE( plugin.data().id() == 0 );
  REQUIRE( plugin.readData(QLatin1String("a")) );
  REQUIRE( plugin.data().id() != 0 );
  REQUIRE( plugin.data().name().size() > 0 );
}
