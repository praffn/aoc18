#include <iostream>
#include <array>
#include "solution.hpp"
#include "util.hpp"

namespace aoc18
{

typedef std::array<std::array<int, 1000>, 1000> Fabric;

struct Claim
{
  int id;
  int left;
  int top;
  int width;
  int height;
};

std::istream& operator>>(std::istream& ins, Claim& claim)
{
  char c;
  //     #                @
  ins >> c >> claim.id >> c >> claim.left;
  //     ,                 :
  ins >> c >> claim.top >> c >> claim.width;
  //     x
  ins >> c >> claim.height;
  return ins;
}

template<>
bool solve<Day::Day03>(std::istream& ins, Solution* solution)
{
  // get claims from input stream
  std::vector<Claim> claims = get_input_vec<Claim>(ins);
  Fabric fabric;
  // fill fabric with 0's
  std::for_each(std::begin(fabric), std::end(fabric),
    [](auto& arr) { arr.fill(0); });
  // for each claim overlap, increment the square on fabric
  std::for_each(std::begin(claims), std::end(claims),
    [&fabric](const Claim& c) {
      for (int i = c.top; i < c.top + c.height; i++) {
        for (int j = c.left; j < c.left + c.width; j++) {
          fabric[i][j]++;
        }
      }
    });

  // lets count the overlaps
  int count = 0;
  for (const auto& l: fabric) {
    for (const auto& i: l) {
      // incr if two or more overlaps
      if (i > 1) count++;
    }
  }

  solution->first = std::to_string(count);

  // now lets figure out which claim does not overlap any other claim
  for (const auto& claim : claims) {
    // for each claim check if "intact"
    bool intact = true;
    for (int i = claim.top; intact && i < claim.top + claim.height; i++) {
      for (int j = claim.left; intact && j < claim.left + claim.width; j++) {
        if (fabric[i][j] != 1) intact = false;
      }
    }
    if (intact) {
      solution->second = std::to_string(claim.id);
      return true;
    }
  }
  return false;
}

}

