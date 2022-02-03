//
// Created by jadjer on 28.12.2021.
//

#ifndef BOT_OF_DUTY_INCLUDE_TELEGRAMHANDLER_HPP_
#define BOT_OF_DUTY_INCLUDE_TELEGRAMHANDLER_HPP_

#include <tgbot/tgbot.h>
#include <vector>

class TelegramHandler {
 public:
  explicit TelegramHandler(std::shared_ptr<TgBot::Bot> const& bot);

 public:
  void onCommandStart(TgBot::Message::Ptr const& message);
  void onCommandMarkMeAsAttendant(TgBot::Message::Ptr const& message);
  void onCommandUnmarkMeAsAttendant(TgBot::Message::Ptr const& message);
  void onCommandWhoIsAttendant(TgBot::Message::Ptr const& message);
  void onNonCommandMessage(TgBot::Message::Ptr const& message);

 private:
  std::shared_ptr<TgBot::Bot> m_bot;
  std::vector<TgBot::Chat::Ptr> m_attendantChats;

  struct MessageMap {
    std::int64_t sourceChatId;
    std::int32_t sourceMessageId;
    std::vector<std::int32_t> forwardsMessageId;
  };

  std::vector<MessageMap> m_messageMap;

  void messageFromAttendant(TgBot::Message::Ptr const& message);
  void messageFromNonAttendant(TgBot::Message::Ptr const& message);
};

#endif//BOT_OF_DUTY_INCLUDE_TELEGRAMHANDLER_HPP_
