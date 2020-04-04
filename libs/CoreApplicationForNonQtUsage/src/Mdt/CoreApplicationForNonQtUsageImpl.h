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
#ifndef MDT_CORE_APPLICATION_FOR_NON_QT_USAGE_IMPL_H
#define MDT_CORE_APPLICATION_FOR_NON_QT_USAGE_IMPL_H

#include "mdt_coreapplicationfornonqtusage_export.h"
#include <QObject>
#include <QCoreApplication>

class MDT_COREAPPLICATIONFORNONQTUSAGE_EXPORT CoreApplicationForNonQtUsageImpl : public QObject
{
 Q_OBJECT

 public:

  void registerApplication(QCoreApplication *app)
  {
    Q_ASSERT(app != nullptr);

    connect(this, &Mdt::CoreApplicationForNonQtUsageImpl::invokeQuit, app, &QCoreApplication::quit, Qt::QueuedConnection);
  }

 Q_SIGNALS:

  void invokeQuit();
};

#endif // #ifndef MDT_CORE_APPLICATION_FOR_NON_QT_USAGE_IMPL_H
