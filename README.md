# MdtApplication

Some additions for QCoreApplication, QGuiApplication and QApplication.

This library is composed of some components:

| Component                    | Description                                         | Main dependency |
|------------------------------|:----------------------------------------------------|-----------------|
| CoreApplicationForNonQtUsage | Provide a QCoreApplication for a non Qt application | QtCore          |
| GuiApplicationForNonQtUsage  | Provide a QGuiApplication for a non Qt application  | QtGui           |
| ConsoleApplication           | Helpers to create console application with Qt       | QtCore          |

# Usage

For the available classes, functions, and their usage,
see [the API documentation](https://scandyna.gitlab.io/mdtapplication)

## Required tools and libraries

Some tools and libraries are required to use MdtApplication:
 - Git
 - CMake
 - Conan (optional)
 - A compiler (Gcc or Clang or MSVC)
 - Make (optional)
 - Qt5

For a overview how to install them, see https://gitlab.com/scandyna/build-and-install-cpp

## CMake project description

Update your CMakeLists.txt to use the required libraries:
```cmake
cmake_minimum_required(VERSION 3.15)
project(MyApp)

find_package(Threads REQUIRED)
find_package(Qt5 COMPONENTS Core Gui REQUIRED)
find_package(Mdt0 COMPONENTS GuiApplicationForNonQtUsage REQUIRED)

add_executable(myApp myApp.cpp)
target_link_libraries(myApp Mdt0::GuiApplicationForNonQtUsage)
```

## Project configuration using Conan

MdtApplication has at least those dependencies:
 - [mdt-cmake-modules](https://gitlab.com/scandyna/mdt-cmake-modules)
 - Qt5

Qt5 can be installed using Conan, which can be usefull
if the required binaries are not distributed by Qt
(such a case will be discussed later).
Using your own installed Qt5 library is also supported.

Here are the available options:

| Option           | Default | Possible Values  | Explanations |
| -----------------|:------- |:----------------:|--------------|
| shared           | True    |  [True, False]   | Build as shared library |
| gui              | True    |  [True, False]   | Include the libraries that depends on QtGui |
| use_conan_qt     | False   |  [True, False]   | Use [conan Qt](https://github.com/bincrafters/conan-qt) as conan dependency |

TODO: use_conan_qt should be True by default !
TODO: update link to Qt

In your source directory, create a `conanfile.txt`:
```conan
[requires]
MdtApplication/x.y.z@scandyna/testing

[generators]
cmake
virtualenv

[options]
MdtApplication:gui=True
```

# TODO: remove
Update your CMakeLists to use the conanbuildinfo.cmake
(recommended, because it then handles important details
like using the correct libstdc++/libc++ library,
and does some checks):
```cmake
if(EXISTS "${CMAKE_BINARY_DIR}/conanbuildinfo.cmake")
  include("${CMAKE_BINARY_DIR}/conanbuildinfo.cmake")
  conan_basic_setup(NO_OUTPUT_DIRS)
endif()
```

Create a build directory and cd to it:
```bash
mkdir build
cd build
```

# TODO: profile build ...
Install the dependencies:
```bash
conan install -s build_type=Release --build=missing ..
```

Activate the build environment:
```bash
source activate.sh
```

Configure your project:
```bash
cmake -DCMAKE_BUILD_TYPE=Release ..
cmake-gui .
```

To restore the standard environment:
```bash
source deactivate.sh
```

## Project configuration without Conan

Build MdtApplication (see below) and install it somewhere, for example in `~/opt/MdtApplication`.

Create a build directory and cd to it:
```bash
mkdir build
cd build
```

Configure your project:
```bash
cmake -DCMAKE_PREFIX_PATH=~/opt/MdtApplication -DCMAKE_BUILD_TYPE=Release ..
cmake-gui .
```

Build your project:
```bash
cmake --build . --config Release
```

Note that the `--config Release` is only mandatory
for multi configuration build systems, like MSVC.

# Install MdtApplication

This chapter covers only the installation of the library.
To run the unit tests, see the next chapter.

Get MdtApplication:
```bash
git clone git@gitlab.com:scandyna/mdtapplication.git
```

Create a build directory and cd to it:
```bash
mkdir build
cd build
```

## Using Conan profiles

When using Conan for dependency management,
it is recommended to use Conan profiles.
This permits to have personal binary repository,
avoiding to recompile everything everytime.
This becomes more important if Qt is managed by Conan.

This requires modifications in the `settings.yml` Conan configuration,
and also some profile files.
See my [conan-config repository](https://gitlab.com/scandyna/conan-config) for more informations.

Some following sections will rely on Conan profiles.

## Note about install prefix

Some note on the `CMAKE_INSTALL_PREFIX`:
 - To target a system wide installation on Linux, set it to `/usr` (`-DCMAKE_INSTALL_PREFIX=/usr`) .
 - For other locations, spcecify also the `<package-name>`, (for example `-DCMAKE_INSTALL_PREFIX=~/opt/MdtApplication`).

For details about that, see:
 - https://scandyna.gitlab.io/mdt-cmake-modules/Modules/MdtInstallDirs.html
 - https://cmake.org/cmake/help/latest/variable/CMAKE_INSTALL_PREFIX.html
 - https://scandyna.gitlab.io/mdt-cmake-modules/Modules/MdtInstallLibrary.html

## Configure MdtApplication with Conan

Install the dependencies:
```bash
conan install -s build_type=Release --build=missing ..
```

Configure MdtApplication:
```bash
cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=~/opt/MdtApplication ..
cmake-gui .
```

## Build and install MdtApplication

To build and install, run:
```cmd
cmake --build . --target INSTALL --config Release
```

Note that the `--config Release` is only mandatory
for multi configuration build systems, like MSVC.


## Build and install MdtApplication on Windows MinGW

Open a terminal that has gcc and mingw32-make in the PATH.

Create a build directory and go to it:
```bash
mkdir build
cd build
```

Install the required dependencies:
```bash
conan install --profile windows_gcc7_x86_64 -s build_type=Release --build=missing ..
```

Configure the project:
```bash
cmake -G"MinGW Makefiles" -DCMAKE_INSTALL_PREFIX=C:\some\path -DQT_PREFIX_PATH="C:\Qt\5.13\mingw73_64" -DCMAKE_BUILD_TYPE=Release ..
cmake-gui .
```

If `QT_PREFIX_PATH` was not specified, and no Qt5 installation is in the `PATH`,
a error will probably occur, telling that Qt was not found.
Set the `QT_PREFIX_PATH` by choosing the path to the Qt5 installation,
then run "Configure".

Also choose different options, like the components to build.
Once done, run "Generate", then quit cmake-gui.

Compile:
```bash
mingw32-make -j4
```

To run the tests:
```bash
ctest --output-on-failure -j4 .
```

Install:
```bash
mingw32-make install
```

## Build and install MdtApplication on Windows MSVC

Create a build directory and go to it:
```bash
mkdir build
cd build
```

Install the required dependencies:
```bash
conan install --profile windows_msvc15_x86_64 -s build_type=Release --build=missing ..
```

Configure:
```cmd
cmake -G "Visual Studio 15 2017 Win64" -DCMAKE_INSTALL_PREFIX=C:\some\path -DQT_PREFIX_PATH="C:\Qt\5.13\msvc2017_64"  ..
cmake-gui .
```

TODO: check "Visual Studio 15 2017 Win32"

To generate the tests, run the build:
```bash
cmake --build . --config Release
```

To run the tests:
```bash
ctest --output-on-failure -C Release -j4 .
```

Install:
```cmd
cmake --build . --target INSTALL --config Release
```

# Work on MdtApplication

## Build

See [BUILD](BUILD.md).

## Create Conan package

See [README](packaging/conan/README.md) in the conan packaging folder.


# Create a Conan package

The package version is picked up from git tag.
If working on MdtApplication, go to the root of the source tree:
```bash
git tag x.y.z
conan create . scandyna/testing --profile $CONAN_PROFILE -s build_type=$BUILD_TYPE
```

To create a package with a explicit version,
go out of the source tree:
```bash
git tag x.y.z
conan create path/to/MdtApplication/source/ x.y.z@scandyna/testing --profile $CONAN_PROFILE -s build_type=$BUILD_TYPE
```

Above examples will generate a package that uses the Qt version that is installed on the system,
or passed to the `CMAKE_PREFIX_PATH` of your build.

To create packages that depend on Conan Qt:
```bash
conan create . scandyna/testing -o MdtApplication:use_conan_qt=True
```

Because Qt offers binary compatibility,
it should not be required to create package for each minor Qt version,
but more a package per compiler and other things that breaks binary compatibility.
