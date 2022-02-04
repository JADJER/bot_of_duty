cmake_minimum_required(VERSION 3.17)

set(HEADERS
        ${PROJECT_SOURCE_DIR}/include/Service.hpp
        ${PROJECT_SOURCE_DIR}/include/TelegramWorker.hpp
        ${PROJECT_SOURCE_DIR}/include/TelegramHandler.hpp
        )

set(SOURCES
        Service.cpp
        TelegramWorker.cpp
        TelegramHandler.cpp
        )

add_library(${PROJECT_NAME} ${HEADERS} ${SOURCES})

target_link_libraries(${PROJECT_NAME} PUBLIC ${tgbot_LIBRARIES})
target_link_libraries(${PROJECT_NAME} PUBLIC ${spdlog_LIBRARIES})

install(TARGETS ${PROJECT_NAME}
        EXPORT export_${PROJECT_NAME}
        LIBRARY DESTINATION lib)