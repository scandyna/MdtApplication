from conan import ConanFile
from conan.tools.cmake import CMakeToolchain, CMakeDeps, CMake, cmake_layout
from conan.tools.files import copy
import os

class MdtConsoleApplicationConan(ConanFile):
  name = "mdtconsoleapplication"
  license = "BSD 3-Clause"
  url = "https://gitlab.com/scandyna/mdtapplication"
  description = "Helpers to create console application with Qt"
  settings = "os", "compiler", "build_type", "arch"
  options = {"shared": [True, False]}
  default_options = {"shared": True}
  generators = "CMakeDeps", "VirtualBuildEnv"

  # See: https://docs.conan.io/en/latest/reference/conanfile/attributes.html#short-paths
  short_paths = True

  # The version can be set on the command line:
  # conan create . x.y.z@scandyna/testing ...
  # It can also be set by a git tag (case of deploy in the CI/CD)
  # The version should usually not be revelant when installing dependencies to build this project:
  # conan install path/to/srouces ...
  # But it can be required. See https://docs.conan.io/en/latest/reference/conanfile/attributes.html#version
  def set_version(self):
    if not self.version:
      if os.path.exists(".git"):
        git = tools.Git()
        self.version = "%s" % (git.get_tag())
      else:
        self.version = "0.0.0"
    self.output.info( "%s: version is %s" % (self.name, self.version) )

  def requirements(self):
    self.requires("mdtcmakeconfig/0.1.0@scandyna/testing")
    self.requires("qt/5.15.6")

  def build_requirements(self):
    self.test_requires("MdtCMakeModules/0.19.3@scandyna/testing")

  def export_sources(self):
    source_root = os.path.join(self.recipe_folder, "../../../")
    copy(self, "CMakeLists.txt", source_root, self.export_sources_folder)
    copy(self, "COPYING", source_root, self.export_sources_folder)
    copy(self, "COPYING.LESSER", source_root, self.export_sources_folder)
    copy(self, "libs/ConsoleApplication/*", source_root, self.export_sources_folder)

  def layout(self):
    cmake_layout(self)

  def generate(self):
    tc = CMakeToolchain(self)
    tc.variables["FROM_CONAN_PROJECT_VERSION"] = self.version
    tc.variables["ENABLE_CORE_APPLICATION_FOR_NON_QT_USAGE"] = "OFF"
    tc.variables["ENABLE_GUI_APPLICATION_FOR_NON_QT_USAGE"] = "OFF"
    tc.variables["ENABLE_COMMAND_LINE_ARGUMENTS"] = "OFF"
    tc.variables["ENABLE_CONSOLE_APPLICATION"] = "ON"
    #tc.variables["INSTALL_CONAN_PACKAGE_FILES"] = "ON"
    tc.generate()

  def build(self):
    cmake = CMake(self)
    cmake.configure()
    cmake.build()

  def package(self):
    cmake = CMake(self)
    cmake.install()

  # Use the default package_id()
  # https://docs.conan.io/en/latest/creating_packages/define_abi_compatibility.html#define-abi-compatibility

  def package_info(self):
    self.cpp_info.set_property("cmake_file_name", "Mdt0ConsoleApplication")
    self.cpp_info.set_property("cmake_target_name", "Mdt0::ConsoleApplication")
    # We have to specify the components of Qt to use, otherwise we will depend on all
    # See also https://gitlab.com/scandyna/mdtapplication/-/issues/4
    self.cpp_info.requires = ["qt::qtCore"]
    self.cpp_info.libs = ["Mdt0ConsoleApplication"]
