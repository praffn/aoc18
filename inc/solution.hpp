#pragma once

#include <iostream>
#include <string>

namespace aoc18
{

enum Day
{
  DayUnknown,
  Day01, Day02, Day03, Day04, Day05,
  Day06, Day07, Day08, Day09, Day10,
  Day11, Day12, Day13, Day14, Day15,
  Day16, Day17, Day18, Day19, Day20,
  Day21, Day22, Day23, Day24, Day25,
};

struct Solution
{
  std::string first;
  std::string second;
};

std::string day_to_string(Day d);

template<Day D>
bool solve(std::istream& ins, Solution* solution);

} //namespace aoc18
