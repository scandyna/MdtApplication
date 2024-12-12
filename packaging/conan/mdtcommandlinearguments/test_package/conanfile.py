from conan import ConanFile
from conan.tools.cmake import CMakeToolchain, CMake

class MdtCommandLineArgumentsTest(ConanFile):
  settings = "os", "compiler", "build_type", "arch"
  generators = "CMakeToolchain", "CMakeDeps"

  def requirements(self):
    self.requires(self.tested_reference_str)

  def build_requirements(self):
    self.test_requires("mdtcmakemodules/0.20.0@scandyna/testing")

  # source() and export_source() are not called
  #def layout(self):
    #cmake_layout(self, src_folder="../test_package")

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
