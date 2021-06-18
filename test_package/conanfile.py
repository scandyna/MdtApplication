from conans import ConanFile, CMake
import os

class MdtApplicationTest(ConanFile):
  settings = "os", "compiler", "build_type", "arch"
  generators = "cmake"
  build_requires = "MdtCMakeModules/[>=0.14.12]@scandyna/testing"

  def configure_cmake(self):
    cmake = CMake(self)

    if self.settings.compiler == "gcc" or self.settings.compiler == "clang":
      if self.settings.compiler.sanitizer == "Thread":
        cmake.definitions["SANITIZER_ENABLE_THREAD"] = "ON"
        cmake.definitions["OPTIMIZATION_LEVEL_OPTION"] = "-O1"

    return cmake

  def build(self):
      cmake = self.configure_cmake()
      cmake.configure()
      cmake.build()

  def test(self):
      cmake = self.configure_cmake()
      cmake.test()

