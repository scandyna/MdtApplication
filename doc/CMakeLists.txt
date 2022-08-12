# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

########################
# CMake dependency graph
########################

# This variable is also used in the Doxygen.in files
set(DOT_FILES_CMAKE_DIR "${CMAKE_CURRENT_BINARY_DIR}/dotfiles/cmake")

file(MAKE_DIRECTORY "${DOT_FILES_CMAKE_DIR}")

add_custom_command(
    OUTPUT cmake-dependency-graph
    COMMAND "${CMAKE_COMMAND}" --graphviz=CMakeDependencyGraph.dot "${PROJECT_BINARY_DIR}"
#     COMMAND dot -Tsvg CMakeDependencyGraph.dot -o CMakeDependencyGraph.svg
    COMMENT "Build CMake dependency graph"
    VERBATIM
    WORKING_DIRECTORY "${DOT_FILES_CMAKE_DIR}"
)
set_property(SOURCE cmake-dependency-graph PROPERTY SYMBOLIC 1)



#######################
# C++ API doc
#######################

configure_file(
  "${PROJECT_SOURCE_DIR}/doc/Doxyfile.in"
  "${PROJECT_BINARY_DIR}/doc/Doxyfile"
)

add_custom_command(
    OUTPUT cpp-api-doc
    COMMAND
      Doxygen::doxygen "${PROJECT_BINARY_DIR}/doc/Doxyfile"
    COMMENT "Build C++ API doc"
    VERBATIM
)
set_property(SOURCE cpp-api-doc PROPERTY SYMBOLIC 1)
add_custom_target(CppApiDoc ALL DEPENDS cpp-api-doc)

############################
# documentation meta target
############################

add_custom_target(documentation ALL DEPENDS cmake-dependency-graph cpp-api-doc)
