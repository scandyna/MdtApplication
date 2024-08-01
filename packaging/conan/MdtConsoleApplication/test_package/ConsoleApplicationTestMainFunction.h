/****************************************************************************
 **
 ** Copyright (C) 2020-2022 Philippe Steinmann.
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
 ** along with MdtApplication.  If not, see <http://www.gnu.org/licenses/>.
 **
 ****************************************************************************/
#ifndef CONSOLE_APPLICATION_TEST_MAIN_FUNCTION_H
#define CONSOLE_APPLICATION_TEST_MAIN_FUNCTION_H

#include "Mdt/AbstractConsoleApplicationMainFunction"

class ConsoleApplicationTestMainFunction : public Mdt::AbstractConsoleApplicationMainFunction
{
  Q_OBJECT

 public:

  explicit ConsoleApplicationTestMainFunction(QObject* parent = nullptr)
   : AbstractConsoleApplicationMainFunction(parent)
  {
  }

  int runMain() override;
};

#endif // #ifndef CONSOLE_APPLICATION_TEST_MAIN_FUNCTION_H
