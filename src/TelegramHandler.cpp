//
// Created by jadjer on 28.12.2021.
//

#include "TelegramHandler.hpp"
#include <spdlog/spdlog.h>

TelegramHandler::TelegramHandler(std::shared_ptr<TgBot::Bot> const& bot) {
  m_bot = bot;
  m_messageMap = {};
  m_attendantChats = {};
}

void TelegramHandler::onCommandStart(TgBot::Message::Ptr const& message) {
  m_bot->getApi().sendMessage(message->chat->id, "Hi!");
}

void TelegramHandler::onCommandMarkMeAsAttendant(TgBot::Message::Ptr const& message) {
  spdlog::info("------------------------------");
  spdlog::info("mark_me_as_attendant");

  auto attendantIterator = std::find_if(m_attendantChats.begin(), m_attendantChats.end(), [&message](auto const& chatId) {
    return message->chat->id == chatId->id;
  });

  if (attendantIterator != m_attendantChats.end()) {
    m_bot->getApi().sendMessage(message->chat->id, "Your already marked as attendant.");
    return;
  }

  m_attendantChats.push_back(message->chat);
  m_bot->getApi().sendMessage(message->chat->id, "Your mark as attendant.");
}

void TelegramHandler::onCommandUnmarkMeAsAttendant(TgBot::Message::Ptr const& message) {
  spdlog::info("------------------------------");
  spdlog::info("unmark_me_as_attendant");

  auto attendantIterator = std::find_if(m_attendantChats.begin(), m_attendantChats.end(), [&message](auto const& chatId) {
    return message->chat->id == chatId->id;
  });

  if (attendantIterator == m_attendantChats.end()) {
    m_bot->getApi().sendMessage(message->chat->id, "Your not marked as attendant.");
    return;
  }

  m_attendantChats.erase(attendantIterator);
  m_bot->getApi().sendMessage(message->chat->id, "Your unmark as attendant.");
}

void TelegramHandler::onCommandWhoIsAttendant(TgBot::Message::Ptr const& message) {
  spdlog::info("------------------------------");
  spdlog::info("who_is_attendant");

  if (m_attendantChats.empty()) {
    m_bot->getApi().sendMessage(message->chat->id, "Attendant is not assigned.");
    return;
  }

  for (auto const& attendant : m_attendantChats) {
    m_bot->getApi().sendMessage(message->chat->id, "Attendant is " + attendant->firstName + " (@" + attendant->username + ").");
  }
}

void TelegramHandler::onNonCommandMessage(TgBot::Message::Ptr const& message) {
  auto attendantIterator = std::find_if(m_attendantChats.begin(), m_attendantChats.end(), [&message](auto const& chatId) {
    return message->chat->id == chatId->id;
  });

  if (attendantIterator != m_attendantChats.end()) {
    messageFromAttendant(message);
  } else {
    messageFromNonAttendant(message);
  }
}

void TelegramHandler::messageFromAttendant(TgBot::Message::Ptr const& message) {
  spdlog::info("------------------------------");
  spdlog::info("Message ID {}, message from \"{}\", chat id {}, name \"{}\" [ATTENDANT!]",
               message->messageId,
               message->chat->username,
               message->chat->id,
               message->chat->firstName);

  if (not message->replyToMessage) {
    m_bot->getApi().sendMessage(message->chat->id, "The message has not been send. Your are attendant.");
    return;
  }

  auto messageMapIterator = std::find_if(m_messageMap.cbegin(), m_messageMap.cend(), [&message](MessageMap const& messageFromMap) -> bool {

    auto messageIdIterator = std::find_if(messageFromMap.forwardsMessageId.cbegin(), messageFromMap.forwardsMessageId.cend(), [&message](std::int32_t messageId) -> bool {
      if (message->replyToMessage->messageId == messageId) {
        spdlog::info("Reply to message ID {}", messageId);
        return true;
      }

      return false;
    });


    if (messageIdIterator != messageFromMap.forwardsMessageId.end()) {
      return true;
    }

    spdlog::info("Message ID not found");
    return false;
  });

  if (messageMapIterator != m_messageMap.end()) {
    m_bot->getApi().forwardMessage(messageMapIterator->sourceChatId, message->chat->id, message->messageId);
  }
}

void TelegramHandler::messageFromNonAttendant(TgBot::Message::Ptr const& message) {
  spdlog::info("------------------------------");
  spdlog::info("Message ID {}, message from \"{}\", chat id {}, name \"{}\"",
               message->messageId,
               message->chat->username,
               message->chat->id,
               message->chat->firstName);

  if (m_attendantChats.empty()) {
    m_bot->getApi().sendMessage(message->chat->id, "Attendant is not assigned.");
    return;
  }

  MessageMap newMessageMap;
  newMessageMap.sourceChatId = message->chat->id;
  newMessageMap.sourceMessageId = message->messageId;

  for (auto const& attendant : m_attendantChats) {
    auto sentMessage = m_bot->getApi().forwardMessage(attendant->id, message->chat->id, message->messageId);
    if (sentMessage) {
      newMessageMap.forwardsMessageId.push_back(sentMessage->messageId);

      m_bot->getApi().sendMessage(message->chat->id, "The message has been send.");

    } else {
      m_bot->getApi().sendMessage(message->chat->id, "The message has not been send.");
    }
  }

  spdlog::info("Associate message ID {} as:", message->messageId);
  for (auto const& messageId : newMessageMap.forwardsMessageId) {
    spdlog::info("Forward message ID: {}" , messageId);
  }

  m_messageMap.push_back(newMessageMap);
}
