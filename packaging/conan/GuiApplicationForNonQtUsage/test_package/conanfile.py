from conans import ConanFile, tools
from conan.tools.cmake import CMake, CMakeToolchain
import os

class MdtGuiApplicationForNonQtUsageTest(ConanFile):
  settings = "os", "compiler", "build_type", "arch"
  generators = "CMakeDeps"

  def build_requirements(self):
    self.tool_requires("MdtCMakeModules/0.19.1@scandyna/testing", force_host_context=True)

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
