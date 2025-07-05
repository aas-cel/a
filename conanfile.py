from conans import ConanFile, CMake

class StylecppConan(ConanFile):
    name = "stylecpp"
    version = "0.1.0"
    license = "MIT"
    author = "StyleCPP Authors"
    url = "https://github.com/stylecpp/stylecpp"
    description = "Utility-first C++ terminal styling library inspired by TailwindCSS."
    topics = ("terminal", "styling", "tailwindcss", "cli", "header-only")
    settings = "os", "compiler", "build_type", "arch"
    generators = "cmake"
    exports_sources = "include/*"
    no_copy_source = True

    def package(self):
        self.copy("*.h", dst="include", src="include")

    def package_id(self):
        self.info.header_only()
