//
// Created by jadjer on 28.12.2021.
//

#include <TelegramHandler.hpp>
#include <problem/ProblemImpl.hpp>
#include <spdlog/spdlog.h>

TelegramHandler::TelegramHandler(std::shared_ptr<TgBot::Bot> const& bot) {
  m_db = std::make_unique<SQLite::Database>("bod.db3", SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE);
  m_bot = bot;

  m_problems = nullptr;
  m_messages = std::make_unique<Message>(m_db);
  m_attendants = std::make_unique<Attendant>(m_db);
}

TelegramHandler::TelegramHandler(std::shared_ptr<TgBot::Bot> const& bot, std::string const& pathFile)
    : TelegramHandler(bot) {
  m_problems = std::make_unique<ProblemImpl>(pathFile);
}

void TelegramHandler::onCommandStart(TgBot::Message::Ptr const& message) {
  m_bot->getApi().sendMessage(message->chat->id, "Hi!");
}

void TelegramHandler::onCommandMarkMeAsAttendant(TgBot::Message::Ptr const& message) {
  spdlog::info("------------------------------");
  spdlog::info("mark_me_as_attendant | {}", message->chat->username);

  auto attendantIterator = std::find_if(m_attendants->begin(), m_attendants->end(), [&message](AttendantItem const& item) {
    return message->chat->id == item.chatId;
  });

  if (attendantIterator != m_attendants->end()) {
    m_bot->getApi().sendMessage(message->chat->id, "Your already marked as attendant.");
    return;
  }

  AttendantItem item;
  item.chatId = message->chat->id;
  item.userName = message->chat->username;
  item.firstName = message->chat->firstName;
  item.secondName = message->chat->lastName;

  m_attendants->setAttendant(item);
  m_bot->getApi().sendMessage(message->chat->id, "Your mark as attendant.");
}

void TelegramHandler::onCommandUnmarkMeAsAttendant(TgBot::Message::Ptr const& message) {
  spdlog::info("------------------------------");
  spdlog::info("unmark_me_as_attendant | {}", message->chat->username);

  auto attendantHasDeleted = m_attendants->deleteAttendant(message->chat->id);
  if (not attendantHasDeleted) {
    m_bot->getApi().sendMessage(message->chat->id, "Your not marked as attendant.");
    return;
  }

  m_bot->getApi().sendMessage(message->chat->id, "Your unmark as attendant.");
}

void TelegramHandler::onCommandWhoIsAttendant(TgBot::Message::Ptr const& message) {
  spdlog::info("------------------------------");
  spdlog::info("who_is_attendant | {}", message->chat->username);

  if (m_attendants->isEmpty()) {
    m_bot->getApi().sendMessage(message->chat->id, "Attendant is not assigned.");
    return;
  }

  for (auto const& attendant : *m_attendants) {
    m_bot->getApi().sendMessage(message->chat->id, "Attendant is " + attendant.firstName + " (@" + attendant.userName + ").");
  }
}

void TelegramHandler::onNonCommandMessage(TgBot::Message::Ptr const& message) {
  auto attendantIterator = std::find_if(m_attendants->begin(), m_attendants->end(), [&message](AttendantItem const& item) {
    return message->chat->id == item.chatId;
  });

  if (attendantIterator != m_attendants->end()) {
    messageFromAttendant(message);
  } else {
    messageFromNonAttendant(message);
  }
}

void TelegramHandler::messageFromAttendant(TgBot::Message::Ptr const& message) {
  spdlog::info("------------------------------");
  spdlog::info(R"(Message ID {}, message from "{}", chat id {}, name "{}" [ATTENDANT!])",
               message->messageId,
               message->chat->username,
               message->chat->id,
               message->chat->firstName);

  if (not message->replyToMessage) {
    m_bot->getApi().sendMessage(message->chat->id, "The message has not been send. Your are attendant.");
    return;
  }

  auto sourceChatIdOptional = m_messages->getSourceChatId(message->replyToMessage->messageId);
  if (not sourceChatIdOptional) {
    spdlog::info("Message ID not found");
    return;
  }

  m_bot->getApi().forwardMessage(sourceChatIdOptional.value(), message->chat->id, message->messageId);
}

void TelegramHandler::messageFromNonAttendant(TgBot::Message::Ptr const& message) {
  spdlog::info("------------------------------");
  spdlog::info(R"(Message ID {}, message from "{}", chat id {}, name "{}")",
               message->messageId,
               message->chat->username,
               message->chat->id,
               message->chat->firstName);

  if (m_attendants->isEmpty()) {
    m_bot->getApi().sendMessage(message->chat->id, "Attendant is not assigned.");
    return;
  }

  std::vector<int64_t> forwardsMessageId;

  for (auto const& attendant : *m_attendants) {
    auto sentMessage = m_bot->getApi().forwardMessage(attendant.chatId, message->chat->id, message->messageId);
    if (sentMessage) {
      forwardsMessageId.push_back(sentMessage->messageId);
    }
  }

  m_messages->addMessage(message->chat->id, forwardsMessageId);
}
