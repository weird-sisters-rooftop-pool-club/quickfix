from conans import ConanFile, CMake, tools
import os

from conans.errors import ConanInvalidConfiguration


class QuickfixConan(ConanFile):
    name = "quickfix"
    version = "1.15.1"
    description = "Quickfix"
    topics = ("conan", "quickfix")
    url = "https://github.com/sourcedelica/conan-quickfix.git"
    _source_url = "https://github.com/sourcedelica/quickfix.git"
    # _source_url = "https://github.com/quickfix/quickfix.git"
    homepage = "https://github.com/quickfix/quickfix"
    license = "The QuickFIX Software License, Version 1.0"
    exports_sources = ["../CMakeLists.txt"]
    generators = "cmake"

    # Options may need to change depending on the packaged library
    settings = "os", "arch", "compiler", "build_type"
    options = {"shared": [True, False], "fPIC": [True, False]}
    default_options = {"shared": False, "fPIC": True}

    _source_subfolder = ".."
    _build_subfolder = "."

    requires = (
        "openssl/1.1.1d"
    )

    def config_options(self):
        if self.settings.os == 'Windows':
            del self.options.fPIC
            if self.options.shared and self.settings.compiler == 'Visual Studio':
                raise ConanInvalidConfiguration('Shared libraries not supported for Visual Studio')

    def source(self):
        pass

    def _configure_cmake(self):
        cmake = CMake(self)
        if self.settings.compiler != "Visual Studio":
            cmake.definitions["CMAKE_CXX_FLAGS"] = "-std=c++11"
        cmake.definitions["HAVE_SSL"] = True
        cmake.definitions["BUILD_EXAMPLES"] = False
        cmake.definitions["BUILD_SHARED_LIBS"] = self.options.shared
        cmake.configure(build_folder=self._build_subfolder)
        return cmake

    def build(self):
        cmake = self._configure_cmake()
        cmake.build(target='quickfix')

    def package(self):
        self.copy(pattern="LICENSE", dst="licenses", src=self._source_subfolder)
        cmake = self._configure_cmake()
        cmake.install()

    def package_info(self):
        self.cpp_info.libs = tools.collect_libs(self)
