# MdtApplication

[![latest pipeline status](https://gitlab.com/scandyna/mdtapplication/badges/experimental/pipeline.svg)](https://gitlab.com/scandyna/mdtapplication/-/pipelines/latest)
[List of commits and CI pipeline status](https://gitlab.com/scandyna/mdtapplication/-/commits/experimental)

Some additions for QCoreApplication, QGuiApplication and QApplication.

This library is composed of some components:

| Component                    | Description                                          | Main dependency |
|------------------------------|:-----------------------------------------------------|-----------------|
| CoreApplicationForNonQtUsage | Provide a QCoreApplication for a non Qt application  | QtCore          |
| GuiApplicationForNonQtUsage  | Provide a QGuiApplication for a non Qt application   | QtGui           |
| ConsoleApplication           | Helpers to create console application with Qt        | QtCore          |
| CommandLineArguments         | Helper class to init and copy command line arguments | None            |

# Usage

This example will use ConsoleApplication.
The principle is the same for the other components.

For the usage of classes and functions for all components,
see [the API documentation](https://scandyna.gitlab.io/mdtapplication)

## CMake project description

Update your CMakeLists.txt to use the required libraries:
```cmake
cmake_minimum_required(VERSION 3.15)
project(MyApp)

find_package(Threads REQUIRED)
find_package(Qt5 REQUIRED COMPONENTS Core)
find_package(Mdt0 REQUIRED COMPONENTS ConsoleApplication )

add_executable(myApp myApp.cpp)
target_link_libraries(myApp Mdt0::ConsoleApplication)
```

## Project using Conan

If you use [Conan](https://conan.io/),
add MdtConsoleApplication as requirement in your `conanfile.txt`:
```conan
[requires]
MdtConsoleApplication/x.y.z@scandyna/testing

[generators]
CMakeDeps
CMakeToolchain
VirtualBuildEnv
```

Add the remote:
```bash
conan remote add gitlab https://gitlab.com/api/v4/projects/25668674/packages/conan
```

Install the dependencies:
```bash
mkdir build && cd build
conan install .. --profile your_profile -s build_type=Debug
```

If you don't use the native compiler,
and your Conan profile defines one
(or it defines some other environments),
bring the required environment to the current shell:
```bash
source conanbuild.sh
```
On Windows:
```bash
.\conanbuild.bat
```

Configure your project:
```bash
cmake -DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake ..
```

Maybe adjust some settings:
```bash
cmake-gui .
```

Build:
```bash
cmake --build . --config Debug
```

To run the tests:
```bash
ctest --output-on-failure -C Debug -j4 .
```

If applicable, restore the previous shell environment:
```bash
source deactivate_conanbuild.sh
```
On Windows:
```bash
.\deactivate_conanbuild.bat
```

For a list of available packages, and also some other details,
see [Conan packages README](packaging/conan/README.md).

## Manual install

It is also possible to install MdtApplication locally.
See [INSTALL](INSTALL.md).

Then, configure your project and specify
the path of the installed MdtApplication and the dependencies:
```bash
cmake -DCMAKE_PREFIX_PATH="/some/path/MdtApplication;/some/path/MdtCMakeConfig;/some/path/MdtCMakeModules;/some/path/qt/Qt5/5.15.2/gcc_64" ..
```

# Work on MdtApplication

## Build

See [BUILD](BUILD.md).

## Create Conan package

See [README](packaging/conan/README.md) in the conan packaging folder.
