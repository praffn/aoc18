#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "solution.hpp"

namespace aoc18
{

template<>
void solve<Day::Day02>(std::istream& ins, std::ostream& outs) {
  int twos = 0;
  int threes = 0;

  // loop trough all ids
  for (std::string id; std::getline(ins, id);) {
    // make mapping for each character and their respective counts
    std::map<char, int> char_count;
    for (const char c : id) {
      const int value = char_count[c] + 1;
      char_count[c] = value;
    }

    // increment twos/threes if a character appears twice/thrice
    bool two = false;
    bool three = false;
    for (const auto count : char_count) {
      if (count.second == 2) two = true;
      if (count.second == 3) three = true;
    }

    if (two) twos++;
    if (three) threes++;
  }
  // output product
  outs << "first: " << (twos * threes) << std::endl;
}

}
