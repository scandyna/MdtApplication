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
#include "GuiApplicationForNonQtUsage.h"
#include "mdt_guiapplicationfornonqtusage_export.h"
#include <QtGlobal>

#if defined Q_CC_MSVC

namespace Mdt{ namespace Impl{ namespace Workaround{ namespace GuiApplicationForNonQtUsage{

  /*
   * Workaround to force MSVC to generate a .lib
   * See https://gitlab.com/scandyna/mdtapplication/-/issues/1
   */
  MDT_GUIAPPLICATIONFORNONQTUSAGE_EXPORT
  void fakeFunctionToGenerateSymbolsToExport()
  {
  }

}}}} // namespace Mdt{ namespace Impl{ namespace Workaround{ namespace GuiApplicationForNonQtUsage{

#endif // #if defined Q_CC_MSVC
