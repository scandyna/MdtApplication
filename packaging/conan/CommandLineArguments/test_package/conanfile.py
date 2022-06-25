from conans import ConanFile, CMake, tools
import os

class MdtCommandLineArgumentsTest(ConanFile):
  settings = "os", "compiler", "build_type", "arch"
  generators = "cmake"
  #build_requires = "MdtCMakeModules/0.17.1@scandyna/testing"

  def build_requirements(self):
    self.tool_requires("MdtCMakeModules/0.18.0@scandyna/testing", force_host_context=True)

  def _configure_cmake(self):
    cmake = CMake(self)

    return cmake


  def build(self):
    cmake = self._configure_cmake()
    cmake.configure()
    cmake.build()

  def test(self):
    cmake = self._configure_cmake()
    cmake.test()
