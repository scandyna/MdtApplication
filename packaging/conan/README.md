[[_TOC_]]

# Use MdtApplication Conan packages

Below is a list of available packages for the various components of MdtApplication.

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
