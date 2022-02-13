//
// Created by jadjer on 12.02.2022.
//

#include "Attendant.hpp"

Attendant::Attendant(std::shared_ptr<SQLite::Database> const& database) {
  m_db = database;

  const bool tableExist = m_db->tableExists("Attendants");
  if (not tableExist) {
    m_db->exec("CREATE TABLE Attendants (id INTEGER PRIMARY KEY, chatId INTEGER, username TEXT, firstName TEXT, secondName TEXT)");
  }

  SQLite::Statement query(*m_db, "SELECT * FROM Attendants");
  while (query.executeStep()) {
    AttendantItem item;
    item.chatId = query.getColumn(1);
    item.userName = query.getColumn(2).getString();
    item.firstName = query.getColumn(3).getString();
    item.secondName = query.getColumn(4).getString();

    m_attendantChats.push_back(item);
  }
}

std::vector<AttendantItem> Attendant::getAttendants() {
  return m_attendantChats;
}

void Attendant::setAttendant(AttendantItem const& attendant) {
  m_attendantChats.push_back(attendant);

  m_db->exec("INSERT INTO Attendants VALUES (NULL, " + std::to_string(attendant.chatId) +
                 ", \"" + attendant.userName +
                 "\", \"" + attendant.firstName +
                 "\", \"" + attendant.secondName +"\")");
}

bool Attendant::deleteAttendant(std::int64_t chatId) {
  auto attendantIterator = std::find_if(m_attendantChats.cbegin(), m_attendantChats.cend(), [&chatId](AttendantItem const& item) {
    return item.chatId == chatId;
  });

  if (attendantIterator == m_attendantChats.cend()) {
    return false;
  }

  m_attendantChats.erase(attendantIterator);
  m_db->exec("DELETE FROM Attendants WHERE chatId = " + std::to_string(chatId));
  return true;
}

bool Attendant::isEmpty() const {
  return m_attendantChats.empty();
}

std::vector<AttendantItem>::const_iterator Attendant::begin() const {
  return m_attendantChats.cbegin();
}

std::vector<AttendantItem>::const_iterator Attendant::end() const {
  return m_attendantChats.cend();
}
