
# Changelog

See https://github.com/olivierlacan/keep-a-changelog

# Doc / Diagrams

See Consistent architecture diagrams for C++ projects -  Marius Feilhauer - Meeting C++ 2019 (documentation)

Make doc targets/helpers
See MdtDeployUtils

Maybe split:
 - final user doc
 - dependencies

cpp-api-doc
cpp-api-doc-dev ?

## Dependency graph

add_custom_target(DependencyGraph
  COMMAND cmake --graphviz=xxx.dot .
  COMMAND dot -Tsvg xxx.dot -o xxx.svg
  WORKING_DIRECTORY "${CMAKE_BINARY_DIR}"
)

## Doxygen auto

COLLABORATION_GRAPH = YES

INCLUDE_GRAPH
INCLUDED_BY_GRAPH

Those can be used to create manual diagrams,
without to much details.

## Doxygen...

https://doxygen.nl/manual/commands.html:

\dotfile <file> ["caption"] [<sizeindication>=<size>]

\include['{'option'}'] <file-name>

\image['{'option[,option]'}'] <format> <file> ["caption"] [<sizeindication>=<size>]

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

Also update README (activate)

Note: this should not affect when used as installed library

# Conan

Update main conanfile.py
(does not produces packages anymore)

Remove conan gui option

Add sanitizer options / support ?

# Conant install

Document how to specify options,
like gui, use_conan_qt,
in the caller conanfile.txt/py

Maybe we end up with a top level conanfile.[txt|py]
to install dependencies to work on the project,
then 1 conanfile.py per library ?

# CI

See: https://docs.gitlab.com/ee/ci/yaml/index.html#release

Use new docker images

See parallel:
    matrix:
    https://docs.gitlab.com/ee/ci/yaml/
Will probably only work for deploy, because of depends (and needs)

# Optimisation

Should add BUILD_USE_IPO_LTO_IF_AVAILABLE in CMakeLists.txt and turn it ON in conanfile.py
See CppProjectTemplate
