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
cmake_minimum_required(VERSION 3.15)

# CMAKE_PREFIX_PATH is empty before any call to project()
# Because set_project_version() does not exist,
# we call the project command twice (is there a cleaner solution?)
project(MdtApplication)

#######################
# Conan
#######################

# if(EXISTS "${CMAKE_BINARY_DIR}/conanbuildinfo.cmake")
#   include("${CMAKE_BINARY_DIR}/conanbuildinfo.cmake")
#   conan_basic_setup(NO_OUTPUT_DIRS)
# endif()

##################################################################
# Project definition with versionning got from git tag or by Conan
##################################################################

find_package(Git REQUIRED)
find_package(MdtCMakeModules REQUIRED)

include(MdtVersionUtils)

message(STATUS "FROM_CONAN_PROJECT_VERSION: ${FROM_CONAN_PROJECT_VERSION}")

set(INITIAL_PROJECT_VERSION)
if(FROM_CONAN_PROJECT_VERSION)
  set(INITIAL_PROJECT_VERSION ${FROM_CONAN_PROJECT_VERSION})
else()
  mdt_cmake_project_version_from_git_tag(INITIAL_PROJECT_VERSION DEFAULT_VERSION 0.0.1)
endif()

project(MdtApplication VERSION ${INITIAL_PROJECT_VERSION} LANGUAGES CXX)

unset(INITIAL_PROJECT_VERSION)

message("CMAKE_PREFIX_PATH: ${CMAKE_PREFIX_PATH}")

#######################
# Options
#######################

include(MdtBuildOptionsUtils)
include(MdtSanitizers)
# include(CMakeDependentOption)

set(CMAKE_CXX_VISIBILITY_PRESET hidden)
set(CMAKE_VISIBILITY_INLINES_HIDDEN YES)

option(ENABLE_CORE_APPLICATION_FOR_NON_QT_USAGE "Enable the CoreApplicationForNonQtUsage component" ON)
option(ENABLE_GUI_APPLICATION_FOR_NON_QT_USAGE "Enable the GuiApplicationForNonQtUsage component" OFF)

# CoreApplicationForNonQtUsage and GuiApplicationForNonQtUsage depends on CommandLineArguments
# When working on MdtApplication, we should enable CommandLineArguments
# When creating packages, we don't depend on CommandLineArguments subdirectory,
# but on the MdtCommandLineArguments package.
# In that case, don't add CommandLineArguments's subdirectory
option(ENABLE_COMMAND_LINE_ARGUMENTS "Enable CommandLineArguments" OFF)
option(USE_COMMAND_LINE_ARGUMENTS_IMPORT_TARGET "Use MdtCommandLineArguments IMPORT TARGET (relevant only while creating packages)" OFF)

# set(CommandLineArgumentsOptional TRUE)
# if(ENABLE_CORE_APPLICATION_FOR_NON_QT_USAGE OR ENABLE_GUI_APPLICATION_FOR_NON_QT_USAGE)
#   set(CommandLineArgumentsOptional FALSE)
# endif()
# cmake_dependent_option(ENABLE_COMMAND_LINE_ARGUMENTS "Enable CommandLineArguments" OFF "CommandLineArgumentsOptional" ON)

option(ENABLE_CONSOLE_APPLICATION "Enable ConsoleApplication" OFF)

if(ENABLE_CORE_APPLICATION_FOR_NON_QT_USAGE OR ENABLE_GUI_APPLICATION_FOR_NON_QT_USAGE OR ENABLE_CONSOLE_APPLICATION)
  set(REQUIRES_QT TRUE)
else()
  set(REQUIRES_QT FALSE)
endif()

option(BUILD_TESTS "Build the tests" OFF)
option(BUILD_BENCHMARKS "Build the benchmarks" OFF)
option(BUILD_EXAMPLES "Build the examples" OFF)
option(BUILD_CPP_API_DOC "Generate Doxyfile for C++ API documentation" OFF)
mdt_set_available_build_types(Release Debug RelWithDebInfo MinSizeRel Instrumented)
option(WARNING_AS_ERROR "Threat warnings as errors" OFF)

# Provide LPO/LTO option if supported
# Note: CMake before 3.9 does only support Intel compiler on Linux.
#       Check documentation of the CheckIPOSupported module,
#       and also CMP0069 policy.
include(CheckIPOSupported)
check_ipo_supported(RESULT HAVE_IPO_LTO)
if(HAVE_IPO_LTO)
  option(BUILD_USE_IPO_LTO "Use link-time optimization" OFF)
endif()

