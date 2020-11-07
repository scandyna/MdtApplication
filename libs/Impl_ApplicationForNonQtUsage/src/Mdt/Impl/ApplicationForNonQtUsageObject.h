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
#ifndef MDT_APPLICATION_FOR_NON_QT_USAGE_IMPL_APPLICATION_FOR_NON_QT_USAGE_OBJECT_H
#define MDT_APPLICATION_FOR_NON_QT_USAGE_IMPL_APPLICATION_FOR_NON_QT_USAGE_OBJECT_H

// #include "mdt_impl_applicationfornonqtusage_export.h"
#include <QObject>
#include <QCoreApplication>

namespace Mdt{ namespace Impl{

  class /*MDT_IMPL_APPLICATIONFORNONQTUSAGE_EXPORT*/ ApplicationForNonQtUsageObject : public QObject
  {
    Q_OBJECT

   public:

    void registerApplication(QCoreApplication *app)
    {
      Q_ASSERT(app != nullptr);

      connect(this, &Mdt::Impl::ApplicationForNonQtUsageObject::invokeQuit, app, &QCoreApplication::quit, Qt::QueuedConnection);
    }

  Q_SIGNALS:

    void invokeQuit();
  };

}} // namespace Mdt{ namespace Impl{

#endif // #ifndef MDT_APPLICATION_FOR_NON_QT_USAGE_IMPL_APPLICATION_FOR_NON_QT_USAGE_OBJECT_H
