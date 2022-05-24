[[_TOC_]]

# Build MdtApplication

This section describes how to build
to work on MdtApplication.

The examples use the command line.
Because CMake is supported natively by some IDE's,
using those should be relatively easy.

## Tools ans libraries

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


## Get the source code

Get the sources:
```bash
git clone https://github.com/scandyna/mdt-cmake-modules.git
```

## Required tools and libraries

The dependencies are the same as in previous chapter plus those:
 - [Catch2](https://github.com/catchorg/Catch2)

If you use Conan, nothing has to be installed explicitely.
Otherwise, see the documentation of the dependencies.

## Configure MdtApplication

Install the dependencies:
```bash
conan install -s build_type=RelWithDebInfo --build=missing ..
```

Configure MdtApplication:
```bash
cmake -DCMAKE_BUILD_TYPE=RelWithDebInfo -DBUILD_TESTS=ON ..
cmake-gui .
```

## Configure and build with ASan and UBSan

Install the dependencies:
```bash
conan install -s build_type=RelWithDebInfo --build=missing ..
```

Configure MdtApplication:
```bash
cmake -DCMAKE_BUILD_TYPE=Instrumented -DBUILD_TESTS=ON ..
cmake-gui .
```

Set the various options, like `BUILD_TYPE_INSTRUMENTED_OPTIMIZATION_LEVEL`,
`BUILD_TYPE_INSTRUMENTED_USE_DEBUG_SYMBOLS` and `BUILD_TYPE_INSTRUMENTED_DEFINE_NDEBUG`.

Build:
```bash
cmake --build . --config Instrumented
```
or:
```bash
make -j4
```

To run the tests:
```bash
ctest . --output-on-failure -C Instrumented -j4
```

## Configure and build with Clang and libc++

On Linux, the default compiler is probably gcc.

To choose the correct compiler (and maybe other flags),
Conan generates a script that can setup a build environment.

The steps will be something like this:
```bash
conan install --profile linux_clang6.0_x86_64_libc++_qt_widgets_modules -s build_type=Release -o MdtApplication:use_conan_qt=True --build=missing ..
source activate.sh
cmake -DCMAKE_BUILD_TYPE=Release -DBUILD_TESTS=ON ..
cmake-gui .
cmake --build . --config Release
ctest . --output-on-failure -C Release
source deactivate.sh
```

## Configure and build with ThreaSanitizer

Gcc supports ThreaSanitizer, but Clang seems to give less false positive.
This is what I experieced on Ubuntu 18.04 with those default compilers.

To build with TSan:
```bash
conan install --profile linux_clang6.0_x86_64_libc++_tsan_qt_widgets_modules -s build_type=RelWithDebInfo -o MdtApplication:use_conan_qt=True --build=missing ..
source activate.sh
cmake -DCMAKE_BUILD_TYPE=Instrumented -DBUILD_TESTS=ON -DSANITIZER_ENABLE_THREAD=ON ..
cmake-gui .
cmake --build . --config Instrumented
ctest . --output-on-failure -C Instrumented
source deactivate.sh
```
