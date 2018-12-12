#include <iostream>
#include <vector>
#include <set>
#include <ctype.h>
#include "solution.hpp"

namespace aoc18
{

static bool same_type(char c, char d)
{
  return tolower(c) == tolower(d);
}

static bool same_polarity(char c, char d) {
  return (
    (c >= 'A' && c <= 'Z' && d >= 'A' && d <= 'Z') ||
    (c >= 'a' && c <= 'z' && d >= 'a' && d <= 'z')
  );
}

// returns the count of the reduced polymer
static int reduce(const std::string polymer_str)
{
  std::vector<char> units(polymer_str.begin(), polymer_str.end());
  auto it = units.begin();
  while (it != units.end() && (it + 1) != units.end()) {
    const char current_c = *it;
    const char next_c = *(it + 1);
    if (same_type(current_c, next_c) && !same_polarity(current_c, next_c)) {
      units.erase(it + 1);
      it = units.erase(it);
      if (it != units.begin()) {
        it--;
      }
    } else {
      it++;
    }
  }

  return units.size();
}

static std::set<char> get_types(const std::string str)
{
  std::set<char> s;
  for (const auto c : str) {
    s.insert(tolower(c));
  }
  return s;
}

static std::string create_polymer_without_type(std::string polymer_str, char type)
{
  std::vector<char> v;
  for (const auto c : polymer_str) {
    if (tolower(c) == tolower(type)) continue;
    v.push_back(c);
  }
  return std::string(v.begin(), v.end());
}

template<>
bool solve<Day::Day05>(std::istream& ins, Solution* solution)
{
  std::string polymer_str;
  std::getline(ins, polymer_str);

  solution->first = std::to_string(reduce(polymer_str));

  const auto types = get_types(polymer_str);
  int shortest = 1000000;
  for (const auto type : types) {
    std::string polymer = create_polymer_without_type(polymer_str, type);
    int len = reduce(polymer);
    shortest = len < shortest
      ? len
      : shortest;
  }
  solution->second = std::to_string(shortest);
  return true;
}

} // namespace aoc18