mdt_get_available_optimization_levels(AVAILABLE_OPTIMIZATION_LEVELS)
set(BUILD_TYPE_INSTRUMENTED_OPTIMIZATION_LEVEL "" CACHE STRING "Set optimization level for Instrumented build")
set_property(CACHE BUILD_TYPE_INSTRUMENTED_OPTIMIZATION_LEVEL PROPERTY STRINGS ${AVAILABLE_OPTIMIZATION_LEVELS})
option(BUILD_TYPE_INSTRUMENTED_USE_DEBUG_SYMBOLS "Add debug symbols (-g on Gcc/Clang, /DEBUG on MSVC)" ON)
option(BUILD_TYPE_INSTRUMENTED_DEFINE_NDEBUG "Set NDEBUG definition for Instrumented build (will disable assert)" OFF)
option(BUILD_SHARED_LIBS "Build shared libraries" ON)

mdt_add_address_sanitizer_option_if_available(SANITIZER_ENABLE_ADDRESS
  HELP_STRING "Enable address sanitizer for Instrumented, RelWithDebInfo, Debug build"
  INITIAL_VALUE OFF
)
mdt_add_memory_sanitizer_option_if_available(SANITIZER_ENABLE_MEMORY
  HELP_STRING "Enable memory sanitizer for Instrumented, RelWithDebInfo, Debug build"
  INITIAL_VALUE OFF
)
mdt_add_undefined_sanitizer_option_if_available(SANITIZER_ENABLE_UNDEFINED
  HELP_STRING "Enable undefined behaviour sanitizer for Instrumented, RelWithDebInfo, Debug build"
  INITIAL_VALUE OFF
)
mdt_add_thread_sanitizer_option_if_available(SANITIZER_ENABLE_THREAD
  HELP_STRING "Enable thread sanitizer for Instrumented, RelWithDebInfo, Debug build (can be incompatible with other sanitizers)"
  INITIAL_VALUE OFF
)

#######################
# Warnings
#######################

if(MSVC)
  add_compile_options(/W3)
  if(WARNING_AS_ERROR)
    add_compile_options(/WX)
  endif()
  # C4996: 'strcpy': This function or variable may be unsafe. Consider using strcpy_s instead (which not works with gcc/clang)
  add_compile_options(/wd4996)
else()
  add_compile_options(-Wall -Wextra -pedantic -Wconversion)
  if(WARNING_AS_ERROR)
    add_compile_options(-Werror)
  endif()
endif()

# See https://stackoverflow.com/questions/46798456/handling-gccs-noexcept-type-warning
# if( (${CMAKE_CXX_COMPILER_ID} MATCHES "GNU") AND (${CMAKE_CXX_COMPILER_VERSION} VERSION_GREATER_EQUAL 7.2) )
#   add_compile_options(-Wno-noexcept-type)
# endif()

#######################
# Paths to dependencies
#######################

include(AddQt5ToCMakePrefixPath)

set(QT_PREFIX_PATH CACHE PATH "Path to the root of Qt distribution. (For example: /opt/qt/Qt5/5.13.0/gcc_64). If empty, system distribution is considered.")
add_qt5_to_cmake_prefix_path("${QT_PREFIX_PATH}")

#######################
# Dependencies
#######################

if(REQUIRES_QT)
  find_package(Threads REQUIRED)
  find_package(Qt5 COMPONENTS Core REQUIRED)
endif()

if(ENABLE_GUI_APPLICATION_FOR_NON_QT_USAGE)
  find_package(Qt5 COMPONENTS Gui REQUIRED)
endif()

if(USE_COMMAND_LINE_ARGUMENTS_IMPORT_TARGET)
  find_package(Mdt${MdtApplication_VERSION_MAJOR} REQUIRED COMPONENTS CommandLineArguments)
  add_library(Mdt::CommandLineArguments ALIAS Mdt${MdtApplication_VERSION_MAJOR}::CommandLineArguments)
endif()

if(BUILD_TESTS)
  find_package(Catch2 REQUIRED)
  find_package(Qt5 COMPONENTS Test REQUIRED)
endif()

if(BUILD_CPP_API_DOC)
  include(FindDoxygen)
  find_package(Doxygen REQUIRED dot)
endif()

#######################
# Windows specific
#######################

# On Windows, RPATH do not exist
# To be able to run tests, we have to put all binaries in the same directory
# TODO: should remove to face the bug !
if(WIN32)
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
endif()

# Workaround for the "too many sections" error on some MinGW compiler
# See: https://stackoverflow.com/questions/16596876/object-file-has-too-many-sections
if(MINGW)
  add_compile_options(-Wa,-mbig-obj)
