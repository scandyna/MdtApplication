########################################################################################
#
# Copyright (C) 2019-2020 Philippe Steinmann.
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

include(MdtAddTest)

message("ENABLE_CORE_APPLICATION_FOR_NON_QT_USAGE: ${ENABLE_CORE_APPLICATION_FOR_NON_QT_USAGE}")
message("ENABLE_GUI_APPLICATION_FOR_NON_QT_USAGE: ${ENABLE_GUI_APPLICATION_FOR_NON_QT_USAGE}")

find_package(Threads REQUIRED)
find_package(Mdt0 COMPONENTS CoreApplicationForNonQtUsage REQUIRED)

if(ENABLE_GUI_APPLICATION_FOR_NON_QT_USAGE)
  find_package(Mdt0 COMPONENTS GuiApplicationForNonQtUsage REQUIRED)
endif()


enable_testing()

mdt_add_test(
  NAME CoreApplicationForNonQtUsageTest
  TARGET coreApplicationForNonQtUsageTest
  DEPENDENCIES Mdt0::CoreApplicationForNonQtUsage
  SOURCE_FILES
    CoreApplicationForNonQtUsageTest.cpp
)

if(ENABLE_GUI_APPLICATION_FOR_NON_QT_USAGE)
  mdt_add_test(
    NAME GuiApplicationForNonQtUsageTest
    TARGET guiApplicationForNonQtUsageTest
    DEPENDENCIES Mdt0::GuiApplicationForNonQtUsage
    SOURCE_FILES
      GuiApplicationForNonQtUsageTest.cpp
  )
endif()
