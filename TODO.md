
# Libs

Q[Core|Gui]AppForNonQtUsage should be forced static libs.
They hold very few code and should be unique per app.
In that case, check to remove some exports if not required.

OR, handle shared libs, but make default to static in Conan recipes ?

SEE: https://gitlab.kitware.com/cmake/cmake/-/issues/18935

# Changelog

See https://github.com/olivierlacan/keep-a-changelog

# Sonar Source

# CMake

Try conan build requires
cmake_installer[>=3.14]@conan/stable

Note: this should not affect when used as installed library

# Conan

Add sanitizer options / support ?

# Optimisation

Should add BUILD_USE_IPO_LTO_IF_AVAILABLE in CMakeLists.txt and turn it ON in conanfile.py
See CppProjectTemplate
