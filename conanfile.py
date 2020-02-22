from conans import ConanFile, CMake, tools

class HelloConan(ConanFile):
    name = "Blink1"
    version = "0.1"
    license = "<MIT>"
    # url = "<Package recipe repository url here, for issues about the package>"
    # description = "<Description of Hello here>"
    settings = "os", "compiler", "build_type", "arch"
    options = {"shared": [True, False]}
    default_options = {"shared": False}
    generators = "cmake"

    def source(self):
        # self.run("git clone https://github.com/LuMoehlenkamp/gitTest.git")
        # This small hack might be useful to guarantee proper /MT /MD linkage
        # in MSVC if the packaged project doesn't have variables to set it
        # properly
        tools.replace_in_file("hello/CMakeLists.txt", "PROJECT(Blink1)",
                              '''PROJECT(Blink1)
                              include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
                              conan_basic_setup()''')

    def build(self):
        cmake = CMake(self)
        cmake.configure(source_folder="./")
        cmake.build()

        # Explicit way:
        # self.run('cmake %s/gitTest %s'
        #          % (self.source_folder, cmake.command_line))
        # self.run("cmake --build . %s" % cmake.build_config)

    def package(self):
        self.copy("*.h", dst="include", src="Blink1")
        self.copy("*Blink1.lib", dst="lib", keep_path=False)
        self.copy("*.dll", dst="bin", keep_path=False)
        self.copy("*.so", dst="lib", keep_path=False)
        self.copy("*.dylib", dst="lib", keep_path=False)
        self.copy("*.a", dst="lib", keep_path=False)

    def package_info(self):
        self.cpp_info.libs = ["Blink1"]