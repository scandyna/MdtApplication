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
include(GenerateExportHeader)

add_library(MyNonQtGuiLibrary
  MyNonQtGuiLibrary/MyLibrary_NonQtApi.cpp
  MyNonQtGuiLibrary/MyLibrary_NonQtApi_Worker.cpp
  MyNonQtGuiLibrary/MyLibrary_Api.cpp
)


if(BUILD_USE_IPO_LTO)
  set_target_properties(MyNonQtGuiLibrary
    PROPERTIES INTERPROCEDURAL_OPTIMIZATION TRUE
  )
endif()

target_link_libraries(MyNonQtGuiLibrary
  PUBLIC
    Mdt::GuiApplicationForNonQtUsage
)

target_include_directories(MyNonQtGuiLibrary
  PUBLIC
   $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
   $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
)

generate_export_header(MyNonQtGuiLibrary)
