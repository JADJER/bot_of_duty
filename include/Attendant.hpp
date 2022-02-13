//
// Created by jadjer on 12.02.2022.
//

#ifndef BOT_OF_DUTY_INCLUDE_ATTENDANT_HPP_
#define BOT_OF_DUTY_INCLUDE_ATTENDANT_HPP_

#include <vector>
#include <SQLiteCpp/SQLiteCpp.h>
#include <AttendantItem.hpp>

class Attendant {
 public:
  explicit Attendant(std::shared_ptr<SQLite::Database> const& database);

 public:
  std::vector<AttendantItem> getAttendants();
  void setAttendant(AttendantItem const& attendant);
  bool deleteAttendant(std::int64_t chatId);

 public:
  [[nodiscard]] bool isEmpty() const;

 public:
  [[nodiscard]] std::vector<AttendantItem>::const_iterator begin() const;
  [[nodiscard]] std::vector<AttendantItem>::const_iterator end() const;

 private:
  std::shared_ptr<SQLite::Database> m_db;
  std::vector<AttendantItem> m_attendantChats;
};

#endif//BOT_OF_DUTY_INCLUDE_ATTENDANT_HPP_
