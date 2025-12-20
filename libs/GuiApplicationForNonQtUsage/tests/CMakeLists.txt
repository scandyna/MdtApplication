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
  NAME GuiApplicationForNonQtUsageTest
  TARGET guiApplicationForNonQtUsageTest
  DEPENDENCIES Mdt::GuiApplicationForNonQtUsage Mdt::Catch2Main
  SOURCE_FILES
    src/GuiApplicationForNonQtUsageTest.cpp
)

# TODO: remove once test fixed
# See https://gitlab.com/scandyna/mdtapplication/-/issues/6
if(SANITIZER_ENABLE_ADDRESS)
  set_tests_properties(GuiApplicationForNonQtUsageTest
    PROPERTIES
      DISABLED True
  )
endif()
