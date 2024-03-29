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
include(GenerateExportHeader)
include(MdtInstallLibrary)

add_library(Mdt_GuiApplicationForNonQtUsage
  Mdt/GuiApplicationForNonQtUsage.cpp
  "${MdtApplication_SOURCE_DIR}/libs/Impl_ApplicationForNonQtUsage/src/Mdt/Impl/ApplicationForNonQtUsage.cpp"
  "${MdtApplication_SOURCE_DIR}/libs/Impl_ApplicationForNonQtUsage/src/Mdt/Impl/ApplicationForNonQtUsageObject.cpp"
)

add_library(Mdt::GuiApplicationForNonQtUsage ALIAS Mdt_GuiApplicationForNonQtUsage)


if(BUILD_USE_IPO_LTO)
  set_target_properties(Mdt_GuiApplicationForNonQtUsage
    PROPERTIES INTERPROCEDURAL_OPTIMIZATION TRUE
  )
endif()

target_link_libraries(Mdt_GuiApplicationForNonQtUsage
  PUBLIC
    Mdt::Impl_ApplicationForNonQtUsage
    Qt5::Gui
#     Threads::Threads
)

target_include_directories(Mdt_GuiApplicationForNonQtUsage
  PUBLIC
   $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
   $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
)

# generate_export_header() does not generate for INTERFACE libraries,
# which Mdt_Impl_ApplicationForNonQtUsage is.
# So, we have to generate it here.
generate_export_header(Mdt_GuiApplicationForNonQtUsage
  BASE_NAME Mdt_X_ApplicationForNonQtUsage
)
target_include_directories(Mdt_Impl_ApplicationForNonQtUsage
  INTERFACE
   $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
)
install(FILES "${CMAKE_CURRENT_BINARY_DIR}/mdt_x_applicationfornonqtusage_export.h"
  DESTINATION ${MDT_INSTALL_INCLUDEDIR}
  COMPONENT Mdt_GuiApplicationForNonQtUsage_Dev
)

mdt_install_library(
  TARGET Mdt_GuiApplicationForNonQtUsage
  OBJECT_TARGETS Mdt_Impl_ApplicationForNonQtUsage
  RUNTIME_DESTINATION ${CMAKE_INSTALL_BINDIR}
  LIBRARY_DESTINATION ${CMAKE_INSTALL_LIBDIR}
  ARCHIVE_DESTINATION ${CMAKE_INSTALL_LIBDIR}
  INCLUDES_DIRECTORY .
  INCLUDES_FILE_WITHOUT_EXTENSION
  INCLUDES_DESTINATION ${MDT_INSTALL_INCLUDEDIR}
  EXPORT_NAME GuiApplicationForNonQtUsage
  EXPORT_NAMESPACE Mdt${PROJECT_VERSION_MAJOR}::
  INSTALL_NAMESPACE ${MDT_INSTALL_PACKAGE_NAME}
  FIND_PACKAGE_PATHS ..
  INSTALL_IS_UNIX_SYSTEM_WIDE ${MDT_INSTALL_IS_UNIX_SYSTEM_WIDE}
  VERSION ${PROJECT_VERSION}
  SOVERSION ${PROJECT_VERSION_MAJOR}
  VERSION_COMPATIBILITY ExactVersion
  RUNTIME_COMPONENT Mdt_GuiApplicationForNonQtUsage_Runtime
  DEVELOPMENT_COMPONENT Mdt_GuiApplicationForNonQtUsage_Dev
)
