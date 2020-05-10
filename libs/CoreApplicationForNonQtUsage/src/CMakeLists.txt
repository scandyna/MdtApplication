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

# include(GenerateExportHeader)
include(MdtInstallLibrary)

# add_library(Mdt_CoreApplicationForNonQtUsage INTERFACE)
add_library(Mdt_CoreApplicationForNonQtUsage
  Mdt/CoreApplicationForNonQtUsage.cpp
)
add_library(Mdt::CoreApplicationForNonQtUsage ALIAS Mdt_CoreApplicationForNonQtUsage)


if(BUILD_USE_IPO_LTO)
  set_target_properties(Mdt_CoreApplicationForNonQtUsage
    PROPERTIES INTERPROCEDURAL_OPTIMIZATION TRUE
  )
endif()

target_link_libraries(Mdt_CoreApplicationForNonQtUsage
  PUBLIC
    Mdt::Impl_ApplicationForNonQtUsage
)

target_include_directories(Mdt_CoreApplicationForNonQtUsage
  PUBLIC
   $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
   $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
)

# generate_export_header(Mdt_CoreApplicationForNonQtUsage)

# mdt_install_interface_library(
#   TARGET Mdt_CoreApplicationForNonQtUsage
#   LIBRARY_DESTINATION ${CMAKE_INSTALL_LIBDIR}
#   INCLUDES_DIRECTORY .
#   INCLUDES_FILE_WITHOUT_EXTENSION
# #   ADDITIONAL_INCLUDES_FILES "${CMAKE_CURRENT_BINARY_DIR}/mdt_algorithms_export.h"
#   INCLUDES_DESTINATION ${MDT_INSTALL_INCLUDEDIR}
#   EXPORT_NAME CoreApplicationForNonQtUsage
#   EXPORT_NAMESPACE Mdt${PROJECT_VERSION_MAJOR}::
#   INSTALL_NAMESPACE ${MDT_INSTALL_PACKAGE_NAME}
#   FIND_PACKAGE_PATHS ..
#   VERSION ${PROJECT_VERSION}
#   VERSION_COMPATIBILITY ExactVersion
#   DEVELOPMENT_COMPONENT Mdt_CoreApplicationForNonQtUsage_Dev
# )

mdt_install_library(
  TARGET Mdt_CoreApplicationForNonQtUsage
  RUNTIME_DESTINATION ${CMAKE_INSTALL_BINDIR}
  LIBRARY_DESTINATION ${CMAKE_INSTALL_LIBDIR}
  ARCHIVE_DESTINATION ${CMAKE_INSTALL_LIBDIR}
  INCLUDES_DIRECTORY .
  INCLUDES_FILE_WITHOUT_EXTENSION
#   ADDITIONAL_INCLUDES_FILES "${CMAKE_CURRENT_BINARY_DIR}/mdt_coreapplicationfornonqtusage_export.h"
  INCLUDES_DESTINATION ${MDT_INSTALL_INCLUDEDIR}
  EXPORT_NAME CoreApplicationForNonQtUsage
  EXPORT_NAMESPACE Mdt${PROJECT_VERSION_MAJOR}::
  INSTALL_NAMESPACE ${MDT_INSTALL_PACKAGE_NAME}
  FIND_PACKAGE_PATHS ..
  INSTALL_IS_UNIX_SYSTEM_WIDE ${MDT_INSTALL_IS_UNIX_SYSTEM_WIDE}
  VERSION ${PROJECT_VERSION}
  SOVERSION ${PROJECT_VERSION_MAJOR}
  VERSION_COMPATIBILITY ExactVersion
  RUNTIME_COMPONENT Mdt_CoreApplicationForNonQtUsage_Runtime
  DEVELOPMENT_COMPONENT Mdt_CoreApplicationForNonQtUsage_Dev
)
