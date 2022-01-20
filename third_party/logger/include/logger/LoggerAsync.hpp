//
// Created by jadjer on 17.11.2021.
//

#ifndef LOGGER_INCLUDE_LOGGER_LOGGER_ASYNC_HPP_
#define LOGGER_INCLUDE_LOGGER_LOGGER_ASYNC_HPP_

#include <memory>

/**
 * @namespace data_layer::logger
 * @brief Logger's namespace
 */
namespace logger {

/**
 * @class LoggerAsync
 * @brief Logger implementation (async)
 */
class LoggerAsync {
   public:
    /**
     * @brief Get LoggerAsync's singleton instance pointer
     * @return Pointer to static LoggerAsync's object
     */
    static LoggerAsync& getInstance();

    /**
     * @brief Set logger's data in debug level
     * @param payload Log's data
     */
    void logDebug(std::string const& payload) noexcept;

    /**
     * @brief Set logger's data in info level
     * @param payload Log's data
     */
    void logInfo(std::string const& payload) noexcept;

    /**
     * @brief Set logger's data in critical level
     * @param payload Log's data
     */
    void logCritical(std::string const& payload) noexcept;

    /**
     * @brief Set logger's data in warning level
     * @param payload Log's data
     */
    void logWarning(std::string const& payload) noexcept;

    /**
     * @brief Set logger's data in error level
     * @param payload Log's data
     */
    void logError(std::string const& payload) noexcept;

   private:
    LoggerAsync();

   private:
    struct Impl;
    std::unique_ptr<Impl> m_impl;
};

}// namespace logger

#endif// LOGGER_INCLUDE_LOGGER_LOGGER_ASYNC_HPP_
