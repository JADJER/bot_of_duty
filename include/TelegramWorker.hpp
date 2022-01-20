//
// Created by jadjer on 27.12.2021.
//

#ifndef BOT_OF_DUTY_INCLUDE_TELEGRAMWORKER_HPP_
#define BOT_OF_DUTY_INCLUDE_TELEGRAMWORKER_HPP_

#include <atomic>
//#include <leveldb/export.h>
#include <logger/Logger.hpp>
#include <memory>
#include <tgbot/tgbot.h>
#include <thread>

class TelegramWorker {
 public:
  using MessageListener = TgBot::EventBroadcaster::MessageListener;
  using CallbackQueryListener = TgBot::EventBroadcaster::CallbackQueryListener;

 public:
  explicit TelegramWorker(std::shared_ptr<TgBot::Bot> const& bot);
  ~TelegramWorker();

 public:
  void start();
  void stop();
  void addCommandHandler(std::string const& commandName, MessageListener const& listener);
  void addMessageHandler(MessageListener const& listener);
  void addCallbackQuery(CallbackQueryListener const& listener);

 private:
  std::thread m_thread;
  std::atomic_bool m_enable;
  std::shared_ptr<TgBot::Bot> m_bot;

 private:
  void loop();
};

#endif//BOT_OF_DUTY_INCLUDE_TELEGRAMWORKER_HPP_
