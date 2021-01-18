/****************************************************************************
 **
 ** Copyright (C) 2020-2021 Philippe Steinmann.
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
#include "Mdt/CommandLineArguments.h"
#include <thread>
#include <atomic>
#include <memory>
#include <chrono>
#include <mutex>
#include <condition_variable>
#include <initializer_list>
#include <cassert>

namespace Mdt{ namespace Impl{

  /*! \internal
   */
  template<typename Worker, typename QApp>
  class ApplicationForNonQtUsage
  {
   public:

    ApplicationForNonQtUsage() = delete;

    explicit ApplicationForNonQtUsage(const CommandLineArguments & args)
     : mWorker(nullptr),
       mCommandLineArguments(args),
       mThread(run, this)
    {
      std::unique_lock<std::mutex> lock(mMutex);
      mInitDoneCondition.wait(lock, [this](){return mInitDone;});
    }

    explicit ApplicationForNonQtUsage(std::initializer_list<const char*> args)
    : ApplicationForNonQtUsage( CommandLineArguments(args) )
    {
    }

    explicit ApplicationForNonQtUsage(int argc, char **argv)
    : ApplicationForNonQtUsage( CommandLineArguments(argc, argv) )
    {
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
      /*
       * We have to instanciate commandLineArguments before app,
       * so we can meet the requirement of Q[Core|Gui]Application,
       * i.e. that arguments are valid the entire lifetime of app
       */
      CommandLineArguments commandLineArguments;
      std::unique_ptr<QApp> app;

      {
        std::lock_guard<std::mutex> lock(instance->mMutex);

        commandLineArguments = instance->mCommandLineArguments;
        assert( commandLineArguments.isCopy() );
        app.reset( new QApp(commandLineArguments.argumentCountRef(), commandLineArguments.argumentVector()) );

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
    CommandLineArguments mCommandLineArguments;
    std::thread mThread;
  };

}} // namespace Mdt{ namespace Impl{

#endif // #ifndef MDT_APPLICATION_FOR_NON_QT_USAGE_IMPL_APPLICATION_FOR_NON_QT_USAGE_H
