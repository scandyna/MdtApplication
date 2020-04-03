# MdtApplication

Some additions for QCoreApplication, QGuiApplication and QApplication.

This project is composed of some libraries:

| Library                      | Description                                         | Main dependency |
|------------------------------|:----------------------------------------------------|-----------------|
| CoreApplicationForNonQtUsage | Provide a QCoreApplication for a non Qt application | QtCore          |
| GuiApplicationForNonQtUsage  | Provide a QGuiApplication for a non Qt application  | QtGui           |

# Usage

For the available classes, functions, and their usage,
see [the API documentation](https://scandyna.gitlab.io/mdtapplication)

## Required tools and libraries

Some tools and libraries are required to use MdtUicNumber:
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
cmake_minimum_required(VERSION 3.10)
project(MyApp)

find_package(Threads REQUIRED)
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
| gui              | False   |  [True, False]   | Include the libraries that depends on QtGui |
| use_conan_qt     | False   |  [True, False]   | Use [conan Qt](https://github.com/bincrafters/conan-qt) as conan dependency |
| build_tests      | False   |  [True, False]   | If True, will also require Catch2 |



In your source directory, create a `conanfile.txt`:
```conan
[requires]
MdtApplication/x.y.z@scandyna/testing

[generators]
cmake_paths

[options]
MdtApplication:gui=True
```

Create a build directory and cd to it:
```bash
mkdir build
cd build
```

Install the dependencies:
```bash
conan install -s build_type=Release --build=missing ..
```

Configure your project:
```bash
cmake -DCMAKE_TOOLCHAIN_FILE=conan_paths.cmake -DCMAKE_BUILD_TYPE=Release ..
cmake-gui .
```
