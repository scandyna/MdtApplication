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
  NAME MyNonQtCoreLibraryTest
  TARGET myNonQtCoreLibraryTest
  DEPENDENCIES MyNonQtCoreLibrary Qt5::Test
  SOURCE_FILES
    src/MyLibraryTest.cpp
)

# TODO: Qt5::Core seems not to be added to the ENVIRONMENT
#       maybe a bug in mdt_add_test()
mdt_add_test(
  NAME MyNonQtCoreLibrary_NonQtApi_Test
  TARGET myNonQtCoreLibrary_NonQtApi_Test
  DEPENDENCIES MyNonQtCoreLibrary Mdt::Catch2Main Qt5::Core
  SOURCE_FILES
    src/MyLibrary_NonQtApi_Test.cpp
)

# get_test_property(MyNonQtCoreLibraryTest ENVIRONMENT testEnv)
# message("MyNonQtCoreLibraryTest ENV: ${testEnv}")

# get_test_property(MyNonQtCoreLibrary_NonQtApi_Test ENVIRONMENT testEnv)
# message("MyNonQtCoreLibrary_NonQtApi_Test ENV: ${testEnv}")
