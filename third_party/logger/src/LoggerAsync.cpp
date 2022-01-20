//
// Created by jadjer on 17.11.2021.
//

#include "logger/LoggerAsync.hpp"

#include "spdlog/async.h"
#include "spdlog/sinks/daily_file_sink.h"
#include "spdlog/spdlog.h"

namespace logger {

LoggerAsync::LoggerAsync() {
    spdlog::set_pattern("[%D %H:%M:%S:%f %z] [%^%l%$] [thread %t] %v");
}

LoggerAsync& LoggerAsync::getInstance() {
    LoggerAsync static loggerInstance;
    return loggerInstance;
}

void LoggerAsync::logDebug(std::string const& payload) noexcept {
    spdlog::debug(payload);
}

void LoggerAsync::logInfo(std::string const& payload) noexcept {
    spdlog::info(payload);
}

void LoggerAsync::logCritical(std::string const& payload) noexcept {
    spdlog::critical(payload);
}

void LoggerAsync::logWarning(std::string const& payload) noexcept {
    spdlog::warn(payload);
}

void LoggerAsync::logError(std::string const& payload) noexcept {
    spdlog::error(payload);
}

}// namespace logger
