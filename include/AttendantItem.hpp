//
// Created by jadjer on 13.02.2022.
//

#ifndef BOT_OF_DUTY_INCLUDE_ATTENDANTITEM_HPP_
#define BOT_OF_DUTY_INCLUDE_ATTENDANTITEM_HPP_

#include <string>

struct AttendantItem {
  std::int64_t chatId;
  std::string userName;
  std::string firstName;
  std::string secondName;
};

#endif//BOT_OF_DUTY_INCLUDE_ATTENDANTITEM_HPP_
