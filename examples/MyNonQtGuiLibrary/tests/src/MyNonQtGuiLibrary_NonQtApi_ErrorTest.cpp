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
#include "catch2/catch.hpp"
#include "MyNonQtGuiLibrary/MyLibrary_NonQtApi.h"
#include <QLatin1String>
#include <QTemporaryDir>

using namespace MyNonQtGuiLibrary;

TEST_CASE("createReport_except")
{
  MyLibrary_NonQtApi lib;

  ReportInformations reportInformations;
  reportInformations.setTitle(QLatin1String("Test title"));

  REQUIRE_THROWS( lib.createReport(reportInformations, QLatin1String("/Some/Probably/I/Hope/Non/Existing/Path")) );
}
