//
// Created by jadjer on 12.02.2022.
//

#include "problem/ProblemImpl.hpp"

ProblemImpl::ProblemImpl(std::string const& pathFile) {

}

ProblemImpl::~ProblemImpl() = default;

bool ProblemImpl::hasProblem(std::string const& problemName) {
  return false;
}
std::string ProblemImpl::getSolution(std::string const& problemName) {
  return std::string();
}

