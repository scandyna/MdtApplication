########################################################################################
#
# Copyright (C) 2019-2022 Philippe Steinmann.
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
  NAME CommandLineArgumentsTest
  TARGET commandLineArgumentsTest
  DEPENDENCIES Mdt::CommandLineArguments Mdt::Catch2Main
  SOURCE_FILES
    src/CommandLineArgumentsTest.cpp
)

# In the tests we check that self assigning works
# Clang, since version 7, warns about that
if( (${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang") AND (${CMAKE_CXX_COMPILER_VERSION} VERSION_GREATER_EQUAL 7) )
  target_compile_options(commandLineArgumentsTest
    PRIVATE "-Wno-self-assign-overloaded"
  )
endif()
