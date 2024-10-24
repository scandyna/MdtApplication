from conan import ConanFile
from conan.tools.cmake import CMakeToolchain, CMakeDeps, CMake

class MdtGuiApplicationForNonQtUsageTest(ConanFile):
  settings = "os", "compiler", "build_type", "arch"
  generators = "CMakeDeps"

  def build_requirements(self):
    self.test_requires("MdtCMakeModules/0.19.3@scandyna/testing")

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
