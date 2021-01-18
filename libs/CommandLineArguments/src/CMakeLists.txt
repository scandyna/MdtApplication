########################################################################################
#
# Copyright (C) 2020-2021 Philippe Steinmann.
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

add_library(Mdt_CommandLineArguments INTERFACE)
add_library(Mdt::CommandLineArguments ALIAS Mdt_CommandLineArguments)

target_compile_features(Mdt_CommandLineArguments INTERFACE cxx_std_14)

# if(BUILD_USE_IPO_LTO)
#   set_target_properties(Mdt_Impl_ApplicationForNonQtUsage
#     PROPERTIES INTERPROCEDURAL_OPTIMIZATION TRUE
#   )
# endif()

# target_link_libraries(Mdt_Impl_ApplicationForNonQtUsage
#   PUBLIC
#     Qt5::Core
#     Threads::Threads
# )

target_include_directories(Mdt_CommandLineArguments
  INTERFACE
   $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
#    $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
)

# if(BUILD_SHARED_LIBS)
#   set_property(TARGET Mdt_Impl_ApplicationForNonQtUsage PROPERTY POSITION_INDEPENDENT_CODE ON)
# endif()


mdt_install_interface_library(
  TARGET Mdt_CommandLineArguments
  LIBRARY_DESTINATION ${CMAKE_INSTALL_LIBDIR}
  INCLUDES_DIRECTORY .
  INCLUDES_DESTINATION ${MDT_INSTALL_INCLUDEDIR}
  EXPORT_NAME CommandLineArguments
  EXPORT_NAMESPACE Mdt${PROJECT_VERSION_MAJOR}::
  INSTALL_NAMESPACE ${MDT_INSTALL_PACKAGE_NAME}
  FIND_PACKAGE_PATHS ..
  VERSION ${PROJECT_VERSION}
  VERSION_COMPATIBILITY ExactVersion
  DEVELOPMENT_COMPONENT MdtApplication_Dev
)
