cmake_minimum_required(VERSION 3.17)
project(bot_of_duty)

set(CMAKE_CXX_STANDARD 20)
add_compile_options(-Wall -Wextra -Wpedantic)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup(TARGETS)

include_directories(include)

add_subdirectory(app)
add_subdirectory(src)
