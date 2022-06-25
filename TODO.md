
# CMake

Should sepcify LANGUAGES CXX in project()

Try conan build requires
cmake_installer[>=3.14]@conan/stable

Also update README (activate)

Note: this should not affect when used as installed library

# Conant install

Document how to specify options,
like gui, use_conan_qt,
in the caller conanfile.txt/py

Maybe we end up with a top level conanfile.[txt|py]
to install dependencies to work on the project,
then 1 conanfile.py per library ?

# CI

Use new docker images

# Optimisation

Should add BUILD_USE_IPO_LTO_IF_AVAILABLE in CMakeLists.txt and turn it ON in conanfile.py
See CppProjectTemplate
