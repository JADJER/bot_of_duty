/*
 * Copyright (c) 2020 LACIT. All rights reserved.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *Created by illidansr on 22.12.2020.
 * @details
 * @file
 * @brief
 */
#ifndef CONTROLLER_LOGGER_HPP
#define CONTROLLER_LOGGER_HPP

#include <local_logger/LoggerProxy.hpp>

#include <type_traits>
#include <string>

namespace logger {

template <typename T>
    struct RemoveQualifiers : public std::remove_cvref<std::remove_pointer_t<T>> {};

template <typename T>
struct IsString : public std::is_same<std::string, typename RemoveQualifiers<T>::type> {};

template <typename T>
struct IsCString : public std::is_same<char, typename RemoveQualifiers<T>::type> {};

template <typename ArgumentType>
std::string toString(ArgumentType argumentToConvert) {
    std::string convertedArgument;

    if constexpr (IsCString<ArgumentType>::value) {
        convertedArgument = std::string(argumentToConvert, sizeof(argumentToConvert) / sizeof(char));
    } else if constexpr (IsString<ArgumentType>::value) {
        convertedArgument = argumentToConvert;
    } else {
        convertedArgument = std::to_string(argumentToConvert);
    }

    return convertedArgument;
}

template <typename Arg>
void unpackWithoutReplacement(std::ostream& stream, Arg const& arg) {
    stream << arg;
}

template <typename Arg, typename... Args>
void unpackWithoutReplacement(std::ostream& stream, Arg const& arg, Args&&... args) {
    unpackWithoutReplacement(stream, arg);
    unpackWithoutReplacement(stream, args...);
}

template <typename Arg>
void unpackWithReplacement(std::string& formatString, Arg const& arg) {
    auto bracketsPosition = formatString.find("{}");
    if (bracketsPosition == std::string::npos) {
        formatString.append(toString(arg));
        return;
    }
    formatString.replace(bracketsPosition, 2, toString(arg));
}

template <typename Arg, typename... Args>
void unpackWithReplacement(std::string& formatString, Arg const& arg, Args&&... args) {
    auto bracketsPosition = formatString.find("{}");
    if (bracketsPosition == std::string::npos) {
        formatString.append(toString(arg));
    } else {
        formatString.replace(bracketsPosition, 2, toString(arg));
    }
    unpackWithReplacement(formatString, args...);
}

template <typename Arg, typename... Args, typename = typename std::enable_if_t<IsString<Arg>::value || IsCString<Arg>::value>>
void unpackTemplateArgsToStream(std::ostream& stream, Arg formatCString, Args&&... args) {
    std::string formatString;

    if constexpr (IsCString<Arg>::value) {
        formatString = std::string(formatCString);
    } else if constexpr (IsString<Arg>::value) {
        formatString = formatCString;
    }

    if constexpr (sizeof...(args) != 0) {
        unpackWithReplacement(formatString, args...);
    }
    stream << formatString;
}

template <typename... Args>
void unpackTemplateArgsToStream(std::ostream& stream, Args&&... args) {
    unpackWithoutReplacement(stream, args...);
}

template <typename... Args>
void log_info(Args&&... args) noexcept {
    std::stringstream stringStream;
    unpackTemplateArgsToStream(stringStream, args...);

    auto logger = Logger(LEVEL_INFO);
    logger << stringStream.str();
    logger.commit();
}

template <typename... Args>
void log_error(Args&&... args) noexcept {
    std::stringstream stringStream;
    unpackTemplateArgsToStream(stringStream, args...);

    auto logger = Logger(LEVEL_ERROR);
    logger << stringStream.str();
    logger.commit();
}

template <typename... Args>
void log_warning(Args&&... args) noexcept {
    std::stringstream stringStream;
    unpackTemplateArgsToStream(stringStream, args...);

    auto logger = Logger(LEVEL_WARNING);
    logger << stringStream.str();
    logger.commit();
}

template <typename... Args>
void log_critical(Args&&... args) noexcept {
    std::stringstream stringStream;
    unpackTemplateArgsToStream(stringStream, args...);

    auto logger = Logger(LEVEL_CRITICAL);
    logger << stringStream.str();
    logger.commit();
}

}// namespace logger

#endif// CONTROLLER_LOGGER_HPP
