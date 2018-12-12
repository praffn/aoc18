#include <iostream>
#include "solution.hpp"

namespace aoc18
{

template<>
bool solve<Day::Day06>(std::istream& ins, Solution *solution) {
  solution->first = "Hello, World";
  return true;
}

}
