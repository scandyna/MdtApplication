[[_TOC_]]

# Use MdtApplication Conan packages

Below is a list of available packages for the various components of MdtApplication.

Note that only the [CMakeDeps](https://docs.conan.io/en/latest/reference/conanfile/tools/cmake/cmakedeps.html)
generator, and its associated tools is supported.
This is mainly because the Qt package from [Conan center](https://conan.io/center/) is used,
which does not support the legacy generators like [cmake](https://docs.conan.io/en/latest/reference/generators/cmake.html).
For more details, see [Conan and CMake](https://scandyna.gitlab.io/mdt-cmake-modules/ConanAndCMake.html).

You may want to use a official [Qt distribution](https://www.qt.io/download) for your prjects.
In that case, the `use_conan_qt` option can be used:
```bash
conan <command> ... -o $PACKAGE:use_conan_qt=False ...
```

Example to install the dependencies using the GuiApplicationForNonQtUsage component:
```bash
conan install .. --profile your_profile -s build_type=Debug -o MdtGuiApplicationForNonQtUsage:use_conan_qt=False
```

In such case, you have to care yourself to use the same qt distribution (arch, version, etc..)
for each part of your projects.

## CoreApplicationForNonQtUsage

Conanfile:
```conan
[requires]
MdtCoreApplicationForNonQtUsage/x.y.z@scandyna/testing
```

Options:
| Option           | Default | Possible Values  | Explanations |
|------------------|:------- |:----------------:|--------------|
| shared           | True    |  [True, False]   | Build as shared library |
| use_conan_qt     | True    |  [True, False]   | Use [conan Qt](https://conan.io/center/qt) as conan dependency |

## GuiApplicationForNonQtUsage

Conanfile:
```conan
[requires]
MdtGuiApplicationForNonQtUsage/x.y.z@scandyna/testing
```

Options:
| Option           | Default | Possible Values  | Explanations |
|------------------|:------- |:----------------:|--------------|
| shared           | True    |  [True, False]   | Build as shared library |
| use_conan_qt     | True    |  [True, False]   | Use [conan Qt](https://conan.io/center/qt) as conan dependency |

## ConsoleApplication

Conanfile:
```conan
[requires]
MdtConsoleApplication/x.y.z@scandyna/testing
```

Options:
| Option           | Default | Possible Values  | Explanations |
|------------------|:------- |:----------------:|--------------|
| shared           | True    |  [True, False]   | Build as shared library |
| use_conan_qt     | True    |  [True, False]   | Use [conan Qt](https://conan.io/center/qt) as conan dependency |

## CommandLineArguments

Conanfile:
```conan
[requires]
MdtCommandLineArgumentsn/x.y.z@scandyna/testing
```

Options: none

# Create Conan packages for MdtApplication libraries

TODO: adapt once modularized

The package version is picked up from git tag.
If working on MdtApplication, go to the root of the source tree:
```bash
git tag x.y.z
conan create packaging/conan/$LIBRARY scandyna/testing --profile $CONAN_PROFILE -s build_type=$BUILD_TYPE
```

To create a package without having a git tag:
```bash
conan create packaging/conan/$LIBRARY x.y.z@scandyna/testing --profile $CONAN_PROFILE -s build_type=$BUILD_TYPE
```

# Rationale

## use_conan_qt option

I had put a option to use Conan packages for my projects that do not depend on Conan Qt packages.

This was because using Conan Qt was a pain.

### Earlier problems

Building Conan Qt packages mostly failed, at least if Qt Widgets are required.

I didn't find a Conan package registry that accepts big packages like Qt.
Bintray (now dead), accepted some Mo, but Qt with Qt Widgets was to big.
GitLab started to develop a Conan package registry, but initially only accepted 50Mo, far to less for Qt.

### Earlier workaround

Using the [cmake](https://docs.conan.io/en/latest/reference/generators/cmake.html),
all worked by adding dependencies to the `CMAKE_PREFIX_PATH` and using upstream CMake package config files.

All seemed to work, because I allways used the same Qt distribution (on my machine, on the CI).

One day, I had compile errors, thaks to Qt, that checks versions.

### Current status

A lots of work has been done to the Qt Conan recipe.

It's now available on [Conan center](https://conan.io/center/),
and it build on Linux (Gcc and Clang)
and on Windows with MSVC.

Currently, it does not build on Windows with Gcc (MinGW).

GitLab's Conan package registry now accepts Qt packages, which is great.
Despite some bugs, like version ranges, remote query, all works fine.

### Current rationale with modern Conan

Using packages from [Conan center](https://conan.io/center/)
requires to use modern CMake generators,
like [CMakeDeps](https://docs.conan.io/en/latest/reference/conanfile/tools/cmake/cmakedeps.html).

Now Conan generates the CMake package config files, which is more robust.
But now, the earlier workaround does not work anymore.

For more details, see [Conan and CMake](https://scandyna.gitlab.io/mdt-cmake-modules/ConanAndCMake.html).

Thinking about how to hack `package_info()` in the `conanfile.py`,
I understood that the `use_conan_qt` is just a bad idea.

Either use Conan or don't.

Maybe, in the future, I would provide some debian packages,
which will probably make me think more about package management.
