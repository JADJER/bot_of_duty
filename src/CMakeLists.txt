cmake_minimum_required(VERSION 3.17)

set(HEADERS
        ${PROJECT_SOURCE_DIR}/include/Message.hpp
        ${PROJECT_SOURCE_DIR}/include/Service.hpp
        ${PROJECT_SOURCE_DIR}/include/Attendant.hpp
        ${PROJECT_SOURCE_DIR}/include/MessageMap.hpp
        ${PROJECT_SOURCE_DIR}/include/AttendantItem.hpp
        ${PROJECT_SOURCE_DIR}/include/TelegramWorker.hpp
        ${PROJECT_SOURCE_DIR}/include/TelegramHandler.hpp

        ${PROJECT_SOURCE_DIR}/include/problem/IProblem.hpp
        ${PROJECT_SOURCE_DIR}/include/problem/ProblemImpl.hpp
        )

set(SOURCES
        Message.cpp
        Service.cpp
        Attendant.cpp
        TelegramWorker.cpp
        TelegramHandler.cpp

        problem/ProblemImpl.cpp
        )

add_library(${PROJECT_NAME} ${HEADERS} ${SOURCES})

target_link_libraries(${PROJECT_NAME} PUBLIC CONAN_PKG::tgbot)
target_link_libraries(${PROJECT_NAME} PUBLIC CONAN_PKG::spdlog)
target_link_libraries(${PROJECT_NAME} PUBLIC CONAN_PKG::rapidjson)
target_link_libraries(${PROJECT_NAME} PUBLIC CONAN_PKG::sqlitecpp)

install(TARGETS ${PROJECT_NAME}
        EXPORT export_${PROJECT_NAME}
        LIBRARY DESTINATION lib)
