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

#include <logger/Logger.hpp>

Logger::Logger() : Logger(LOGGER_LEVEL_INFO) {}

Logger::Logger(LoggerLevel loggerLevel) : m_loggerAsync(LoggerAsync::getInstance()) {
  clear();
  m_loggerLevel = loggerLevel;
}

void Logger::setLevel(LoggerLevel loggerLevel) {
  m_loggerLevel = loggerLevel;
}

void Logger::commit() {
  auto payload = m_payload.str();

  switch (m_loggerLevel) {
    case LoggerLevel::LOGGER_LEVEL_INFO:
      m_loggerAsync.logInfo(payload);
      break;

    case LoggerLevel::LOGGER_LEVEL_WARNING:
      m_loggerAsync.logWarning(payload);
      break;

    case LoggerLevel::LOGGER_LEVEL_ERROR:
      m_loggerAsync.logError(payload);
      break;

    case LoggerLevel::LOGGER_LEVEL_CRITICAL:
      m_loggerAsync.logCritical(payload);
      break;
  }

  clear();
}

void Logger::clear() {
  m_payload.str(std::string());
}
