from conans import ConanFile, tools
from conan.tools.cmake import CMakeToolchain, CMakeDeps, CMake
#from conan.tools.env import VirtualBuildEnv
import os

class MdtCommandLineArgumentsConan(ConanFile):
  name = "MdtConsoleApplication"
  license = "BSD 3-Clause"
  url = "https://gitlab.com/scandyna/mdtapplication"
  description = "Helpers to create console application with Qt"
  settings = "os", "compiler", "build_type", "arch"
  generators = "CMakeDeps", "VirtualBuildEnv"
  # If no_copy_source is False, conan copies sources to build directory and does in-source build,
  # resulting having build files installed in the package
  # See also: https://github.com/conan-io/conan/issues/350
  no_copy_source = True

