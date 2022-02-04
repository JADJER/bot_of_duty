cmake_minimum_required(VERSION 3.17)
project(bot_of_duty)

set(CMAKE_CXX_STANDARD 20)
add_compile_options(-Wall -Wextra -Wpedantic)

include(${CMAKE_BINARY_DIR}/conan_paths.cmake)

find_package(tgbot REQUIRED)
find_package(spdlog REQUIRED)

include_directories(${tgbot_INCLUDE_DIRS})
include_directories(${spdlog_INCLUDE_DIRS})

include_directories(include)

add_subdirectory(app)
add_subdirectory(src)
