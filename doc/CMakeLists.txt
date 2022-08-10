# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

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
