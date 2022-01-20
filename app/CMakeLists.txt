cmake_minimum_required(VERSION 3.17)

set(SOURCES main.cpp)

add_executable(${PROJECT_NAME}_app ${SOURCES})

target_link_libraries(${PROJECT_NAME}_app PUBLIC ${PROJECT_NAME})
target_link_libraries(${PROJECT_NAME}_app PUBLIC logger)

install(TARGETS ${PROJECT_NAME}_app
        EXPORT export_${PROJECT_NAME}_app
        RUNTIME DESTINATION bin)