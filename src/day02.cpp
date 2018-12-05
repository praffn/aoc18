#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "solution.hpp"
#include "util.hpp"

namespace aoc18
{

static int string_difference(const std::string& a, const std::string &b, std::string *out) {
  std::vector<char> mv;
  int difference = 0;
  for (size_t i = 0; i < a.length(); i++) {
    if (a[i] != b[i]) {
      difference++;
      continue;
    }
    mv.push_back(a[i]);
  }
  *out = std::string(mv.begin(), mv.end());
  return difference;
}

static int first(const std::vector<std::string>& ids) {
  int twos = 0;
  int threes = 0;

  // loop trough all ids
  for (const std::string id : ids) {
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
  // return product
  return twos * threes;
}

static std::string second(const std::vector<std::string>& ids) {
  for (const std::string id : ids) {
    for (const std::string other_id : ids) {
      if (id.compare(other_id) == 0 || id.length() != other_id.length()) continue;
      std::string mask;
      if (string_difference(id, other_id, &mask) == 1) {
        return mask;
      }
    }
  }
  return "WRONG";
}

template<>
void solve<Day::Day02>(std::istream& ins, std::ostream& outs) {
  const std::vector<std::string> ids = ins_to_str_vec(ins);
  outs << "first: " << first(ids) << std::endl;
  outs << "second: " << second(ids) << std::endl;
}

}
