from conans import ConanFile, tools
#from conans.errors import ConanInvalidConfiguration
from conan.tools.cmake import CMakeToolchain, CMakeDeps, CMake
#from conan.tools.env import VirtualBuildEnv
import os


class MdtApplicationConan(ConanFile):
  name = "MdtApplication"
  #version = "0.1"
  license = "BSD 3-Clause"
  url = "https://gitlab.com/scandyna/mdtapplication"
  description = "Some additions for QCoreApplication, QGuiApplication and QApplication"
  settings = "os", "compiler", "build_type", "arch"
  # TODO: remove gui option
  options = {"shared": [True, False],
             "gui": [True, False]}
  default_options = {"shared": True,
                     "gui": True}
  # TODO fix once issue solved
  # Due to a issue using GitLab Conan repository,
  # version ranges are not possible.
  # See https://gitlab.com/gitlab-org/gitlab/-/issues/333638
  #build_requires = "MdtCMakeModules/0.17.1@scandyna/testing", "catch2/2.13.9"
  #tool_requires = "MdtCMakeModules/0.17.1@scandyna/testing", "catch2/2.13.9"
  #build_requires = "MdtCMakeModules/0.14.18@scandyna/testing", "Catch2/2.11.1@catchorg/stable"
  #build_requires = "MdtCMakeModules/[>=0.14.12]@scandyna/testing", "Catch2/[>=2.11.1]@catchorg/stable"
  #generators = "CMakeToolchain"
  generators = "CMakeDeps", "CMakeToolchain", "VirtualBuildEnv"
  #generators = "cmake", "cmake_paths", "virtualenv", "cmake_find_package_multi"
  #generators = "cmake"
  exports_sources = "libs/*", "CMakeLists.txt", "conanfile.py", "COPYING", "COPYING.LESSER"
  # If no_copy_source is False, conan copies sources to build directory and does in-source build,
  # resulting having build files installed in the package
  # See also: https://github.com/conan-io/conan/issues/350
  no_copy_source = True

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

    # Building 5.14.x causes currently problems (8.04.2020)
    # As workaround, try fix a known version that we can build
    # Take a Qt version that we have in our Docker images
    # Hmm, now try to use package from conan-center (20.04.2022)
    self.requires("qt/5.15.2")
    #self.requires("qt/5.14.2@bincrafters/stable")
    #self.requires("qt/5.12.7@bincrafters/stable")
    #if self.options.gui:
      #self.options["qt"].GUI = True

  #def generate(self):
      #cmake = CMakeDeps(self)
      ## generate the config files for the tool require
      #cmake.build_context_activated = ["mdtcmakemodules"]
      ## disambiguate the files, targets, etc
      ##cmake.build_context_suffix = {"MdtCMakeModules": "_BUILD"}
      #cmake.generate()

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
    self.tool_requires("catch2/2.13.9", force_host_context=True)
    self.tool_requires("MdtCMakeModules/0.18.1@scandyna/testing", force_host_context=True)

  # TODO: use generate()
  #def configure_cmake(self):
    #cmake = CMake(self)
    #cmake.definitions["FROM_CONAN_PROJECT_VERSION"] = self.version

    #if self.options.gui:
      #cmake.definitions["ENABLE_GUI_APPLICATION_FOR_NON_QT_USAGE"] = "ON"

    #if self.settings.compiler == "gcc" or self.settings.compiler == "clang":
      #if self.settings.compiler.sanitizer == "Thread":
        #cmake.definitions["SANITIZER_ENABLE_THREAD"] = "ON"

    #return cmake

  def generate(self):
    tc = CMakeToolchain(self)
    tc.variables["FROM_CONAN_PROJECT_VERSION"] = self.version
    #tc.variables["INSTALL_CONAN_PACKAGE_FILES"] = "ON"
    if self.options.gui:
      tc.variables["ENABLE_GUI_APPLICATION_FOR_NON_QT_USAGE"] = "ON"
    if self.settings.compiler == "gcc" or self.settings.compiler == "clang":
      if self.settings.compiler.sanitizer == "Thread":
        tc.variables["SANITIZER_ENABLE_THREAD"] = "ON"
    tc.generate()

  # TODO: should throw a exception,
  # because this recipe cannot be used to create packages
  # TODO: see validate() ?
  def build(self):
    #cmake = self.configure_cmake()
    cmake = CMake(self)
    cmake.configure()
    cmake.build()


  def package(self):
    #cmake = self.configure_cmake()
    cmake = CMake(self)
    cmake.install()

  def package_info(self):

    self.cpp_info.set_property("cmake_file_name", "Mdt0")

    self.cpp_info.components["mdtconsoleapplication"].set_property("cmake_target_name", "Mdt0::ConsoleApplication")
    self.cpp_info.components["mdtconsoleapplication"].libs = ["Mdt0ConsoleApplication"]
