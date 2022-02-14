//
// Created by jadjer on 27.12.2021.
//

#include <Service.hpp>
#include <spdlog/spdlog.h>
#include <string>

int main(int argc, char** argv) {
  if (argc < 2 or argc > 3) {
    spdlog::critical("{} <token> [solution json file]", std::string(argv[0]));
    return 1;
  }

  std::string token = argv[1];

  std::unique_ptr<Service> service;
  service = std::make_unique<Service>(token);

  if (argc == 3) {
    std::string jsonFilePath = argv[2];
    service = std::make_unique<Service>(token, jsonFilePath);
  }

  signal(SIGINT, [](int s) {
    spdlog::info("SIGINT got");
    exit(1);
  });

  service->start();

  return 0;
}