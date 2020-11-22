from conans import ConanFile, CMake
import os

class MdtApplicationTest(ConanFile):
  settings = "os", "compiler", "build_type", "arch"
  generators = "cmake_paths"
  build_requires = "MdtCMakeModules/[>=0.14.12]@scandyna/testing"

  def configure_cmake(self):
    cmake = CMake(self)

    cmake.definitions["CMAKE_TOOLCHAIN_FILE"] = "%s/conan_paths.cmake" % (self.build_folder)

    return cmake

  def build(self):
      cmake = self.configure_cmake()
      cmake.configure()
      cmake.build()

  def test(self):
      cmake = self.configure_cmake()
      cmake.test()

