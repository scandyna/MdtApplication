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
include(GenerateExportHeader)

# MSVC complains about inconsistent dll linkage (C4273)
# and also throws error: definition of dllimport static data member not allowed (C2491)
# This has something to do with export headers
#
# generate_export_header() does not generate for INTERFACE libraries,
# which Mdt_Impl_ApplicationForNonQtUsage is.
#
# generate_export_header() does nothing for a executable,
# but only for libraries (which makes sense).
#
# As workaround, create a static library for the tests,
# which then can generate the correct export header.

add_library(Impl_ApplicationForNonQtUsageTest_Lib
    "${MdtApplication_SOURCE_DIR}/libs/Impl_ApplicationForNonQtUsage/src/Mdt/Impl/ApplicationForNonQtUsage.cpp"
    "${MdtApplication_SOURCE_DIR}/libs/Impl_ApplicationForNonQtUsage/src/Mdt/Impl/ApplicationForNonQtUsageObject.cpp"
)
target_link_libraries(Impl_ApplicationForNonQtUsageTest_Lib
  PUBLIC
    Mdt::Impl_ApplicationForNonQtUsage
)
generate_export_header(Impl_ApplicationForNonQtUsageTest_Lib
  BASE_NAME Mdt_X_ApplicationForNonQtUsage
)
target_include_directories(Mdt_Impl_ApplicationForNonQtUsage
  INTERFACE
   $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
)


mdt_add_test(
  NAME Impl_ApplicationForNonQtUsageTest
  TARGET impl_ApplicationForNonQtUsageTest
  DEPENDENCIES Impl_ApplicationForNonQtUsageTest_Lib Mdt::Catch2Main
  SOURCE_FILES
    src/Impl_ApplicationForNonQtUsageTest.cpp
)
