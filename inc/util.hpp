#pragma once

#include <iostream>
#include <vector>
#include <string>

namespace aoc18
{

template<class T>
std::vector<T> get_input_vec(std::istream& ins)
{
  std::vector<T> v;
  for (T value; ins >> value;) {
    v.push_back(value);
  }
  return v;
}

} // namespace aoc18
