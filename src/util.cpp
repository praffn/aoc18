#include "util.hpp"

namespace aoc18
{
  
std::vector<long int> ins_to_long_vec(std::istream& ins) {
  std::vector<long int> v;
  for (std::string line; std::getline(ins, line);) {
    v.push_back(std::stol(line));
  }
  return v;
}

std::vector<std::string> ins_to_str_vec(std::istream& ins) {
  std::vector<std::string> v;
  for (std::string line; std::getline(ins, line);) {
    v.push_back(line);
  }
  return v; 
}

} // namespace aoc18
