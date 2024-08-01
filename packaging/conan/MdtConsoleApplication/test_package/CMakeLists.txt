
cmake_minimum_required(VERSION 3.15)

project(MdtConsoleApplicationTest)

find_package(MdtCMakeModules REQUIRED)
find_package(Mdt0 REQUIRED COMPONENTS ConsoleApplication)
find_package(Qt5 REQUIRED COMPONENTS Core)

# message("Mdt0ConsoleApplication_DIR: ${Mdt0ConsoleApplication_DIR}")
# message("Qt5Core_DIR: ${Qt5Core_DIR}")

set(CMAKE_AUTOMOC ON)

include(MdtAddTest)

enable_testing()

mdt_add_test(
  NAME ConsoleApplicationTest
  TARGET consoleApplicationTest
  DEPENDENCIES Mdt0::ConsoleApplication
  SOURCE_FILES
    main.cpp
    ConsoleApplicationTestMainFunction.cpp
)
