
cmake_minimum_required(VERSION 3.15)

project(MdtCommandLineArgumentsTest)

if(EXISTS "${CMAKE_BINARY_DIR}/conanbuildinfo.cmake")
  include("${CMAKE_BINARY_DIR}/conanbuildinfo.cmake")
  conan_basic_setup(NO_OUTPUT_DIRS)
endif()


find_package(MdtCMakeModules REQUIRED)
find_package(Mdt0 REQUIRED COMPONENTS CommandLineArguments)

include(MdtAddTest)

enable_testing()

mdt_add_test(
  NAME CommandLineArgumentsTest
  TARGET commandLineArgumentsTest
  DEPENDENCIES Mdt0::CommandLineArguments
  SOURCE_FILES
    main.cpp
)
