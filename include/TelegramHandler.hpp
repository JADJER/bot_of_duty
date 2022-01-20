//
// Created by jadjer on 28.12.2021.
//

#ifndef BOT_OF_DUTY_INCLUDE_TELEGRAMHANDLER_HPP_
#define BOT_OF_DUTY_INCLUDE_TELEGRAMHANDLER_HPP_

#include <tgbot/tgbot.h>

class TelegramHandler {
 public:
  explicit TelegramHandler(std::shared_ptr<TgBot::Bot> const& bot);

 public:
  void onCommandStart(TgBot::Message::Ptr const& message);
  void onCommandMarkMeAsAttendant(TgBot::Message::Ptr const& message);
  void onCommandUnmarkMeAsAttendant(TgBot::Message::Ptr const& message);
  void onCommandWhoIsAttendant(TgBot::Message::Ptr const& message);
  void onCommandSetAttendantIs(TgBot::Message::Ptr const& message);
  void onNonCommandMessage(TgBot::Message::Ptr const& message);

 private:
  TgBot::Chat::Ptr m_attendantChat;
  std::shared_ptr<TgBot::Bot> m_bot;
};

#endif//BOT_OF_DUTY_INCLUDE_TELEGRAMHANDLER_HPP_
