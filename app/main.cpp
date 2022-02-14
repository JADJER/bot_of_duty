//
// Created by jadjer on 27.12.2021.
//

#include <Service.hpp>
#include <spdlog/spdlog.h>
#include <string>

int main(int argc, char** argv) {
  if (argc < 2) {
    spdlog::critical("{} <token> [solution json file]", std::string(argv[0]));
    return 1;
  }

  if (argc % 2 != 0) {
    spdlog::critical("Wrong program arguments");
    spdlog::info("{} <token> [solution json file]", std::string(argv[0]));
    spdlog::info("-p Path to json file with problems");
    spdlog::info("-db Path to file with database");
    return 1;
  }

  std::string token = argv[1];
  std::string problemJsonPath;
  std::string databasePath;

  for (size_t i = 2; i < argc - 1; i++) {
    if (std::string("-p").compare(argv[i]) == 0) {
      problemJsonPath = argv[i + 1];
      spdlog::info("Problem file path: {}", problemJsonPath);
    }

    if (std::string("-db").compare(argv[i]) == 0) {
      databasePath = argv[i + 1];
      spdlog::info("Database file path: {}", databasePath);
    }
  }

  auto service = std::make_unique<Service>(token, problemJsonPath, databasePath);

  signal(SIGINT, [](int) {
    spdlog::info("SIGINT got");
    exit(1);
  });

  service->start();

  return 0;
}