[[_TOC_]]

# Build MdtApplication

This section describes how to build
to work on MdtApplication.

The examples use the command line.
Because CMake is supported natively by some IDE's,
using those should be relatively easy.

## Required tools and libraries

Some tools are required to build MdtApplication:
 - Git
 - Conan
 - CMake
 - Make (can be other, like Ninja)
 - C++ compiler (like Gcc or Clang or MSVC)

Additional tools are required to generate the documentation:
 - Doxygen

For a overview how to install them, see https://gitlab.com/scandyna/build-and-install-cpp

Tools and libraries that are managed by Conan:
 - [Catch2](https://github.com/catchorg/Catch2)
 - Qt
 - [MdtCMakeModules](https://gitlab.com/scandyna/mdt-cmake-modules)


## Get the source code

Get the sources:
```bash
git clone https://gitlab.com/scandyna/mdtapplication.git
```

Create a build directory and cd to it:
```bash
mkdir build
cd build
```

## Install the dependencies

The recommended way is to use Conan to install the dependencies.
The examples are based on that.

See also some Conan specific informations,
like using profiles and options, in the [README](README.md).

### Note about conan and new generators

Below examples are based on the new generators,
like CMakeDeps, CMakeToolchain and VirtualBuildEnv.

Some of those recommend to specify the build and host profile:
```bash
conan install --profile:build $CONAN_PROFILE --profile:host $CONAN_PROFILE -s build_type=$BUILD_TYPE --build=missing ..
```

Currently, specify both profiles can fail for some packages.

Also, for simplicity, the examples will specify a single profile
for native builds (not cross-compilation):
```bash
conan install --profile $CONAN_PROFILE -s build_type=$BUILD_TYPE --build=missing ..
```

The new CMakeToolchain generator creates a `conan_toolchain.cmake` which will be passed to CMake:
```bash
cmake -DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake ..
```
This will set some flags, like `CMAKE_CXX_FLAGS_INIT`
and also the `CMAKE_BUILD_TYPE` (for non multi-config CMake generators).

Note: the compiler (like `CMAKE_CXX_COMPILER`) is not set in the generated toolchain file.
See also: https://github.com/conan-io/conan/issues/9962

The compiler is specified in the profiles, in a new (undocumented ?) buildenv section:
```conan
[buildenv]
CC=gcc-7
CXX=g++-7
```

To build (or at least generate the build system) using the correct compiler,
we have to get this information.
Here comes the conan VirtualBuildEnv, which generates somes scripts, like `conanbuild.sh`.

On UNIX like system, the workflow looks like:
```bash
conan install ...
source conanbuild.sh
cmake ...
source deactivate_conanbuild.sh
```
and on Windows:
```bash
conan install ...
.\conanbuild
cmake ...
.\deactivate_conanbuild
```

## Configure MdtApplication

This is a example on Linux using gcc.

Install the dependencies:
```bash
conan install --profile linux_gcc7_x86_64_qt_widgets_modules -s build_type=Debug --build=missing ..
```

Configure MdtApplication:
```bash
source conanbuild.sh
cmake -DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake -DBUILD_TESTS=ON ..
cmake-gui .
```

## Configure and build with ASan and UBSan

Install the dependencies:
```bash
conan install --profile linux_gcc7_x86_64_qt_widgets_modules -s build_type=Debug --build=missing ..
```

Configure MdtApplication:
```bash
source conanbuild.sh
cmake -DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake -DBUILD_TESTS=ON -DSANITIZER_ENABLE_ADDRESS=ON -DSANITIZER_ENABLE_UNDEFINED=ON ..
cmake-gui .
```

## Configure and build with Clang and libc++

Install the dependencies:
```bash
conan install --profile linux_clang6.0_x86_64_libc++_qt_widgets_modules -s build_type=Debug --build=missing ..
```

Configure MdtApplication:
```bash
source conanbuild.sh
cmake -DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake -DBUILD_TESTS=ON ..
cmake-gui .
```

## Configure and build with ThreadSanitizer

Gcc supports ThreadSanitizer, but Clang seems to give less false positive.
This is what I experieced on Ubuntu 18.04 with those default compilers.

Install the dependencies:
```bash
conan install --profile linux_clang6.0_x86_64_libc++_tsan_qt_widgets_modules -s build_type=Debug --build=missing ..
```

Configure MdtApplication:
```bash
source conanbuild.sh
cmake -DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake -DBUILD_TESTS=ON -DSANITIZER_ENABLE_THREAD=ON ..
cmake-gui .
```

## Build and run the tests

Those examples use cmake to run the build,
which should work everywhere.

Build:
```bash
cmake --build . --config Debug -j4
```

To run the tests:
```bash
ctest . --output-on-failure -C Debug -j4
```

## Restore your environment

On Unix:
```bash
source deactivate_conanbuild.sh
```
On Windows:
```bash
.\deactivate_conanbuild
```
