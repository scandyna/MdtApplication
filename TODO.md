
# Libs

Q[Core|Gui]AppForNonQtUsage should be forced static libs.
They hold very few code and should be unique per app.
In that case, check to remove some exports if not required.

OR, handle shared libs, but make default to static in Conan recipes ?

SEE: https://gitlab.kitware.com/cmake/cmake/-/issues/18935

# Changelog

See https://github.com/olivierlacan/keep-a-changelog

# Doc / Diagrams

See Consistent architecture diagrams for C++ projects -  Marius Feilhauer - Meeting C++ 2019 (documentation)

## Doxygen auto

COLLABORATION_GRAPH = YES

INCLUDE_GRAPH
INCLUDED_BY_GRAPH

Those can be used to create manual diagrams,
without to much details.

## Doxygen...

https://doxygen.nl/manual/commands.html:

## UML manual

PlantUML
-> Also see what packages are reuqired in docker images
   NOTE: create a docker image for docs ? (lighter)

See Doxygen integration

Also, markdown UML file integrated with Doxygen ?

Inline UML in Doxygen ?

# Sonar Source

# CMake

Should sepcify LANGUAGES CXX in project()

Try conan build requires
cmake_installer[>=3.14]@conan/stable


Note: this should not affect when used as installed library

# Conan

Add sanitizer options / support ?

# CI

See: https://docs.gitlab.com/ee/ci/yaml/index.html#release

See parallel:
    matrix:
    https://docs.gitlab.com/ee/ci/yaml/
Will probably only work for deploy, because of depends (and needs)

# Optimisation

Should add BUILD_USE_IPO_LTO_IF_AVAILABLE in CMakeLists.txt and turn it ON in conanfile.py
See CppProjectTemplate
