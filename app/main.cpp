//
// Created by jadjer on 27.12.2021.
//

#include <Service.hpp>
#include <spdlog/spdlog.h>
#include <string>

int main(int argc, char** argv) {
  if (argc != 2) {
    spdlog::critical("{} <token>", std::string(argv[0]));
    return 1;
  }

  std::string token = argv[1];

  Service service(token);
  service.start();

  return 0;
}