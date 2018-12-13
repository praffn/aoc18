#include <iostream>
#include <vector>
#include <array>
#include "solution.hpp"
#include "util.hpp"

namespace aoc18
{

struct Coord
{
  int x;
  int y;

  Coord() {}
  Coord(int x, int y) : x(x), y(y) {}
};

std::istream& operator>>(std::istream& ins, Coord& point)
{
  char c;
  ins >> point.x >> c >> point.y;
  return ins;
}

static int manhattan_dist(const Coord& a, const Coord& b)
{
  return std::abs(a.x - b.x) + std::abs(a.y - b.y);
}

static void get_bounding_box(const std::vector<Coord>& coords, int& min_x, int& min_y, int& max_x, int& max_y)
{
  min_x = min_y = -1;
  max_x = max_y = 0;
  for (const auto& coord : coords) {
    min_x = coord.x < min_x ? coord.x : min_x;
    min_y = coord.y < min_y ? coord.x : min_y;
    max_x = coord.x > max_x ? coord.x : max_x;
    max_y = coord.y > max_y ? coord.x : max_y;
  }
}

static bool index_of_owned_coord(const Coord& coord, const std::vector<Coord>& coords, size_t& index)
{
  int lowest_dist = 1000000;
  index = -1;
  bool tied = false;
  for (size_t i = 0; i < coords.size(); i++) {
    const auto& c_coord = coords[i];
    int dist = manhattan_dist(c_coord, coord);
    if (dist == 0) {
      index = i;
      return true;
    }
    if (dist == lowest_dist) {
      // if equal we got a tie. set tied flag
      tied = true;
    } else if (dist < lowest_dist) {
      lowest_dist = dist;
      index = i;
      tied = false;
    }
  }

  return !tied;
}

/**
 * General idea:
 * 1) Parse all points
 * 2) Find bounding box (±1)
 * 4) For each coordinate c in bounding box
 *   4.1) For each point p in points
 *     4.1.1) get distance d from c to p
 *     4.1.2) if d == 0 return index of p
 *     4.1.3) else if d < lowest_dist
 *       4.1.3.1) lowest_dist = d; lowest_idx = index of p
 *     4.1.4) else if d == lowest_dist then return -1 (tied)
 */
template<>
bool solve<Day::Day06>(std::istream& ins, Solution* solution)
{
  const auto& coords = get_input_vec<Coord>(ins);
  int min_x, min_y, max_x, max_y;
  get_bounding_box(coords, min_x, min_y, max_x, max_y);

  std::vector<int> areas;
  areas.assign(coords.size(), 0);

  for (int y = min_y-1; y <= max_y+1; y++) {
    for (int x = min_x-1; x <= max_x+1; x++) {
      Coord coord(x, y);
      size_t index;
      if (index_of_owned_coord(coord, coords, index)) {
        if (x == min_x || x == max_x || y == min_y || y == max_y) {
          areas[index] = -1;
        } else if (areas[index] >= 0) {
          areas[index]++;
        }
      }
    }
  }

  int largest = -1;
  for (const auto area : areas) {
    largest = area > largest ? area : largest;
  }

  solution->first = std::to_string(largest);
  return true;
}

}
