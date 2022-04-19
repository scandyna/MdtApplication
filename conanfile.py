from conans import ConanFile, CMake, tools
import os


class MdtApplicationConan(ConanFile):
  name = "MdtApplication"
  #version = "0.1"
  license = "BSD 3-Clause"
  url = "https://gitlab.com/scandyna/mdtapplication"
  description = "Some additions for QCoreApplication, QGuiApplication and QApplication"
  settings = "os", "compiler", "build_type", "arch"
  options = {"shared": [True, False],
             "gui": [True, False],
             "use_conan_qt": [True, False]}
  default_options = {"shared": True,
                     "gui": True,
                     "use_conan_qt": False}
  # TODO fix once issue solved
  # Due to a issue using GitLab Conan repository,
  # version ranges are not possible.
  # See https://gitlab.com/gitlab-org/gitlab/-/issues/333638
  build_requires = "MdtCMakeModules/0.14.18@scandyna/testing", "Catch2/2.11.1@catchorg/stable"
  #build_requires = "MdtCMakeModules/[>=0.14.12]@scandyna/testing", "Catch2/[>=2.11.1]@catchorg/stable"
  generators = "cmake", "cmake_paths", "virtualenv"
  exports_sources = "libs/*", "CMakeLists.txt", "conanfile.py", "COPYING", "COPYING.LESSER"
  # If no_copy_source is False, conan copies sources to build directory and does in-source build,
  # resulting having build files installed in the package
  # See also: https://github.com/conan-io/conan/issues/350
  no_copy_source = True

  # See: https://docs.conan.io/en/latest/reference/conanfile/attributes.html#short-paths
  short_paths = True

  def set_version(self):
    if os.path.exists(".git"):
      git = tools.Git()
      self.version = "%s" % (git.get_tag())


  def requirements(self):

    # The main usage of using conan Qt package is for TSan builds
    # Building 5.14.x causes currently problems (8.04.2020)
    # As workaround, try fix a known version that we can build
    # Take a Qt version that we have in our Docker images
    if self.options.use_conan_qt:
      self.requires("qt/5.14.2@bincrafters/stable")
      #self.requires("qt/5.12.7@bincrafters/stable")
      #if self.options.gui:
        #self.options["qt"].GUI = True


  def configure_cmake(self):
    cmake = CMake(self)
    cmake.definitions["FROM_CONAN_PROJECT_VERSION"] = self.version

    if self.options.gui:
      cmake.definitions["ENABLE_GUI_APPLICATION_FOR_NON_QT_USAGE"] = "ON"

    if self.settings.compiler == "gcc" or self.settings.compiler == "clang":
      if self.settings.compiler.sanitizer == "Thread":
        cmake.definitions["SANITIZER_ENABLE_THREAD"] = "ON"

    return cmake


  def build(self):
    cmake = self.configure_cmake()
    cmake.configure()
    cmake.build()


  def package(self):
    cmake = self.configure_cmake()
    cmake.install()
