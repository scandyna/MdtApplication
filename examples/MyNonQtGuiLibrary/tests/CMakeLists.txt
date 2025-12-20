########################################################################################
#
# Copyright (C) 2020-2025 Philippe Steinmann.
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
  DEPENDENCIES MyNonQtGuiLibrary Mdt::Catch2Main Qt6::Gui
  SOURCE_FILES
    src/MyNonQtGuiLibrary_NonQtApi_Test.cpp
)

# TODO: remove once test fixed
# See https://gitlab.com/scandyna/mdtapplication/-/issues/6
if(SANITIZER_ENABLE_ADDRESS)
  set_tests_properties(MyNonQtGuiLibrary_NonQtApi_Test
    PROPERTIES
      DISABLED True
  )
endif()


mdt_add_test(
  NAME MyNonQtGuiLibrary_NonQtApi_ErrorTest
  TARGET myNonQtGuiLibrary_NonQtApi_ErrorTest
  DEPENDENCIES MyNonQtGuiLibrary Mdt::Catch2Main Qt6::Gui
  SOURCE_FILES
    src/MyNonQtGuiLibrary_NonQtApi_ErrorTest.cpp
)

# TODO: remove once test fixed
# See https://gitlab.com/scandyna/mdtapplication/-/issues/6
# Exceptions are not supported by TSan - TODO: check that
# https://github.com/google/sanitizers/issues/485
if(SANITIZER_ENABLE_ADDRESS OR SANITIZER_ENABLE_THREAD)
  set_tests_properties(MyNonQtGuiLibrary_NonQtApi_ErrorTest
    PROPERTIES
      DISABLED True
  )
endif()
