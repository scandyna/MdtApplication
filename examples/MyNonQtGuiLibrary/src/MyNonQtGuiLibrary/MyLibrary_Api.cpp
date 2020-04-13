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
#include "MyLibrary_Api.h"
#include <QTextCursor>
#include <QTextBlock>

namespace MyNonQtGuiLibrary{

void MyLibrary_Api::createReport(const ReportInformations & info)
{
  mDocument.clear();

  QTextCursor cursor(&mDocument);
  cursor.insertText( info.title() );
}

QString MyLibrary_Api::reportTitle() const
{
  const QTextBlock block = mDocument.begin();
  if( !block.isValid() ){
    return QString();
  }
  return block.text();
}

} // namespace MyNonQtGuiLibrary
