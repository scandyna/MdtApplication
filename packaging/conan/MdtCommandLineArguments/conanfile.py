from conans import ConanFile, tools
from conan.tools.cmake import CMakeToolchain, CMakeDeps, CMake
#from conan.tools.env import VirtualBuildEnv
import os

class MdtCommandLineArgumentsConan(ConanFile):
  name = "MdtCommandLineArguments"
  license = "BSD 3-Clause"
  url = "https://gitlab.com/scandyna/mdtapplication"
  description = "Helper class to init and copy command line arguments"
  # CMakeToolchain requires the settings.
  # So, add them here and erase them in the package_id()
  # TODO: is it CMakeToolchain or CMakeDeps  or both ?
  settings = "os", "compiler", "build_type", "arch"
  generators = "CMakeDeps", "VirtualBuildEnv"
  # If no_copy_source is False, conan copies sources to build directory and does in-source build,
  # resulting having build files installed in the package
  # See also: https://github.com/conan-io/conan/issues/350
  no_copy_source = True

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
    self.requires("MdtCMakeConfig/0.0.5@scandyna/testing")

  # When using --profile:build xx and --profile:host xx ,
  # the dependencies declared in build_requires and tool_requires
  # will not generate the required files.
  # see:
  # - https://github.com/conan-io/conan/issues/10272
  # - https://github.com/conan-io/conan/issues/9951
  def build_requirements(self):
    # TODO fix once issue solved
    # Due to a issue using GitLab Conan repository,
    # version ranges are not possible.
    # See https://gitlab.com/gitlab-org/gitlab/-/issues/333638
    self.tool_requires("MdtCMakeModules/0.19.1@scandyna/testing", force_host_context=True)

  # The export exports_sources attributes does not work if the conanfile.py is in a sub-folder.
  # See https://github.com/conan-io/conan/issues/3635
  # and https://github.com/conan-io/conan/pull/2676
  def export_sources(self):
    self.copy("CMakeLists.txt", src="../../../", dst=".")
    self.copy("COPYING", src="../../../", dst=".")
    self.copy("COPYING.LESSER", src="../../../", dst=".")
    self.copy("libs/CommandLineArguments/*", src="../../../", dst=".")

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
    self.info.header_only()

  def package_info(self):
    self.cpp_info.includedirs = ['include']
    self.cpp_info.libs = []
    self.cpp_info.set_property("cmake_file_name", "Mdt0CommandLineArguments")
    self.cpp_info.set_property("cmake_target_name", "Mdt0::CommandLineArguments")
    self.cpp_info.requires = ["MdtCMakeConfig::MdtCMakeConfig"]
