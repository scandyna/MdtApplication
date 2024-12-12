from conan import ConanFile
from conan.tools.env import VirtualBuildEnv
from conan.tools.cmake import CMakeToolchain, CMakeDeps, CMake
import os

# This recipe is only to install dependencies to build MdtApplication
# The recipes to create packages are in packaging/conan/ subfolder
class MdtApplicationConan(ConanFile):
  name = "mdtapplication"
  #version = "0.1"
  license = "BSD 3-Clause"
  url = "https://gitlab.com/scandyna/mdtapplication"
  description = "Some additions for QCoreApplication, QGuiApplication and QApplication"
  settings = "os", "compiler", "build_type", "arch"
  options = {"shared": [True, False],
             "build_only_doc": [True, False]}
  default_options = {"shared": True,
                     "build_only_doc": False}
  generators = "CMakeDeps", "VirtualBuildEnv"

  # See: https://docs.conan.io/en/latest/reference/conanfile/attributes.html#short-paths
  short_paths = True

  # TODO: has this sense here ?
  # The version can be set on the command line:
  # conan create . x.y.z@scandyna/testing ...
  # It can also be set by a git tag (case of deploy in the CI/CD)
  # The version should usually not be revelant when installing dependencies to build this project:
  # conan install path/to/sources ...
  # But it can be required. See https://docs.conan.io/en/latest/reference/conanfile/attributes.html#version
  def set_version(self):
    if not self.version:
      if os.path.exists(".git"):
        git = tools.Git()
        self.version = "%s" % (git.get_tag())
      else:
        self.version = "0.0.0"
    self.output.info( "%s: version is %s" % (self.name, self.version) )

  def _requires_qt(self):
    #if self.options.build_only_doc:
      #return False
    return True

  def _requires_catch(self):
    if self.options.build_only_doc:
      return False
    return True

  def requirements(self):
    if self._requires_qt():
      # Building 5.14.x causes currently problems (8.04.2020)
      # As workaround, try fix a known version that we can build
      # Take a Qt version that we have in our Docker images
      # Hmm, now try to use package from conan-center (20.04.2022)
      self.requires("qt/5.15.6")

  def build_requirements(self):
    if self._requires_catch():
      self.test_requires("catch2/2.13.9")
    self.test_requires("mdtcmakemodules/0.20.0@scandyna/testing")

  def generate(self):
    tc = CMakeToolchain(self)
    tc.variables["FROM_CONAN_PROJECT_VERSION"] = self.version
    #tc.variables["INSTALL_CONAN_PACKAGE_FILES"] = "ON"
    #if self.options.gui:
      #tc.variables["ENABLE_GUI_APPLICATION_FOR_NON_QT_USAGE"] = "ON"
    if self.options.build_only_doc:
      tc.variables["ENABLE_CORE_APPLICATION_FOR_NON_QT_USAGE"] = "ON"
      tc.variables["ENABLE_GUI_APPLICATION_FOR_NON_QT_USAGE"] = "ON"
      tc.variables["ENABLE_COMMAND_LINE_ARGUMENTS"] = "ON"
      tc.variables["ENABLE_CONSOLE_APPLICATION"] = "ON"
      tc.variables["BUILD_EXAMPLES"] = "OFF"
      tc.variables["BUILD_CPP_API_DOC"] = "ON"
    else:
      if self.settings.compiler == "gcc" or self.settings.compiler == "clang":
        if self.settings.compiler.sanitizer == "Thread":
          tc.variables["SANITIZER_ENABLE_THREAD"] = "ON"
    tc.generate()
