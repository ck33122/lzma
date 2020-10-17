from conans import ConanFile, CMake, tools
import os


class LzmaConan(ConanFile):
  name = "lzma"
  version = "1.2"
  license = "public domain"
  url = "https://github.com/ck33122/lzma"
  description = "conan lzma package"
  settings = "os", "compiler", "build_type", "arch"
  generators = "cmake"
  exports_sources = "*"
  requires = ""

  def configure(self):
    del self.settings.compiler.libcxx

  def build(self):
    print("self.dir_src(): %s" % self.dir_src())
    cmake = CMake(self)
    cmake.configure(source_folder=self.dir_src())
    cmake.build()

  def package(self):
    self.copy("*.h", src="%s%sinc" % (self.dir_src(), os.sep), dst="include", keep_path=False)
    self.copy("*.dll", dst="bin", keep_path=False)
    self.copy("*.lib", dst="lib", keep_path=False)
    self.copy("*.so", dst="lib", keep_path=False)
    self.copy("*.so.*", dst="lib", keep_path=False)
    self.copy("*.dylib", dst="lib", keep_path=False)
    self.copy("*.a", dst="lib", keep_path=False)

  def package_info(self):
    self.cpp_info.includedirs = ['include']
    if self.settings.os == "Windows":
      self.cpp_info.libs = ["lzma.lib"]
    else:
      self.cpp_info.libs = ["liblzma.a", "dl"]

  def dir_src(self):
    return self.source_folder

  def dir_bld(self):
    try:
      return self.build_full_path
    except:
      self.build_full_path = "%s%sbuild" % (self.dir_src(), os.sep)
      return self.build_full_path
