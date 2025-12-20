
cmake_minimum_required(VERSION 3.22)

project(MdtCoreApplicationForNonQtUsageTest)

find_package(MdtCMakeModules REQUIRED)

find_package(Mdt0 REQUIRED COMPONENTS CoreApplicationForNonQtUsage)
# find_package(Mdt0CoreApplicationForNonQtUsage REQUIRED)


message("Mdt0_FOUND: ${Mdt0_FOUND}")
message("Mdt0CoreApplicationForNonQtUsage_DIR: ${Mdt0CoreApplicationForNonQtUsage_DIR}")

set(CMAKE_AUTOMOC ON)

enable_testing()

include(MdtAddTest)

mdt_add_test(
  NAME CoreApplicationForNonQtUsageTest
  TARGET coreApplicationForNonQtUsageTest
  DEPENDENCIES Mdt0::CoreApplicationForNonQtUsage
  SOURCE_FILES
    main.cpp
)
