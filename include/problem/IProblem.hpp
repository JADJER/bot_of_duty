//
// Created by jadjer on 12.02.2022.
//

#ifndef BOT_OF_DUTY_INCLUDE_PROBLEM_IPROBLEM_HPP_
#define BOT_OF_DUTY_INCLUDE_PROBLEM_IPROBLEM_HPP_

#include <string>

struct IProblem {
  virtual ~IProblem() = default;
  virtual bool hasProblem(std::string const& problemName) = 0;
  virtual std::string getSolution(std::string const& problemName) = 0;
};

#endif//BOT_OF_DUTY_INCLUDE_PROBLEM_IPROBLEM_HPP_
