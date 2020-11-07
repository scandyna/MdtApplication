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
include(GenerateExportHeader)
include(MdtInstallLibrary)

add_library(Mdt_Impl_ApplicationForNonQtUsage STATIC
  Mdt/Impl/CommandLineArguments.cpp
#   Mdt/Impl/ApplicationForNonQtUsage.cpp
  Mdt/Impl/ApplicationForNonQtUsageObject.cpp
)
add_library(Mdt::Impl_ApplicationForNonQtUsage ALIAS Mdt_Impl_ApplicationForNonQtUsage)

target_compile_features(Mdt_Impl_ApplicationForNonQtUsage PUBLIC cxx_std_14)

if(BUILD_USE_IPO_LTO)
  set_target_properties(Mdt_Impl_ApplicationForNonQtUsage
    PROPERTIES INTERPROCEDURAL_OPTIMIZATION TRUE
  )
endif()

target_link_libraries(Mdt_Impl_ApplicationForNonQtUsage
  PUBLIC
    Qt5::Core
    Threads::Threads
)

target_include_directories(Mdt_Impl_ApplicationForNonQtUsage
  PUBLIC
   $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
   $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
)

# target_include_directories(Mdt_Impl_ApplicationForNonQtUsage
#   PRIVATE
#     $<BUILD_INTERFACE:$<TARGET_PROPERTY:Qt5::Core,INTERFACE_INCLUDE_DIRECTORIES>>
#   PUBLIC
#    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
#    $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
# )

if(BUILD_SHARED_LIBS)
  set_property(TARGET Mdt_Impl_ApplicationForNonQtUsage PROPERTY POSITION_INDEPENDENT_CODE ON)
endif()

# generate_export_header(Mdt_Impl_ApplicationForNonQtUsage)

mdt_install_interface_library(
  TARGET Mdt_Impl_ApplicationForNonQtUsage
  LIBRARY_DESTINATION ${CMAKE_INSTALL_LIBDIR}
  INCLUDES_DIRECTORY .
#   INCLUDES_FILE_WITHOUT_EXTENSION
#   ADDITIONAL_INCLUDES_FILES "${CMAKE_CURRENT_BINARY_DIR}/mdt_impl_applicationfornonqtusage_export.h"
  INCLUDES_DESTINATION ${MDT_INSTALL_INCLUDEDIR}
  EXPORT_NAME Impl_ApplicationForNonQtUsage
  EXPORT_NAMESPACE Mdt${PROJECT_VERSION_MAJOR}::
  INSTALL_NAMESPACE ${MDT_INSTALL_PACKAGE_NAME}
  FIND_PACKAGE_PATHS ..
  VERSION ${PROJECT_VERSION}
  VERSION_COMPATIBILITY ExactVersion
  DEVELOPMENT_COMPONENT Mdt_Impl_ApplicationForNonQtUsage_Dev
)

# mdt_install_library(
#   TARGET Mdt_Impl_ApplicationForNonQtUsage
#   RUNTIME_DESTINATION ${CMAKE_INSTALL_BINDIR}
#   LIBRARY_DESTINATION ${CMAKE_INSTALL_LIBDIR}
#   ARCHIVE_DESTINATION ${CMAKE_INSTALL_LIBDIR}
#   INCLUDES_DIRECTORY .
#   INCLUDES_FILE_WITHOUT_EXTENSION
#   ADDITIONAL_INCLUDES_FILES "${CMAKE_CURRENT_BINARY_DIR}/mdt_impl_applicationfornonqtusage_export.h"
#   INCLUDES_DESTINATION ${MDT_INSTALL_INCLUDEDIR}
#   EXPORT_NAME Impl_ApplicationForNonQtUsage
#   EXPORT_NAMESPACE Mdt${PROJECT_VERSION_MAJOR}::
#   INSTALL_NAMESPACE ${MDT_INSTALL_PACKAGE_NAME}
#   FIND_PACKAGE_PATHS ..
#   INSTALL_IS_UNIX_SYSTEM_WIDE ${MDT_INSTALL_IS_UNIX_SYSTEM_WIDE}
#   VERSION ${PROJECT_VERSION}
#   SOVERSION ${PROJECT_VERSION_MAJOR}
#   VERSION_COMPATIBILITY ExactVersion
#   RUNTIME_COMPONENT Mdt_Impl_ApplicationForNonQtUsage_Runtime
#   DEVELOPMENT_COMPONENT Mdt_Impl_ApplicationForNonQtUsage_Dev
# )
