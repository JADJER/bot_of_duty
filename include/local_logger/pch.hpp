//
// Created by illidansr on 03.03.2021.
//

#ifndef CONTROLLER_PCH_HPP
#define CONTROLLER_PCH_HPP

#include <concepts>
#include <type_traits>

template <typename LogMessage>
concept LogSerializable = requires(LogMessage message) {
    /*std::is_class_v<LogMessage>;
    std::is_base_of_v<google::protobuf::Message,
            LogMessage>;
    std::is_constructible_v<LogMessage>;*/
    true;
};

#endif// CONTROLLER_PCH_HPP
