//
// Created by jadjer on 27.12.2021.
//

#include "TelegramWorker.hpp"
#include <exception>
#include <iostream>
#include <logger/Logger.hpp>

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
  m_logger.setLevel(LOGGER_LEVEL_INFO);
  m_logger << "Bot username: " << m_bot->getApi().getMe()->username;
  m_logger.commit();

  m_bot->getApi().deleteWebhook();
  TgBot::TgLongPoll longPoll(*m_bot);

  m_logger.setLevel(LOGGER_LEVEL_INFO);
  m_logger << "Long poll started";
  m_logger.commit();

  while (m_enable) {
    try {
      longPoll.start();
    } catch (std::exception& e) {
      m_logger.setLevel(LOGGER_LEVEL_ERROR);
      m_logger << "Error: " << e.what();
      m_logger.commit();
    }
  }
}
