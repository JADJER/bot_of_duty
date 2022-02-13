//
// Created by jadjer on 12.02.2022.
//

#ifndef BOT_OF_DUTY_INCLUDE_MESSAGE_HPP_
#define BOT_OF_DUTY_INCLUDE_MESSAGE_HPP_

#include <MessageMap.hpp>
#include <SQLiteCpp/SQLiteCpp.h>
#include <tgbot/tgbot.h>
#include <vector>
#include <optional>

class Message {
 public:
  explicit Message(std::shared_ptr<SQLite::Database> const& database);

 public:
  void addMessage(std::int64_t sourceChatId, std::int64_t forwardMessageId);
  void addMessage(std::int64_t sourceChatId, std::vector<std::int64_t> const& forwardsMessageId);

 public:
  std::optional<std::int64_t> getSourceChatId(std::int64_t forwardMessageId);

 public:
  [[nodiscard]] std::vector<MessageMap>::const_iterator begin() const;
  [[nodiscard]] std::vector<MessageMap>::const_iterator end() const;

 private:
  std::vector<MessageMap> m_messagesMap;
  std::shared_ptr<SQLite::Database> m_db;
};

#endif//BOT_OF_DUTY_INCLUDE_MESSAGE_HPP_
