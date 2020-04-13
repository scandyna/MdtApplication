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
#ifndef MDT_GUI_APPLICATION_FOR_NON_QT_USAGE_H
#define MDT_GUI_APPLICATION_FOR_NON_QT_USAGE_H

#include "Mdt/Impl/ApplicationForNonQtUsage.h"
#include <QGuiApplication>
#include <initializer_list>

namespace Mdt{

  /*! \breif Provide a QGuiApplication for a non Qt application
   *
   */
  template<typename Worker>
  class GuiApplicationForNonQtUsage
  {
   public:

    /*! \brief Construct a gui application
     *
     * This overload can be used if you don't have access
     * to the command line arguments provided in
     * the main() function of a C/C++ application.
     *
     * \pre At least 1 argument must be provided (which is the command name)
     * \note This constructor takes care to add the required null pointer after the last argument.
     * \sa https://www.gnu.org/software/libc/manual/html_node/Program-Arguments.html
     * \sa GuiApplicationForNonQtUsage(int, char**)
     */
    explicit GuiApplicationForNonQtUsage(std::initializer_list<const char*> args)
     : mImpl(args)
    {
    }

    /*! \brief Construct a gui application
     *
     * Will start a new thread,
     *  then instanciate \a Worker and QGuiApplication
     *  and finally call exec() to start a event loop,
     *  all in the context of the new thread.
     */
    explicit GuiApplicationForNonQtUsage(int argc, char **argv)
     : mImpl(argc, argv)
    {
    }

    /*! \brief Stop the thread
     *
     * Will first quit the Qt event loop,
     *  then stop the thread.
     *  The instance of \a Worker will also be deleted.
     */
    ~GuiApplicationForNonQtUsage() = default;

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

    Impl::ApplicationForNonQtUsage<Worker, QGuiApplication> mImpl;
  };

} // namespace Mdt{

#endif // #ifndef MDT_GUI_APPLICATION_FOR_NON_QT_USAGE_H
