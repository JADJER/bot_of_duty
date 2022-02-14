//
// Created by jadjer on 28.12.2021.
//

#ifndef BOT_OF_DUTY_INCLUDE_TELEGRAMHANDLER_HPP_
#define BOT_OF_DUTY_INCLUDE_TELEGRAMHANDLER_HPP_

#include <Attendant.hpp>
#include <Message.hpp>
#include <SQLiteCpp/SQLiteCpp.h>
#include <SQLiteCpp/VariadicBind.h>
#include <problem/IProblem.hpp>
#include <tgbot/tgbot.h>
#include <vector>

class TelegramHandler {
 public:
  TelegramHandler() = delete;
  explicit TelegramHandler(std::shared_ptr<TgBot::Bot> const& bot, std::string const& problemJsonFile = "", std::string const& databasePath = "");

 public:
  void onCommandStart(TgBot::Message::Ptr const& message);
  void onCommandMarkMeAsAttendant(TgBot::Message::Ptr const& message);
  void onCommandUnmarkMeAsAttendant(TgBot::Message::Ptr const& message);
  void onCommandWhoIsAttendant(TgBot::Message::Ptr const& message);
  void onNonCommandMessage(TgBot::Message::Ptr const& message);

 private:
  std::shared_ptr<TgBot::Bot> m_bot;
  std::unique_ptr<Message> m_messages;
  std::unique_ptr<IProblem> m_problems;
  std::shared_ptr<SQLite::Database> m_db;
  std::unique_ptr<Attendant> m_attendants;

 private:
  void messageFromAttendant(TgBot::Message::Ptr const& message);
  void messageFromNonAttendant(TgBot::Message::Ptr const& message);
};

#endif//BOT_OF_DUTY_INCLUDE_TELEGRAMHANDLER_HPP_
