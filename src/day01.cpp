#include <iostream>
#include <set>
#include <vector>
#include "solution.hpp"
#include "util.hpp"

namespace aoc18
{
  template<>
  void solve<Day::Day01>(std::istream& ins, std::ostream& outs)
  {
    std::string line;
    long int frequency = 0;
    std::set<long int> freq_set;
    std::vector<long int> freqs = ins_to_long_vec(ins);

    // first
    for (const long int value : freqs) {
      frequency += value;
    }

    outs << "first: " << frequency << std::endl;

    // second
    frequency = 0;
    while (true) {
      for (const long int value : freqs) {
        frequency += value;
        if (freq_set.find(frequency) != freq_set.end()) {
          outs << "second: " << frequency << std::endl;
          return;
        }
        freq_set.insert(frequency);
      }
    }
  }
}
