
set(GRAPHVIZ_EXTERNAL_LIBS False)

# Using Conan CMakeDeps generator will create some targets
# that are not recognized as external libraries
set(GRAPHVIZ_IGNORE_TARGETS "^[a-z]" "^MdtCMakeModules")
