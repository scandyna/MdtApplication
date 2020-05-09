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
include(MdtAddTest)

mdt_add_test(
  NAME Impl_CommandLineArgumentsTest
  TARGET impl_CommandLineArgumentsTest
  DEPENDENCIES Mdt::Impl_ApplicationForNonQtUsage Mdt::Catch2Main
  SOURCE_FILES
    src/Impl_CommandLineArgumentsTest.cpp
)

mdt_add_test(
  NAME Impl_ApplicationForNonQtUsageTest
  TARGET impl_ApplicationForNonQtUsageTest
  DEPENDENCIES Mdt::Impl_ApplicationForNonQtUsage Mdt::Catch2Main
  SOURCE_FILES
    src/Impl_ApplicationForNonQtUsageTest.cpp
)