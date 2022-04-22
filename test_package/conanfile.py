from conans import ConanFile, CMake, tools
from conan.tools.cmake import CMakeToolchain
from conan.tools.cmake import CMakeDeps
import os

class MdtApplicationTest(ConanFile):
  settings = "os", "compiler", "build_type", "arch"
  generators = "cmake"
  build_requires = "MdtCMakeModules/[>=0.14.12]@scandyna/testing"


  def _generate_with_CMakeToolChain_generator(self):
    tools.mkdir("CMakeToolChain_generator")
    with tools.chdir("CMakeToolChain_generator"):
      self.output.info("Generating with CMakeToolchain and CMakeDeps generators")
      tc = CMakeToolchain(self)
      tc.generate()
      deps = CMakeDeps(self)
      deps.generate()


  def _configure_cmake(self):
    cmake = CMake(self)

    if self.settings.compiler == "gcc" or self.settings.compiler == "clang":
      if self.settings.compiler.sanitizer == "Thread":
        cmake.definitions["SANITIZER_ENABLE_THREAD"] = "ON"
        cmake.definitions["OPTIMIZATION_LEVEL_OPTION"] = "-O1"

    return cmake


  def _build_with_cmake_generator(self):
    self.output.info("Build with cmake generator")
    cmake = self._configure_cmake()
    cmake.configure()
    cmake.build()


  def _build_with_CMakeToolChain_generator(self):
    with tools.chdir("CMakeToolChain_generator"):
      self.output.info("Build with CMakeToolchain and CMakeDeps generators")
      cmake = self._configure_cmake()
      cmake.configure()
      cmake.build()


  def generate(self):
    self._generate_with_CMakeToolChain_generator()

  def build(self):
    self._build_with_cmake_generator()
    self._build_with_CMakeToolChain_generator()

      #cmake = self._configure_cmake()
      #cmake.configure()
      #cmake.build()

  def test(self):
      cmake = self._configure_cmake()
      cmake.test()
