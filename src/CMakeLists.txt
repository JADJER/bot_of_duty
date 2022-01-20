cmake_minimum_required(VERSION 3.17)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall")
set(Boost_USE_MULTITHREADED ON)

find_package(Threads REQUIRED)
find_package(OpenSSL REQUIRED)
find_package(Boost COMPONENTS system REQUIRED)
find_package(CURL)
include_directories(/usr/local/include ${OPENSSL_INCLUDE_DIR} ${Boost_INCLUDE_DIR})

if (CURL_FOUND)
    include_directories(${CURL_INCLUDE_DIRS})
    add_definitions(-DHAVE_CURL)
endif()

set(HEADERS
        ${PROJECT_SOURCE_DIR}/include/Service.hpp
        ${PROJECT_SOURCE_DIR}/include/TelegramWorker.hpp
        ${PROJECT_SOURCE_DIR}/include/TelegramHandler.hpp

        ${PROJECT_SOURCE_DIR}/include/local_logger/Logger.hpp
        ${PROJECT_SOURCE_DIR}/include/local_logger/LoggerProxy.hpp
        ${PROJECT_SOURCE_DIR}/include/local_logger/pch.hpp
        )

set(SOURCES
        Service.cpp
        TelegramWorker.cpp
        TelegramHandler.cpp

        local_logger/Logger.cpp
        )

add_library(${PROJECT_NAME} SHARED ${HEADERS} ${SOURCES})

target_link_libraries(${PROJECT_NAME} TgBot ${CMAKE_THREAD_LIBS_INIT} ${OPENSSL_LIBRARIES} ${Boost_LIBRARIES})

install(TARGETS ${PROJECT_NAME}
        EXPORT export_${PROJECT_NAME}
        LIBRARY DESTINATION lib)