//
// Created by jadjer on 27.12.2021.
//

#include <Service.hpp>
#include <string>

int main(int argc, char** argv) {
  std::string token = "5039903362:AAHtGiQvDpeMwHAGi9xHjDhDcsdZ1XBTwpw";

  if (argc == 2) {
    token = argv[1];
  }

  Service service(token);
  service.start();

  return 0;
}