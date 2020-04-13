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
#include "MyNonQtGuiLibrary_Benchmark.h"
#include "MyNonQtGuiLibrary/MyLibrary_Api.h"
#include "Mdt/Impl/CommandLineArguments.h"
#include <QGuiApplication>
#include <QLatin1String>

using namespace MyNonQtGuiLibrary;

void MyNonQtGuiLibraryBenchmark::createReportBenchmark()
{
  MyLibrary_Api lib;

  ReportInformations reportInformations;
  reportInformations.setTitle(QLatin1String("Test title"));

  QBENCHMARK{
    lib.createReport(reportInformations);
  }

  QCOMPARE( lib.reportTitle(), QLatin1String("Test title") );
}

void MyNonQtGuiLibraryBenchmark::reportTitleBenchmark()
{
  MyLibrary_Api lib;

  ReportInformations reportInformations;
  reportInformations.setTitle(QLatin1String("Test title"));

  lib.createReport(reportInformations);

  QString reportTitle;
  QBENCHMARK{
    reportTitle = lib.reportTitle();
  }
  QCOMPARE( reportTitle, QLatin1String("Test title") );
}


int main(int argc, char **argv)
{
  Mdt::Impl::CommandLineArguments args({"MyNonQtGuiLibraryBenchmark","-platform","minimal"});
  QGuiApplication app(args.argumentCountRef(), args.argumentVector());
  MyNonQtGuiLibraryBenchmark benchmark;

  return QTest::qExec(&benchmark, argc, argv);
}
