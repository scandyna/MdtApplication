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
#ifndef MDT_APPLICATION_FOR_NON_QT_USAGE_IMPL_APPLICATION_FOR_NON_QT_USAGE_H
#define MDT_APPLICATION_FOR_NON_QT_USAGE_IMPL_APPLICATION_FOR_NON_QT_USAGE_H

#include "ApplicationForNonQtUsageObject.h"
#include <thread>
#include <atomic>
#include <memory>
#include <chrono>
#include <mutex>
#include <condition_variable>

namespace Mdt{ namespace Impl{

  /*! \internal
   */
  template<typename Worker, typename QApp>
  class ApplicationForNonQtUsage
  {
   public:

    explicit ApplicationForNonQtUsage()
    : mWorker(nullptr),
      mThread(run, this)
    {
      std::unique_lock<std::mutex> lock(mMutex);
      mInitDoneCondition.wait(lock, [this](){return mInitDone;});
    }

    ~ApplicationForNonQtUsage()
    {
      mObject.invokeQuit();
      mThread.join();
    }

    Worker & worker()
    {
      return *mWorker;
    }

    const Worker & worker() const
    {
      return *mWorker;
    }

  private:

    static void run(ApplicationForNonQtUsage *instance)
    {
      std::unique_ptr<QApp> app;

      {
        std::lock_guard<std::mutex> lock(instance->mMutex);

        int argc = 1;
        const char* argv[2] = { "dummy", 0 };
        app.reset( new QApp(argc, const_cast<char**>(argv)) );

        instance->mWorker = new Worker;
        instance->mObject.registerApplication(app.get());
        instance->mInitDone = true;
      }
      instance->mInitDoneCondition.notify_one();

      app->exec();

      delete instance->mWorker;
    }

    bool mInitDone = false;
    std::mutex mMutex;
    std::condition_variable mInitDoneCondition;
    ApplicationForNonQtUsageObject mObject;
    std::atomic<Worker*> mWorker;
    std::thread mThread;
  };

}} // namespace Mdt{ namespace Impl{

#endif // #ifndef MDT_APPLICATION_FOR_NON_QT_USAGE_IMPL_APPLICATION_FOR_NON_QT_USAGE_H
