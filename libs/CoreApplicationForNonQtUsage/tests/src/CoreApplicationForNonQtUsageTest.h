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
#ifndef CORE_APPLICATION_FOR_NON_QT_USAGE_TEST_H
#define CORE_APPLICATION_FOR_NON_QT_USAGE_TEST_H

#include "Mdt/CoreApplicationForNonQtUsage"
#include <QCoreApplication>
#include <QObject>
#include <QString>
#include <QLatin1String>
#include <atomic>
#include <mutex>

class SomeComposedData
{
 public:

  void setId(int id)
  {
    mId = id;
  }

  int id() const
  {
    return mId;
  }

  void setName(const QString & name)
  {
    mName = name;
  }

  const QString & name() const
  {
    return mName;
  }

 private:

  int mId = 0;
  QString mName;
};


class MyBusinessLogic : public QObject
{
  Q_OBJECT

 public:

  void setValue(int value)
  {
    mValue = value;
  }

  int value() const
  {
    return mValue;
  }

  bool readData(const QString & filePath)
  {
    if(filePath.isEmpty()){
      return false;
    }
    mData.setId(5);
    mData.setName(QLatin1String("five"));

    return true;
  }

  const SomeComposedData & data() const
  {
    return mData;
  }

  void stop()
  {
  }

 private:

  int mValue = 0;
  SomeComposedData mData;
};

class MyPluginWorker : public QObject
{
  Q_OBJECT

 public:

  explicit MyPluginWorker()
   : QObject()
  {
  }

  ~MyPluginWorker()
  {
    // Maybe abort some long taks, like waiting a response on a port (network, serial port, ...)
    mBusinessLogic.stop();
  }

 public slots:

  void setValue(int value)
  {
    mBusinessLogic.setValue(value);
  }

  void value(std::atomic<int> & v) const
  {
    v = mBusinessLogic.value();
  }

  void readData(std::atomic<bool> & retVal, const QString & filePath)
  {
    retVal = mBusinessLogic.readData(filePath);
    emit dataHaveBeenRead(mBusinessLogic.data());
  }

 signals:

  void dataHaveBeenRead(const SomeComposedData & data);

 private:

  MyBusinessLogic mBusinessLogic;
};

class MyPlugin : public QObject
{
  Q_OBJECT

  using LockGuard = std::lock_guard<std::mutex>;

 public:

  explicit MyPlugin(QObject *parent = nullptr)
   : QObject(parent)
  {
    connect(this, &MyPlugin::readDataImpl, &mApp.worker(), &MyPluginWorker::readData, Qt::BlockingQueuedConnection);
    connect(this, &MyPlugin::setValueImpl, &mApp.worker(), &MyPluginWorker::setValue, Qt::BlockingQueuedConnection);
    connect(this, &MyPlugin::valueImpl, &mApp.worker(), &MyPluginWorker::value, Qt::BlockingQueuedConnection);
    connect(&mApp.worker(), &MyPluginWorker::dataHaveBeenRead, this, &MyPlugin::setDataCopy, Qt::DirectConnection);
  }

  void setValue(int value)
  {
    emit setValueImpl(value);
  }

  int value() const
  {
    std::atomic<int> v(0);
    valueImpl(v);
    return v;
  }

  bool readData(const QString & filePath)
  {
    std::atomic<bool> retVal(false);
    readDataImpl(retVal, filePath);
    return retVal;
  }

  const SomeComposedData & data() const
  {
    LockGuard lock(mMutex);
    return mDataCopy;
  }

 signals:

  void setValueImpl(int value);
  void valueImpl(std::atomic<int> & value) const;
  void readDataImpl(std::atomic<bool> & retVal, const QString & filePath);

 private slots:

  void setDataCopy(const SomeComposedData & data)
  {
    LockGuard lock(mMutex);
    mDataCopy = data;
  }

 private:

  SomeComposedData mDataCopy;
  mutable std::mutex mMutex;
  Mdt::CoreApplicationForNonQtUsage<MyPluginWorker> mApp;
};

#endif // #ifndef CORE_APPLICATION_FOR_NON_QT_USAGE_TEST_H
