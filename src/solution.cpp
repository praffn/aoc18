#include <iostream>
#include <string>
#include <sstream>
#include "solution.hpp"

namespace aoc18
{

std::string day_to_string(Day d)
{
  std::stringstream ss;
  ss << "Day " << d;
  return ss.str();
}

}
