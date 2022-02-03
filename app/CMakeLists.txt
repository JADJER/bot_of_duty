cmake_minimum_required(VERSION 3.17)

set(SOURCES main.cpp)

add_executable(${PROJECT_NAME}_app ${SOURCES})

target_link_libraries(${PROJECT_NAME}_app ${PROJECT_NAME} ${CONAN_LIBS})

install(TARGETS ${PROJECT_NAME}_app
        EXPORT export_${PROJECT_NAME}_app
        RUNTIME DESTINATION bin)