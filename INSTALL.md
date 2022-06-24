[[_TOC_]]

# Install MdtApplication

Get MdtApplication:
```bash
git clone git@gitlab.com:scandyna/mdtapplication.git
```

Create a build directory and cd to it:
```bash
mkdir build
cd build
```

## Required tools and libraries

Some tools and libraries are required to build and MdtApplication:
 - Git
 - CMake
 - Conan (optional)
 - A compiler (Gcc or Clang or MSVC)
 - Make (optional)
 - Qt5

For a overview how to install them, see https://gitlab.com/scandyna/build-and-install-cpp

Some Mdt tools and libraries are also required:
 - [MdtCMakeConfig](https://gitlab.com/scandyna/mdtcmakeconfig)
 - [MdtCMakeModules](https://gitlab.com/scandyna/mdt-cmake-modules)

See the project repository for each of them to install those.

## Note about install prefix

Some note on the `CMAKE_INSTALL_PREFIX`:
 - To target a system wide installation on Linux, set it to `/usr` (`-DCMAKE_INSTALL_PREFIX=/usr`) .
 - For other locations, spcecify also the `<package-name>`, (for example `-DCMAKE_INSTALL_PREFIX=~/opt/MdtApplication`).

For details about that, see:
 - https://scandyna.gitlab.io/mdt-cmake-modules/Modules/MdtInstallDirs.html
 - https://cmake.org/cmake/help/latest/variable/CMAKE_INSTALL_PREFIX.html
 - https://scandyna.gitlab.io/mdt-cmake-modules/Modules/MdtInstallLibrary.html

## Configure MdtApplication

Configure MdtApplication:
```bash
cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=/some/path/MdtApplication -DCMAKE_PREFIX_PATH="/some/path/MdtApplication;/some/path/MdtCMakeConfig;/some/path/MdtCMakeModules;/some/path/qt/Qt5/5.15.2/gcc_64" ..
cmake-gui .
```

For more details, see also [BUILD](BUILD.md).

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
cmake -G"MinGW Makefiles" -DCMAKE_INSTALL_PREFIX=C:\some\path\MdtApplication -DQT_PREFIX_PATH="C:\Qt\5.13\mingw73_64" -DCMAKE_PREFIX_PATH="C:\some\path\MdtApplication;C:\some\path\MdtCMakeConfig;C:\some\path\MdtCMakeModules" -DCMAKE_BUILD_TYPE=Release ..
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
cmake -G"Visual Studio 15 2017 Win64" -DCMAKE_INSTALL_PREFIX=C:\some\path\MdtApplication -DQT_PREFIX_PATH="C:\Qt\5.13\msvc2017_64" -DCMAKE_PREFIX_PATH="C:\some\path\MdtApplication;C:\some\path\MdtCMakeConfig;C:\some\path\MdtCMakeModules" -DCMAKE_BUILD_TYPE=Release ..
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
