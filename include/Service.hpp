//
// Created by jadjer on 27.12.2021.
//

#ifndef BOT_OF_DUTY_SRC_SERVICE_HPP_
#define BOT_OF_DUTY_SRC_SERVICE_HPP_

#include <string>
#include <memory>
#include <TelegramWorker.hpp>
#include <TelegramHandler.hpp>

/**
 * @class Service
 * @brief
 */
class Service {
 public:
  /**
   * @brief
   * @param token
   * @param jsonFilePath
   */
  explicit Service(std::string const& token, std::string const& jsonFilePath = "", std::string const& databasePath = "");

 public:
  /**
   * @brief Start service loop
   */
  void start();
  void stop();

 private:
  std::shared_ptr<TgBot::Bot> m_bot;
  std::unique_ptr<TelegramWorker> m_telegramWorker;
  std::unique_ptr<TelegramHandler> m_telegramHandler;
};

#endif//BOT_OF_DUTY_SRC_SERVICE_HPP_
