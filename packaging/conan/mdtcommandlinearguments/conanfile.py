from conan import ConanFile
from conan.tools.cmake import CMakeToolchain, CMakeDeps, CMake, cmake_layout
from conan.tools.files import copy
import os

class MdtCommandLineArgumentsConan(ConanFile):
  name = "mdtcommandlinearguments"
  license = "BSD 3-Clause"
  url = "https://gitlab.com/scandyna/mdtapplication"
  description = "Helper class to init and copy command line arguments"
  # We use CMake to configure/build/(test)/install
  # We also have dependencies we manage with Conan
  # We then use CMakeDeps and CMakeToolchain generators.
  # This requires the settings.
  # We will remove them in the package_id()
  # See: https://docs.conan.io/2/tutorial/creating_packages/other_types_of_packages/header_only_packages.html
  settings = "os", "compiler", "build_type", "arch"
  generators = "CMakeDeps", "VirtualBuildEnv"

  # The version can be set on the command line:
  # conan create . x.y.z@scandyna/testing ...
  # It can also be set by a git tag (case of deploy in the CI/CD)
  # The version should usually not be revelant when installing dependencies to build this project:
  # conan install path/to/srouces ...
  # But it can be required. See https://docs.conan.io/en/latest/reference/conanfile/attributes.html#version
  def set_version(self):
    #if not self.version:
      #if os.path.exists(".git"):
        #git = tools.Git()
        #self.version = "%s" % (git.get_tag())
      #else:
        #self.version = "0.0.0"
    self.output.info( "%s: version is %s" % (self.name, self.version) )

  def requirements(self):
    self.requires("mdtcmakeconfig/0.1.0@scandyna/testing")

  def build_requirements(self):
    self.test_requires("MdtCMakeModules/0.19.3@scandyna/testing")

  def export_sources(self):
    source_root = os.path.join(self.recipe_folder, "../../../")
    copy(self, "CMakeLists.txt", source_root, self.export_sources_folder)
    copy(self, "COPYING", source_root, self.export_sources_folder)
    copy(self, "COPYING.LESSER", source_root, self.export_sources_folder)
    copy(self, "libs/CommandLineArguments/*", source_root, self.export_sources_folder)

  def layout(self):
    cmake_layout(self)

  def generate(self):
    tc = CMakeToolchain(self)
    tc.variables["FROM_CONAN_PROJECT_VERSION"] = self.version
    tc.variables["ENABLE_CORE_APPLICATION_FOR_NON_QT_USAGE"] = "OFF"
    tc.variables["ENABLE_GUI_APPLICATION_FOR_NON_QT_USAGE"] = "OFF"
    tc.variables["ENABLE_COMMAND_LINE_ARGUMENTS"] = "ON"
    tc.variables["ENABLE_CONSOLE_APPLICATION"] = "OFF"
    #tc.variables["INSTALL_CONAN_PACKAGE_FILES"] = "ON"
    tc.generate()

  def build(self):
    cmake = CMake(self)
    cmake.configure()
    cmake.build()

  def package(self):
    cmake = CMake(self)
    cmake.install()

  def package_id(self):
    self.info.clear()

  def package_info(self):
    self.cpp_info.bindirs = []
    self.cpp_info.libdirs = []
    self.cpp_info.includedirs = ['include']
    self.cpp_info.libs = []
    self.cpp_info.set_property("cmake_file_name", "Mdt0CommandLineArguments")
    self.cpp_info.set_property("cmake_target_name", "Mdt0::CommandLineArguments")
