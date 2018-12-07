#include <iostream>
#include <set>
#include <vector>
#include "solution.hpp"
#include "util.hpp"

namespace aoc18
{
  template<>
  bool solve<Day::Day01>(std::istream& ins, Solution* solution)
  {
    std::string line;
    long int frequency = 0;
    std::set<long int> freq_set;
    auto freqs = get_input_vec<long int>(ins);

    // first
    for (const auto& value : freqs) {
      frequency += value;
    }

    solution->first = std::to_string(frequency);

    // second
    frequency = 0;
    while (true) {
      for (const auto& value : freqs) {
        frequency += value;
        if (freq_set.find(frequency) != freq_set.end()) {
          solution->second = std::to_string(frequency);
          return true;
        }
        freq_set.insert(frequency);
      }
    }

    return false;
  }
}
