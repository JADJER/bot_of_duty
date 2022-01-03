//
// Created by jadjer on 28.12.2021.
//

#include "TelegramHandler.hpp"

TelegramHandler::TelegramHandler(std::shared_ptr<TgBot::Bot> const& bot) {
  m_bot = bot;
  m_attendantChat = nullptr;
}

void TelegramHandler::onCommandStart(TgBot::Message::Ptr const& message) {
  m_bot->getApi().sendMessage(message->chat->id, "Hi!");
}

void TelegramHandler::onCommandMarkMeAsAttendant(TgBot::Message::Ptr const& message) {
  m_logger.setLevel(LOGGER_LEVEL_INFO);
  m_logger << "mark_me_as_attendant";
  m_logger.commit();

  if (m_attendantChat == nullptr) {
    m_attendantChat = message->chat;
    m_bot->getApi().sendMessage(message->chat->id, "Your mark as attendant");
    return;
  }

  if (message->chat->id == m_attendantChat->id) {
    m_bot->getApi().sendMessage(message->chat->id, "Your already marked as attendant");

  } else {
    m_bot->getApi().sendMessage(message->chat->id, "Other human is as attendant");
    m_bot->getApi().sendMessage(message->chat->id, "Attendant is " + m_attendantChat->firstName + " (@" + m_attendantChat->username + ")");
  }
}

void TelegramHandler::onCommandUnmarkMeAsAttendant(TgBot::Message::Ptr const& message) {
  m_logger.setLevel(LOGGER_LEVEL_INFO);
  m_logger << "unmark_me_as_attendant";
  m_logger.commit();

  if (m_attendantChat == nullptr) {
    m_bot->getApi().sendMessage(message->chat->id, "Your not marked as attendant");
    return;
  }

  if (message->chat->id == m_attendantChat->id) {
    m_attendantChat = nullptr;
    m_bot->getApi().sendMessage(message->chat->id, "Your unmark as attendant");

  } else {
    m_bot->getApi().sendMessage(message->chat->id, "Your not marked as attendant");
  }
}

void TelegramHandler::onCommandWhoIsAttendant(TgBot::Message::Ptr const& message) {
  m_logger.setLevel(LOGGER_LEVEL_INFO);
  m_logger << "who_is_attendant";
  m_logger.commit();

  if (m_attendantChat == nullptr) {
    m_bot->getApi().sendMessage(message->chat->id, "Attendant is not assigned");
    return;
  }

  m_bot->getApi().sendMessage(message->chat->id, "Attendant is " + m_attendantChat->firstName + " (@" + m_attendantChat->username + ")");
}

void TelegramHandler::onCommandSetAttendantIs(TgBot::Message::Ptr const&) {}

void TelegramHandler::onNonCommandMessage(TgBot::Message::Ptr const& message) {
  if (m_attendantChat == nullptr) {
    m_bot->getApi().sendMessage(message->chat->id, "Attendant is not assigned");
    return;
  }

  if (message->chat->id == m_attendantChat->id) {
    return;
  }

  m_bot->getApi().forwardMessage(m_attendantChat->id, message->chat->id, message->messageId);
}
