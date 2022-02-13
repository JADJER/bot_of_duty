//
// Created by jadjer on 12.02.2022.
//

#ifndef BOT_OF_DUTY_INCLUDE_PROBLEM_PROBLEMIMPL_HPP_
#define BOT_OF_DUTY_INCLUDE_PROBLEM_PROBLEMIMPL_HPP_

#include <problem/IProblem.hpp>

class ProblemImpl : public IProblem {
 public:
  ProblemImpl() = delete;
  explicit ProblemImpl(std::string const& pathFile);

  ~ProblemImpl() override;

 public:
  bool hasProblem(std::string const& problemName) override;
  std::string getSolution(std::string const& problemName) override;
};

#endif//BOT_OF_DUTY_INCLUDE_PROBLEM_PROBLEMIMPL_HPP_
