from conan import ConanFile
from conan.tools.cmake import CMakeToolchain, CMakeDeps, CMake

class MdtGuiApplicationForNonQtUsageTest(ConanFile):
  settings = "os", "compiler", "build_type", "arch"
  generators = "CMakeDeps"

  def requirements(self):
    self.requires(self.tested_reference_str)

  def build_requirements(self):
    self.test_requires("mdtcmakemodules/0.20.0@scandyna/testing")

  def generate(self):
    tc = CMakeToolchain(self)
    tc.variables["CMAKE_MESSAGE_LOG_LEVEL"] = "DEBUG"
    tc.generate()

  def build(self):
    cmake = CMake(self)
    cmake.configure()
    cmake.build()

  def test(self):
    cmake = CMake(self)
    cmake.test()
