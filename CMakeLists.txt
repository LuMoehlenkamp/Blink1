cmake_minimum_required(VERSION 3.7.1)

 project(gitTest)

 add_definitions("-std=c++14")

 include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
 conan_basic_setup()

 add_executable(Blink1 main.cpp)
 target_link_libraries(Blink1 ${CONAN_LIBS})
