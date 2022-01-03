//
// Created by jadjer on 27.12.2021.
//

#include "Service.hpp"
#include <logger/Logger.hpp>

Service::Service(std::string const& token) {
  m_bot = std::make_shared<TgBot::Bot>(token);

  m_telegramWorker = std::make_unique<TelegramWorker>(m_bot);
  m_telegramHandler = std::make_unique<TelegramHandler>(m_bot);
}

void Service::start() {
  m_telegramWorker->addCommandHandler("start", [this](auto&& PH1) { m_telegramHandler->onCommandStart(std::forward<decltype(PH1)>(PH1)); });
  m_telegramWorker->addCommandHandler("mark_me_as_attendant", [this](auto&& PH1) { m_telegramHandler->onCommandMarkMeAsAttendant(std::forward<decltype(PH1)>(PH1)); });
  m_telegramWorker->addCommandHandler("unmark_me_as_attendant", [this](auto&& PH1) { m_telegramHandler->onCommandUnmarkMeAsAttendant(std::forward<decltype(PH1)>(PH1)); });
  m_telegramWorker->addCommandHandler("set_attendant_is", [this](auto&& PH1) { m_telegramHandler->onCommandSetAttendantIs(std::forward<decltype(PH1)>(PH1)); });
  m_telegramWorker->addCommandHandler("who_is_attendant", [this](auto&& PH1) { m_telegramHandler->onCommandWhoIsAttendant(std::forward<decltype(PH1)>(PH1)); });

  m_telegramWorker->addMessageHandler([this](auto&& PH1) { m_telegramHandler->onNonCommandMessage(std::forward<decltype(PH1)>(PH1)); });

  m_telegramWorker->start();
}
