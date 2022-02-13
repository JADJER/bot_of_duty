//
// Created by jadjer on 12.02.2022.
//

#include "Message.hpp"
#include <spdlog/spdlog.h>

Message::Message(std::shared_ptr<SQLite::Database> const& database) {
  m_db = database;

  const bool tableExist = m_db->tableExists("Messages");
  if (not tableExist) {
    m_db->exec("CREATE TABLE Messages (id INTEGER PRIMARY KEY, source INTEGER, forward INTEGER)");
  }

  SQLite::Statement query(*m_db, "SELECT * FROM Messages");
  while (query.executeStep()) {
    MessageMap messageMap{};
    messageMap.sourceChatId = query.getColumn(1);
    messageMap.forwardMessageId = query.getColumn(2);

    m_messagesMap.push_back(messageMap);
  }
}

void Message::addMessage(std::int64_t sourceChatId, int64_t forwardMessageId) {
  MessageMap messageMap{};
  messageMap.sourceChatId = sourceChatId;
  messageMap.forwardMessageId = forwardMessageId;

  m_messagesMap.push_back(messageMap);

  spdlog::info("Associate message ID {} as {}:", sourceChatId, forwardMessageId);
  m_db->exec("INSERT INTO Messages VALUES (NULL, " + std::to_string(sourceChatId) + ", " + std::to_string(forwardMessageId) + ")");
}

void Message::addMessage(std::int64_t sourceChatId, std::vector<std::int64_t> const& forwardsMessageId) {
  for (std::int64_t const& forwardMessageId : forwardsMessageId) {
    addMessage(sourceChatId, forwardMessageId);
  }
}

std::optional<int64_t> Message::getSourceChatId(std::int64_t forwardMessageId) {
  auto messageMapIterator = std::find_if(m_messagesMap.cbegin(), m_messagesMap.cend(), [&forwardMessageId](MessageMap const& messageFromMap) -> bool {
    if (messageFromMap.forwardMessageId == forwardMessageId) {
      spdlog::info("Reply to message ID {}", forwardMessageId);
      return true;
    }

    return false;
  });

  if (messageMapIterator != m_messagesMap.cend()) {
    return messageMapIterator->sourceChatId;
  }

  return std::nullopt;
}

std::vector<MessageMap>::const_iterator Message::begin() const {
  return m_messagesMap.cbegin();
}

std::vector<MessageMap>::const_iterator Message::end() const {
  return m_messagesMap.cend();
}
