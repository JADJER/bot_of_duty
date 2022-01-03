//
// Created by jadjer on 27.12.2021.
//

#include <Service.hpp>
#include <string>

int main(int argc, char** argv) {
  if (argc != 2) {
    std::cout << argv[0] << " <token>";
    return 1;
  }

  std::string token = argv[1];

  Service service(token);
  service.start();

  return 0;
}