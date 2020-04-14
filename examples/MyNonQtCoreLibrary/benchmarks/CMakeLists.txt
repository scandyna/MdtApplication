########################################################################################
#
# Copyright (C) 2019-2020 Philippe Steinmann.
#
# This file is part of QCoreApplicationForNonQtUsage library.
#
# QCoreApplicationForNonQtUsage is free software: you can redistribute it and/or modify
# it under the terms of the GNU Lesser General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# QCoreApplicationForNonQtUsage is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public License
# along with QCoreApplicationForNonQtUsage. If not, see <http://www.gnu.org/licenses/>.
#
########################################################################################
include(MdtAddTest)

mdt_add_test(
  NAME MyNonQtCoreLibraryBenchmark
  TARGET myNonQtCoreLibraryBenchmark
  DEPENDENCIES MyNonQtCoreLibrary Qt5::Core Qt5::Test
  SOURCE_FILES
    src/MyLibraryBenchmark.cpp
)

mdt_add_test(
  NAME MyNonQtCoreLibrary_NonQtApi_Benchmark
  TARGET myNonQtCoreLibrary_NonQtApi_Benchmark
  DEPENDENCIES MyNonQtCoreLibrary Qt5::Core Mdt::Catch2Main
  SOURCE_FILES
    src/MyLibrary_NonQtApi_Benchmark.cpp
)
