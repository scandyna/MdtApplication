########################################################################################
#
# Copyright (C) 2019-2021 Philippe Steinmann.
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
cmake_minimum_required(VERSION 3.10)

project(MdtApplicationTest)

if(EXISTS "${CMAKE_BINARY_DIR}/conanbuildinfo.cmake")
  include("${CMAKE_BINARY_DIR}/conanbuildinfo.cmake")
  conan_basic_setup(NO_OUTPUT_DIRS)
endif()


find_package(Threads REQUIRED)
find_package(MdtCMakeModules REQUIRED)

include(MdtAddTest)
include(MdtSanitizers)


enable_testing()

# Conan does not propagate options to the test_package.
# For example:
# conan create . scandyna/testing -o MdtApplication:gui=True
# In the test_package/conanfile.py , it seems not to be sanely possible
# to check if the MdtApplication package was create with the gui option
#
# So, we expect that components depending on QtCore are allways available.
# For other components, we check if they are available, then test if they can be used.

find_package(Qt5 COMPONENTS Core REQUIRED)

set(CMAKE_AUTOMOC ON)

find_package(Mdt0 COMPONENTS ConsoleApplication CoreApplicationForNonQtUsage REQUIRED)


if(SANITIZER_ENABLE_THREAD)
  mdt_build_with_thread_sanitizer(BUILD_TYPES RelWithDebInfo)
  add_compile_options($<$<CONFIG:RelWithDebInfo>:${OPTIMIZATION_LEVEL_OPTION}>)
endif()


mdt_add_test(
  NAME ConsoleApplicationTest
  TARGET consoleApplicationTest
  DEPENDENCIES Mdt0::ConsoleApplication
  SOURCE_FILES
    ConsoleApplicationTest.cpp
    ConsoleApplicationTestMainFunction.cpp
)

mdt_add_test(
  NAME CoreApplicationForNonQtUsageTest
  TARGET coreApplicationForNonQtUsageTest
  DEPENDENCIES Mdt0::CoreApplicationForNonQtUsage
  SOURCE_FILES
    CoreApplicationForNonQtUsageTest.cpp
)

find_package(Mdt0 COMPONENTS GuiApplicationForNonQtUsage QUIET)
if(Mdt0GuiApplicationForNonQtUsage_FOUND)
  find_package(Qt5 COMPONENTS Gui REQUIRED)
  mdt_add_test(
    NAME GuiApplicationForNonQtUsageTest
    TARGET guiApplicationForNonQtUsageTest
    DEPENDENCIES Mdt0::GuiApplicationForNonQtUsage
    SOURCE_FILES
      GuiApplicationForNonQtUsageTest.cpp
  )
endif()
