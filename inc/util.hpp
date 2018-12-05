#include <iostream>
#include <vector>

namespace aoc18
{

std::vector<long int> ins_to_vec(std::istream& ins) {
  std::vector<long int> v;
  for (std::string line; std::getline(ins, line);) {
    v.push_back(std::stol(line));
  }
  return v;
}

} // namespace aoc18