endif()

#######################
# Sanitizers
#######################

if(SANITIZER_ENABLE_ADDRESS)
  mdt_build_with_address_sanitizer(BUILD_TYPES Instrumented RelWithDebInfo Debug)
endif()
if(SANITIZER_ENABLE_MEMORY)
  mdt_build_with_memory_sanitizer(BUILD_TYPES Instrumented RelWithDebInfo Debug)
endif()
if(SANITIZER_ENABLE_UNDEFINED)
  mdt_build_with_undefined_sanitizer(BUILD_TYPES Instrumented RelWithDebInfo Debug)
endif()
if(SANITIZER_ENABLE_THREAD)
  message(VERBOSE "Build with TSan for Instrumented RelWithDebInfo Debug")
  mdt_build_with_thread_sanitizer(BUILD_TYPES Instrumented RelWithDebInfo Debug)
endif()

#######################
# Instrumented build
#######################

if(BUILD_TYPE_INSTRUMENTED_OPTIMIZATION_LEVEL)
  add_compile_options($<$<CONFIG:Instrumented>:${BUILD_TYPE_INSTRUMENTED_OPTIMIZATION_LEVEL}>)
endif()

if(BUILD_TYPE_INSTRUMENTED_USE_DEBUG_SYMBOLS)
  mdt_add_debug_symbols_compile_option(BUILD_TYPES Instrumented)
endif()

if(BUILD_TYPE_INSTRUMENTED_DEFINE_NDEBUG)
  add_definitions($<$<CONFIG:Instrumented>:NDEBUG>)
endif()

#######################
# Install
#######################

set(MDT_INSTALL_PACKAGE_NAME Mdt${PROJECT_VERSION_MAJOR})
include(GNUInstallDirs)
include(MdtInstallDirs)
include(MdtPackageConfigHelpers)

# TODO: remove
# mdt_install_namespace_package_config_file(
#   INSTALL_NAMESPACE ${MDT_INSTALL_PACKAGE_NAME}
#   DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/${MDT_INSTALL_PACKAGE_NAME}"
#   COMPONENT Mdt_Dev
# )

#######################
# Qt
#######################

if(REQUIRES_QT)
  # TODO: not a target property, will it be propagated trough projects ??
  add_definitions(-DQT_NO_CAST_DEFINITIONS -DQT_NO_CAST_FROM_ASCII -DQT_NO_CAST_TO_ASCII -DQT_NO_CAST_FROM_BYTEARRAY)

  set(CMAKE_AUTOMOC ON)
  set(CMAKE_AUTOUIC ON)
endif()

#######################
# Sources and tests
#######################

if(BUILD_TESTS)
  add_library(Mdt_Catch2Main STATIC Catch2Main.cpp)
  target_link_libraries(Mdt_Catch2Main PUBLIC Catch2::Catch2)
  add_library(Mdt::Catch2Main ALIAS Mdt_Catch2Main)

  enable_testing()
endif()

if(ENABLE_COMMAND_LINE_ARGUMENTS)
  add_subdirectory(libs/CommandLineArguments)
endif()

if(ENABLE_CONSOLE_APPLICATION)
  add_subdirectory(libs/ConsoleApplication)
endif()

if(ENABLE_CORE_APPLICATION_FOR_NON_QT_USAGE OR ENABLE_GUI_APPLICATION_FOR_NON_QT_USAGE)
  add_subdirectory(libs/Impl_ApplicationForNonQtUsage)
endif()

if(ENABLE_CORE_APPLICATION_FOR_NON_QT_USAGE)
  add_subdirectory(libs/CoreApplicationForNonQtUsage)
endif()

if(ENABLE_GUI_APPLICATION_FOR_NON_QT_USAGE)
  add_subdirectory(libs/GuiApplicationForNonQtUsage)
endif()

if(BUILD_EXAMPLES)
  add_subdirectory(examples)
endif()

# Keep this at last
# A CMake dependency graph will be generated,
# that requires targets to be defined before
if(BUILD_CPP_API_DOC)
  add_subdirectory(doc)
endif()


#######################
# Debug
#######################

message(STATUS "CMAKE_BUILD_TYPE:${CMAKE_BUILD_TYPE}")
message(STATUS "BUILD_SHARED_LIBS:${BUILD_SHARED_LIBS}")
message(STATUS "CMAKE_CXX_FLAGS:${CMAKE_CXX_FLAGS}")
message(STATUS "IPO supported: ${HAVE_IPO_LTO}")
message(STATUS "BUILD_USE_IPO_LTO: ${BUILD_USE_IPO_LTO}")
