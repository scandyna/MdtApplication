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
#ifndef MDT_APPLICATION_FOR_NON_QT_USAGE_IMPL_COMMAND_LINE_ARGUMENTS_H
#define MDT_APPLICATION_FOR_NON_QT_USAGE_IMPL_COMMAND_LINE_ARGUMENTS_H

#include "mdt_impl_applicationfornonqtusage_export.h"
#include <initializer_list>
#include <cassert>
#include <cstring>

namespace Mdt{ namespace Impl{

  /*! \internal Helper class to init and copy command line arguments
   */
  class MDT_IMPL_APPLICATIONFORNONQTUSAGE_EXPORT CommandLineArguments
  {
   public:

    /*! \brief Construct a null command line arguments
     */
    explicit CommandLineArguments() = default;

    /*! \brief Constrcut command line arguments with a copy \a args
     *
     * \pre \a args must contain at least 1 valid string
     * \pre each element in the list must be a valid string
     * \note This method takes care to add the required null pointer after the last argument.
     * \sa https://www.gnu.org/software/libc/manual/html_node/Program-Arguments.html
     */
    explicit CommandLineArguments(std::initializer_list<const char*> args)
     : mArgc(args.size()),
       mIsCopy(true)
    {
      assert(args.size() >= 1ul);

      mArgv = new char*[mArgc+1];
      int row = 0;
      for(const auto str : args){
        assert(str != nullptr);
        mArgv[row] = duplicateString(str);
        ++row;
      }
      mArgv[mArgc] = nullptr;
    }

    /*! \brief Constrcut command line arguments that references \a argv
     *
     * \pre \a argc must be >= 1
     */
    explicit CommandLineArguments(int argc, char **argv)
     : mArgc(argc),
       mArgv(argv),
       mIsCopy(false)
    {
      assert(argc >= 1);
    }

    /*! \brief Delete this command line arguments if it is a copy
     */
    ~CommandLineArguments()
    {
      cleanup();
    }

    /*! \brief Copy construct arguments from \a other
     */
    CommandLineArguments(const CommandLineArguments & other)
     : mArgc(other.mArgc),
       mIsCopy(true)
    {
      duplicateArgumentVector(other.mArgv);
    }

    /*! \brief Copy assign \a other to this arguments
     */
    CommandLineArguments & operator=(const CommandLineArguments & other)
    {
      if(&other == this){
        mIsCopy = other.mIsCopy;
      }else{
        cleanup();
        mArgc = other.mArgc;
        mIsCopy = true;
        duplicateArgumentVector(other.mArgv);
      }

      return *this;
    }

    CommandLineArguments(CommandLineArguments &&) = delete;
    CommandLineArguments & operator=(CommandLineArguments &&) = delete;

    /*! \brief Check if this command line arguments is a copy
     */
    bool isCopy() const noexcept
    {
      return mIsCopy;
    }

    /*! \brief Check if this command line arguments is null
     *
     * Returns true unless at least 1 argument exists
     */
    bool isNull() const noexcept
    {
      return mArgc <= 0;
    }

    /*! \brief Get the count of arguments
     */
    int argumentCount() const noexcept
    {
      return mArgc;
    }

    /*! \brief Access the count of arguments
     */
    int & argumentCountRef() noexcept
    {
      return mArgc;
    }

    /*! \brief Access the arguments vector
     *
     * \pre this command line arguments must not be null
     * \sa isNull()
     */
    char **argumentVector() const noexcept
    {
      assert(mArgv != nullptr);

      return mArgv;
    }

   private:

    void cleanup()
    {
      if(mIsCopy){
        for(int row = 0; row < mArgc; ++row){
          delete[] mArgv[row];
        }
        delete[] mArgv;
      }
    }

    static char *duplicateString(const char *sourceString)
    {
      assert(sourceString != nullptr);

      char *outString;
      const auto len = std::strlen(sourceString);
      outString = new char[len+1];
      std::strcpy(outString, sourceString);

      return outString;
    }

    void duplicateArgumentVector(char **argv)
    {
      mArgv = new char*[mArgc+1];
      for(int row = 0; row < mArgc; ++row){
        mArgv[row] = duplicateString(argv[row]);
      }
      mArgv[mArgc] = nullptr;
    }

    int mArgc = 0;
    char **mArgv = nullptr;
    bool mIsCopy = false;
  };

}} // namespace Mdt{ namespace Impl{

#endif // #ifndef MDT_APPLICATION_FOR_NON_QT_USAGE_IMPL_COMMAND_LINE_ARGUMENTS_H
