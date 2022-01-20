//
// Created by illidansr on 05.02.2021.
//

#ifndef LOGGER_INCLUDE_LOGGER_LOGGER_LEVEL_HPP_
#define LOGGER_INCLUDE_LOGGER_LOGGER_LEVEL_HPP_

/**
 * @namespace data_layer::logger
 * @brief Logger's namespace
 */
namespace logger {

/**
 * @enum LoggerLevel
 * @briefLogger levels enum determination
 */
enum LoggerLevel {
    LEVEL_INFO,
    LEVEL_WARNING,
    LEVEL_ERROR,
    LEVEL_CRITICAL
};

}// namespace logger

#endif// LOGGER_INCLUDE_LOGGER_LOGGER_LEVEL_HPP_
