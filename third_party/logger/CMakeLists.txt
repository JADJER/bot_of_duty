cmake_minimum_required(VERSION 3.14)
project(logger
        VERSION 1
        DESCRIPTION "Logger"
        LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

include_directories(include)

add_subdirectory(src)
add_subdirectory(tests)
