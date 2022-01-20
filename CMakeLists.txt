cmake_minimum_required(VERSION 3.17)
project(bot_of_duty)

set(CMAKE_CXX_STANDARD 20)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

include_directories(include)

add_subdirectory(third_party/logger)
include_directories(third_party/logger/include)

add_subdirectory(app)
add_subdirectory(src)
