########################################################################################
#
# Copyright (C) 2020-2022 Philippe Steinmann.
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
include(MdtInstallIncludes)

# There have been several tempted things here
#
# Static library:
# Works, but requires the user application to also link to this implementation library
# This was discovered while making the Conan package for MdtCoreApplicationForNonQtUsage
# (At the end, the user must only link to Mdt::CoreApplicationForNonQtUsage or Mdt::GuiApplicationForNonQtUsage)
#
# OBJECT library:
# This simply did never work properly
# At last try, it failed with MSVC.
# For example, see https://gitlab.com/scandyna/mdtapplication/-/jobs/2889409256
#
# What we need is to compile this implementation into the final libraries

add_library(Mdt_Impl_ApplicationForNonQtUsage INTERFACE)
add_library(Mdt::Impl_ApplicationForNonQtUsage ALIAS Mdt_Impl_ApplicationForNonQtUsage)

target_compile_features(Mdt_Impl_ApplicationForNonQtUsage INTERFACE cxx_std_14)

target_link_libraries(Mdt_Impl_ApplicationForNonQtUsage
  INTERFACE
    Mdt::CommandLineArguments
    Qt5::Core
#     Threads::Threads
)

target_include_directories(Mdt_Impl_ApplicationForNonQtUsage
  INTERFACE
   $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
   $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
)

mdt_install_include_directory(
  DIRECTORY .
  DESTINATION ${MDT_INSTALL_INCLUDEDIR}
  COMPONENT Mdt_Impl_ApplicationForNonQtUsage_Dev
)
