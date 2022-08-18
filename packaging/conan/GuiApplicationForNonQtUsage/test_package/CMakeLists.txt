
cmake_minimum_required(VERSION 3.15)

project(MdtGuiApplicationForNonQtUsageTest)

find_package(MdtCMakeModules REQUIRED)
find_package(Mdt0 REQUIRED COMPONENTS GuiApplicationForNonQtUsage)
find_package(Qt5 REQUIRED COMPONENTS Gui)

set(CMAKE_AUTOMOC ON)

enable_testing()

include(MdtAddTest)

mdt_add_test(
  NAME GuiApplicationForNonQtUsageTest
  TARGET guiApplicationForNonQtUsageTest
  DEPENDENCIES Mdt0::GuiApplicationForNonQtUsage
  SOURCE_FILES
    main.cpp
)
