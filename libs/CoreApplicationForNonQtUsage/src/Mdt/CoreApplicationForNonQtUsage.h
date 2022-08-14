/****************************************************************************
 **
 ** Copyright (C) 2019-2022 Philippe Steinmann.
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
#ifndef MDT_CORE_APPLICATION_FOR_NON_QT_USAGE_H
#define MDT_CORE_APPLICATION_FOR_NON_QT_USAGE_H

#include "Mdt/Impl/ApplicationForNonQtUsage.h"
#include <QCoreApplication>
#include <initializer_list>

namespace Mdt{

  /*! \breif Provide a QCoreApplication for a non Qt application
   *
   * To be able to use some parts of Qt,
   *  it is needed to use a Qt event loop.
   *  The main event loop must be created with QCoreApplication.
   *
   * For a application that does not use Qt,
   *  no instance of QCoreApplication is created.
   *  If some sort of library is loaded from such application,
   *  the attempt could be to create a instance:
   * \code
   * MyLibrary_Api *myLibraryNew()
   * {
   *   QCoreApplication app;
   *
   *   app.exec();
   *
   *   return new MyLibrary_Api;
   * }
   * \endcode
   *  Here, the caller application is blocked until app.exec() finishes.
   *
   * A solution is run all the library stuff in a separate thread.
   *  All classes are then instanciated in this new thread context,
   *  which will also be the Qt main thread.
   *
   * \startuml
   *  !include MdtCoreApplicationForNonQtUsage_example.txt
   * \enduml
   *
   * Lets say that we have a MyLibrary_Api:
   * \code
   * class MyLibrary_Api : public QObject
   * {
   *   Q_OBJECT
   *
   *  public:
   *
   *   MyLibraryError sendCommand(const std::string & command);
   *
   *   void setValue(const std::string & value);
   *   const std::string & value() const;
   *
   *  signals:
   *
   *   void responseReceived(const std::string & response);
   *
   *  private:
   *
   *   std::string mValue;
   * };
   * \endcode
   *
   * In above code, \a MyLibraryError is a enum:
   * \code
   * enum class MyLibraryError
   * {
   *   NoError = 0,
   *   UnknownCommand = 12
   * };
   * \endcode
   *
   * Imagine that \a MyLibrary_Api uses some classes that rely on the Qt event loop,
   *  like QTcpSocket, QSerialPort, etc.., which works best when the asynchronous API are used.
   *
   * For the usage from a non Qt application, we can give access to MyLibrary_Api:
   * \code
   * class MyLibrary_NonQtApi : public QObject
   * {
   *   Q_OBJECT
   *
   *   using LockGuard = const std::lock_guard<std::mutex>;
   *
   *  public:
   *
   *   explicit MyLibrary_NonQtApi(QObject *parent = nullptr);
   *
   *   MyLibraryError sendCommand(const std::string & command);
   *   bool hasReceivedResponse() const;
   *   const std::string & response() const;
   *
   *   void setValue(const std::string & value);
   *   std::string value() const;
   *
   *  public slots:
   *
   *   void onResponseReceived(const std::string & response);
   *
   *  signals:
   *
   *   void invokeSendCommand(MyLibraryError & retVal, const std::string & command);
   *
   *   void invokeSetValue(const std::string & val);
   *   void invokeValue(std::string & value) const;
   *
   *  private:
   *
   *   mutable std::mutex mMutex;
   *   std::string mResponse;
   *   Mdt::CoreApplicationForNonQtUsage<MyLibrary_NonQtApi_Worker> mApp;
   * };
   * \endcode
   *
   * Next we have to create a worker, which will be created in the thread context of MyLibrary_Api:
   * \code
   * class MyLibrary_NonQtApi_Worker : public QObject
   * {
   *   Q_OBJECT
   *
   *  public:
   *
   *   explicit MyLibrary_NonQtApi_Worker(QObject *parent = nullptr);
   *
   *   std::string response() const;
   *
   *   MyLibrary_Api & libraryApi();
   *
   *  public slots:
   *
   *   void sendCommand(MyLibraryError & retVal, const std::string & command);
   *   void onResponseReceived(const std::string & response);
   *
   *   void setValue(const std::string & val)
   *   void value(std::string & val);
   *
   *  private:
   *
   *   MyLibrary_Api mLib;
   * };
   * \endcode
   *
   * MyLibrary_NonQtApi will be instanciated from the non Qt user, in its main thread context.
   *  Having a instance of Mdt::CoreApplicationForNonQtUsage, \a mApp , MyLibrary_NonQtApi_Worker will be instanciated from a separate thread.
   *  In this thread, a instance of QCoreApplication is also created.
   *
   * Next we have to call the methods of MyLibrary_Api in the correct thread.
   *  It could be tempting to try this:
   * \code
   * int MyLibrary_NonQtApi::value() const
   * {
   *   return mApp.worker().libraryApi().value();
   * }
   * \endcode
   * above code will call MyLibrary_Api::value() from the caller thread,
   *  which is wrong.
   *
   * We need a mechanism to invoke methods of MyLibrary_Api from his thread context.
   *  Qt offers us such tool: signal/slots with queued connections.
   *
   * The constructor of MyLibrary_NonQtApi makes some signal and slots connections:
   * \code
   * MyLibrary_NonQtApi::MyLibrary_NonQtApi(QObject *parent)
   *  : QObject(parent),
   *    mApp({"myappname"})
   * {
   *   connect(this, &MyLibrary_NonQtApi::invokeSendCommand, &mApp.worker(), &MyLibrary_NonQtApi_Worker::sendCommand, Qt::BlockingQueuedConnection);
   *   connect(&mApp.worker().libraryApi(), &MyLibrary_Api::responseReceived, this, &MyLibrary_NonQtApi::onResponseReceived, Qt::DirectConnection);
   *
   *   connect(this, &MyLibrary_NonQtApi::invokeSetValue, &mApp.worker(), &MyLibrary_NonQtApi_Worker::setValue, Qt::BlockingQueuedConnection);
   *   connect(this, &MyLibrary_NonQtApi::invokeValue, &mApp.worker(), &MyLibrary_NonQtApi_Worker::value, Qt::BlockingQueuedConnection);
   * }
   * \endcode
   *
   * Notice that the constructor does not get the standard \a argc and \a argv
   * arguments usually provided in the main() function of a C/C++ program,
   * so we provide our application name only.
   * See the constructors documentation of Mdt::CoreApplicationForNonQtUsage for more details.
   *
   * Here is the implementation of MyLibrary_NonQtApi::sendCommand():
   * \code
   * MyLibraryError MyLibrary_NonQtApi::sendCommand(const std::string & command)
   * {
   *   {
   *     LockGuard lock(mMutex);
   *     mResponse.clear();
   *   }
   *   MyLibraryError retVal;
   *   invokeSendCommand(retVal, command);
   *   return retVal;
   * }
   * \endcode
   *
   * The worker then calls MyLibrary_Api:
   * \code
   * void MyLibrary_NonQtApi_Worker::sendCommand(MyLibraryError & retVal, const std::string & command)
   * {
   *   retVal = mLib.sendCommand(command);
   * }
   * \endcode
   *
   * The invokeSendCommand() is called, which is in fact a signal emition.
   * Thanks to the Qt signal and slots mechanism,
   * this will be enough to call MyLibrary_Api::sendCommand() in its own thread context.
   *
   * The \a retVal variable is passed by reference,
   * so that the result can be available after the invocation.
   * Because we use BlockingQueuedConnection, there should be no data race on \a retVal .
   *
   * \a MyLibrary_Api will send a signal once it receives a response.
   *
   * The ideal solution would be to relay this signal to MyLibrary_NonQtApi,
   * then use some callback method to catch it from the non Qt application.
   * Doing so will require to have a QueuedConnection (or BlockingQueuedConnection)
   * from MyLibrary_Api to MyLibrary_NonQtApi.
   * This is not possible, because the receiver of a queued connection must have a Qt event loop,
   * which we don't have.
   *
   * A proper solution could be to implement (or use)
   * a mechanism that is able to invoke methods accross threads,
   * which seems not to be a easy task, and will not be covered here.
   * I personaly don't know how to invoke a function in the context of a target thread
   * (is it possible at all without having access to some event loop on target side ?).
   *
   * As workaround, MyLibrary_NonQtApi will receive the response and store a copy of it.
   *
   * Here is the implementation of the slot that update the response:
   * \code
   * void MyLibrary_NonQtApi::onResponseReceived(const std::string & response)
   * {
   *   LockGuard lock(mMutex);
   *   mResponse = response;
   * }
   * \endcode
   *
   * Again, this requires that the response is copiable.
   *
   * The implementation of the getter:
   * \code
   * const std::string & MyLibrary_NonQtApi::response() const
   * {
   *   LockGuard lock(mMutex);
   *   return mResponse;
   * }
   * \endcode
   *
   * The signal/slot connection uses a direct connection, so no Qt event loop is required on the receiver side:
   * \code
   * connect(&mApp.worker().libraryApi(), &MyLibrary_Api::responseReceived, this, &MyLibrary_NonQtApi::onResponseReceived, Qt::DirectConnection);
   * \endcode
   *
   * Here, mResponse is accessed by 2 separate thread, so it has to be protected by a mutex.
   *
   * This also transforms a event based design to some sort of synchronous API.
   *
   * The user could process like:
   * \code
   * MyLibrary_NonQtApi lib;
   *
   * if( !lib.sendCommand("command") ){
   *   // error handling
   * }
   * while( !lib.hasReceivedResponse() ){
   *   // Some application wait method
   * }
   * processResponse( lib.response() );
   * \endcode
   *
   *
   * MyLibrary_Api has also some value with a getter.
   * To avoid intrusive modifications on the library (think about concurency between MyLibrary_Api and MyLibrary_NonQtApi),
   * we have to call MyLibrary_Api::value() from his thread context.
   *
   * Here is the implementation of MyLibrary_NonQtApi::value():
   * \code
   * std::string MyLibrary_NonQtApi::value() const
   * {
   *   std::string val;
   *   invokeValue(val);
   *   return val;
   * }
   * \endcode
   *
   * the worker then calls MyLibrary_Api:
   * \code
   * void MyLibrary_NonQtApi_Worker::value(std::string & val)
   * {
   *   val = mLib.value();
   * }
   * \endcode
   *
   * Notice also that we get a copy of the value
   * (this will then not work with non copiable types).
   *
   * \note To have real shared states between MyLibrary_Api and MyLibrary_NonQtApi,
   *  MyLibrary_Api would have to be designed for thread concurency
   *  between calls comming from the rest of the library,
   *  and those comming from MyLibrary_NonQtApi.
   *  It could be tempting to add a mutex in MyLibrary_NonQtApi_Worker,
   *  but this will not help.
   *
   *
   * Maybe we also have a C wrapper. This topic is not covered here,
   *  but only a example of the implementation of some functions:
   * \code
   * MyLibrary_NonQtApi *myLibraryNew()
   * {
   *   return new MyLibrary_NonQtApi;
   * }
   *
   * int myLibrarySendCommand(MyLibrary_NonQtApi *lib, const char *command)
   * {
   *   return lib->sendCommand(command);
   * }
   *
   * void myLibraryDelete(MyLibrary_NonQtApi *lib)
   * {
   *   delete lib;
   * }
   * \endcode
   *
   * \sa https://stackoverflow.com/questions/25025168/event-loop-in-qt-based-dll-in-a-non-qt-application
   * \sa https://stackoverflow.com/questions/2150488/using-a-qt-based-dll-in-a-non-qt-application
   */
  template<typename Worker>
  class CoreApplicationForNonQtUsage
  {
   public:

    /*! \brief Construct a core application
     *
     * This overload can be used if you don't have access
     * to the command line arguments provided in
     * the main() function of a C/C++ application.
     *
     * \pre At least 1 argument must be provided (which is the command name)
     * \note This constructor takes care to add the required null pointer after the last argument.
     * \sa https://www.gnu.org/software/libc/manual/html_node/Program-Arguments.html
     * \sa CoreApplicationForNonQtUsage(int, char**)
     */
    explicit CoreApplicationForNonQtUsage(std::initializer_list<const char*> args)
     : mImpl(args)
    {
    }

    /*! \brief Construct a core application
     *
     * Will start a new thread,
     *  then instanciate \a Worker and QCoreApplication
     *  with a copy of \a argc and a copy of the content of \a argv
     *  and finally call exec() to start a event loop,
     *  all in the context of the new thread.
     *
     * \pre At least 1 argument must be provided (which is the command name)
     */
    explicit CoreApplicationForNonQtUsage(int argc, char **argv)
     : mImpl(argc, argv)
    {
    }

    /*! \brief Stop the thread
     *
     * Will first quit the Qt event loop,
     *  then stop the thread.
     *  The instance of \a Worker will also be deleted.
     */
    ~CoreApplicationForNonQtUsage() = default;

    /*! \brief Reference the worker
     */
    Worker & worker()
    {
      return mImpl.worker();
    }

    /*! \brief Reference the worker
     */
    const Worker & worker() const
    {
      return mImpl.worker();
    }

   private:

    Impl::ApplicationForNonQtUsage<Worker, QCoreApplication> mImpl;
  };

} // namespace Mdt{

#endif // #ifndef MDT_CORE_APPLICATION_FOR_NON_QT_USAGE_H
