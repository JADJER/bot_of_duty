//
// Created by jadjer on 27.12.2021.
//

#include <TelegramWorker.hpp>
#include <exception>
#include <iostream>
#include <local_logger/Logger.hpp>

TelegramWorker::TelegramWorker(std::shared_ptr<TgBot::Bot> const& bot)
    : m_enable(true) {

  m_bot = bot;
}

TelegramWorker::~TelegramWorker() {
  stop();
}

void TelegramWorker::start() {
  m_enable = true;

  m_thread = std::thread(&TelegramWorker::loop, this);
  m_thread.join();
}

void TelegramWorker::stop() {
  m_enable = false;

  if (m_thread.joinable()) {
    m_thread.join();
  }
}

void TelegramWorker::addCommandHandler(std::string const& commandName, MessageListener const& listener) {
  m_bot->getEvents().onCommand(commandName, listener);
}

void TelegramWorker::addMessageHandler(MessageListener const& listener) {
  m_bot->getEvents().onNonCommandMessage(listener);
}

void TelegramWorker::addCallbackQuery(CallbackQueryListener const& listener) {
  m_bot->getEvents().onCallbackQuery(listener);
}

void TelegramWorker::loop() {
  logger::log_info("Bot username: {}", m_bot->getApi().getMe()->username);

  m_bot->getApi().deleteWebhook();
  TgBot::TgLongPoll longPoll(*m_bot);

  logger::log_info("Long poll started");

  while (m_enable) {
    try {
      longPoll.start();
    } catch (std::exception& e) {
      logger::log_error("Error: {}", e.what());
    }
  }
}
