//
// Created by jadjer on 17.11.2021.
//

#include "logger/LoggerAsync.hpp"

#include "spdlog/async.h"
#include "spdlog/sinks/daily_file_sink.h"
#include "spdlog/spdlog.h"

namespace logger {

struct LoggerAsync::Impl {
    std::shared_ptr<spdlog::logger> loggerAsyncImpl;
};

LoggerAsync::LoggerAsync() :
    m_impl(std::make_unique<Impl>()) {
    spdlog::set_pattern("[%D %H:%M:%S:%f %z] [%^%l%$] [thread %t] %v");
    m_impl->loggerAsyncImpl = spdlog::daily_logger_mt<spdlog::async_factory>("Logger", "logs/log.txt", 3, 00, false, 3);
}

LoggerAsync& LoggerAsync::getInstance() {
    LoggerAsync static loggerInstance;
    return loggerInstance;
}

void LoggerAsync::logDebug(std::string const& payload) noexcept {
    spdlog::debug(payload);
    m_impl->loggerAsyncImpl->template debug(payload);
}

void LoggerAsync::logInfo(std::string const& payload) noexcept {
    spdlog::info(payload);
    m_impl->loggerAsyncImpl->template info(payload);
}

void LoggerAsync::logCritical(std::string const& payload) noexcept {
    spdlog::critical(payload);
    m_impl->loggerAsyncImpl->template critical(payload);
}

void LoggerAsync::logWarning(std::string const& payload) noexcept {
    spdlog::warn(payload);
    m_impl->loggerAsyncImpl->template warn(payload);
}

void LoggerAsync::logError(std::string const& payload) noexcept {
    spdlog::error(payload);
    m_impl->loggerAsyncImpl->template error(payload);
}

}// namespace logger
