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
#ifndef BOT_OF_DUTY_INCLUDE_LOGGER_LOGGER_HPP_
#define BOT_OF_DUTY_INCLUDE_LOGGER_LOGGER_HPP_

#include "LoggerAsync.hpp"
#include "LoggerLevel.hpp"
#include <sstream>

/**
 * @class Logger
 * @brief Class wrapper for async logger.
 * Write data as stream
 */
class Logger {
 public:
  Logger();
  explicit Logger(LoggerLevel loggerLevel);

 public:
  /**
   * @brief
   * @param loggerLevel
   */
  void setLevel(LoggerLevel loggerLevel);

  /**
     * @brief Input log's payload as data stream
     * @tparam Payload Template param with log's payload
     * @param payload Log's payload
     * @return Stream ptr
     */
  template<typename Payload>
  std::ostream& operator<<(Payload const& payload) {
    m_payload << payload;
    return m_payload;
  }

  /**
     * @brief Commit log's payload to logger
     */
  void commit();

 private:
  LoggerLevel m_loggerLevel;
  LoggerAsync& m_loggerAsync;
  std::stringstream m_payload;

 private:
  /**
   * @brief
   */
  void clear();
};

#endif// BOT_OF_DUTY_INCLUDE_LOGGER_LOGGER_HPP_
