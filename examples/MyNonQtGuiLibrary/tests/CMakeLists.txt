########################################################################################
#
# Copyright (C) 2020-2020 Philippe Steinmann.
#
# This file is part of MdtApplication library.
#
# MdtApplication is free software: you can redistribute it and/or modify
# it under the terms of the GNU Lesser General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# MdtApplication is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public License
# along with MdtApplication. If not, see <http://www.gnu.org/licenses/>.
#
########################################################################################
include(MdtAddTest)

mdt_add_test(
  NAME MyNonQtGuiLibrary_NonQtApi_Test
  TARGET myNonQtGuiLibrary_NonQtApi_Test
  DEPENDENCIES MyNonQtGuiLibrary Mdt::Catch2Main Qt5::Gui
  SOURCE_FILES
    src/MyNonQtGuiLibrary_NonQtApi_Test.cpp
)
