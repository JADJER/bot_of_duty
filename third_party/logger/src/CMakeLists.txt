cmake_minimum_required(VERSION 3.19)

set(HEADERS
        ${PROJECT_SOURCE_DIR}/include/logger/Logger.hpp
        ${PROJECT_SOURCE_DIR}/include/logger/LoggerAsync.hpp
        ${PROJECT_SOURCE_DIR}/include/logger/LoggerLevel.hpp)

set(SOURCE
        Logger.cpp
        LoggerAsync.cpp)

add_library(${PROJECT_NAME} SHARED ${HEADERS} ${SOURCE})

target_include_directories(${PROJECT_NAME} PUBLIC
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>)

install(
        TARGETS ${PROJECT_NAME}
        EXPORT export_${PROJECT_NAME}
        ARCHIVE DESTINATION ${PROJECT_DESTINATION}/lib
        LIBRARY DESTINATION ${PROJECT_DESTINATION}/lib
        RUNTIME DESTINATION ${PROJECT_DESTINATION}/bin
)