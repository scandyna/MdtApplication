from conans import ConanFile, tools
from conan.tools.cmake import CMake, CMakeToolchain, cmake_layout
import os

class MdtCommandLineArgumentsTest(ConanFile):
  settings = "os", "compiler", "build_type", "arch"
  generators = "CMakeToolchain", "CMakeDeps"

  def build_requirements(self):
    self.tool_requires("MdtCMakeModules/0.18.3@scandyna/testing", force_host_context=True)

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
