cmake_minimum_required(VERSION 3.19)

set(TARGET_NAME logger_test)

set(LOGGER_LIB logger)

set(SOURCE
        main.cpp
        logger_test.cpp)

add_executable(${TARGET_NAME} ${SOURCE})

target_link_libraries(${TARGET_NAME} PUBLIC ${LOGGER_LIB})
