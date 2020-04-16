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
#include "MyLibrary_NonQtApi.h"

namespace MyNonQtGuiLibrary{

MyLibrary_NonQtApi::MyLibrary_NonQtApi(QObject *parent)
 : QObject(parent),
   mApp({"mynonqtguiapp","-platform","minimal"})
{
  connect(this, &MyLibrary_NonQtApi::invokeCreateReport, &mApp.worker(), &MyLibrary_NonQtApi_Worker::createReport, Qt::BlockingQueuedConnection);
  connect(this, &MyLibrary_NonQtApi::invokeReportTitle, &mApp.worker(), &MyLibrary_NonQtApi_Worker::reportTitle, Qt::BlockingQueuedConnection);
}

void MyLibrary_NonQtApi::createReport(const ReportInformations & info, const QString & reportDirectoryPath)
{
  std::exception_ptr eptr;

  invokeCreateReport(eptr, info, reportDirectoryPath);
  if(eptr){
    std::rethrow_exception(eptr);
  }
}

} // namespace MyNonQtGuiLibrary
