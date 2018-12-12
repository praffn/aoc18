#include <iostream>
#include <iomanip>
#include <map>
#include <vector>
#include <time.h>
#include <array>
#include <regex>
#include <sstream>
#include "solution.hpp"
#include "util.hpp"

namespace aoc18
{

typedef int guard_id;
typedef std::array<int, 60> sleep_schedule;

static std::regex timestamp_regex(R"(^\[\d{4}-(\d\d)-(\d\d) \d\d:(\d\d)\] (.*)$)");
static std::regex guard_regex(R"(Guard #(\d+) begins shift)");

struct Record
{
  struct tm tm;
  std::string str;
};

std::istream& operator>>(std::istream& ins, Record& record)
{
  // [1518-08-06 00:16] wakes up
  char c;
  record.tm = {};
  //     [                 date                              ]      ws
  ins >> c >> std::get_time(&record.tm, "%Y-%m-%d %H:%M") >> c >> std::ws;
  std::getline(ins, record.str);
  record.tm.tm_year += 400;
  return ins; 
}

// static void print_record(Record& record) {
//   std::cout << "| " << std::put_time(&record.tm, "%c") << std::endl;
//   std::cout << "| \"" << record.str << "\"" << std::endl;
// }

template<>
bool solve<Day::Day04>(std::istream& ins, Solution* solution)
{
  std::vector<Record> records = get_input_vec<Record>(ins);

  std::sort(records.begin(), records.end(),
    [](Record& r1, Record& r2) {
      return std::mktime(&r1.tm) < std::mktime(&r2.tm);
    });

  int current_guard = -1;

  std::map<int, std::array<int, 60>> guard_schedule;

  for (const auto& record : records) {
    // first of all, check if guard has ben mapped.
    // if not, map to zeroed minute array
    if (guard_schedule.find(current_guard) == guard_schedule.end()) {
      guard_schedule[current_guard] = std::array<int, 60>();
      guard_schedule[current_guard].fill(0);
    }

    if (record.str.compare("wakes up") == 0) {
      // current guard wakes up. Increment this minute and all the next!
      for (int i = record.tm.tm_min; i < 60; i++) {
        int current_minute = guard_schedule[current_guard][i];
        guard_schedule[current_guard][i] = current_minute == 0 ? 0 : current_minute - 1;
      }
      continue;
    }

    if (record.str.compare("falls asleep") == 0) {
      for (int i = record.tm.tm_min; i < 60; i++) {
        guard_schedule[current_guard][i]++;
      }
      continue;
    }

    std::smatch guard_matches;
    if (!std::regex_search(record.str, guard_matches, guard_regex)) {
      return false;
    }
    current_guard = std::stoi(guard_matches[1].str());
  }

  // lets find guard who sleeps the most
  int sleepy_guard_id = -1;
  int highest_minute = 0;
  for (const auto& guard : guard_schedule) {
    int sum = 0;
    for (const auto m : guard.second) {
      sum += m;
    }
    if (sum > highest_minute) {
      highest_minute = sum;
      sleepy_guard_id = guard.first;
    }
  }

  // lets find the minute this guard was asleep the most
  int best_minute = -1;
  int best_minute_n = 0;
  for (int i = 0; i < 60; i++) {
    int m = guard_schedule[sleepy_guard_id][i];
    if (m > best_minute_n) {
      best_minute_n = m;
      best_minute = i;
    }
  }

  solution->first = std::to_string(sleepy_guard_id * best_minute);

  int best_guard_id = -1;
  int highest_minute_count = 0;
  int minute = -1;

  for (const auto& guard : guard_schedule) {
    int id = guard.first;
    for (int i = 0; i < 60; i++) {
      int m = guard.second[i];
      if (m > highest_minute_count) {
        highest_minute_count = m;
        minute = i;
        best_guard_id = id;
      }
    }
  }
  
  solution->second = std::to_string(best_guard_id * minute);

  return true;
}

// [1518-07-18 00:14] wakes up1
// [1518-03-23 00:19] falls asleep
// [1518-10-12 23:58] Guard #421 begins shift
// [1518-08-05 00:24] falls asleep
// [1518-09-18 00:48] wakes up
// [1518-08-03 00:57] wakes up

// std::istream& operator>>(std::istream& ins, Claim& Record)
// {
//   char c;
//   //     #                @
//   ins >> c >> claim.id >> c >> claim.left;
//   //     ,                 :
//   ins >> c >> claim.top >> c >> claim.width;
//   //     x
//   ins >> c >> claim.height;
//   return ins;
// }

// map guards to sleep schedule
// sleep schedule maps minutes to how many times theyve been sleeping that minute

// template<>
// bool solve<Day::Day04>(std::istream& ins, Solution* solution)
// {
//   std::map<int, std::array<int, 60>> guard_map;
//   int current_guard = -1;
//   std::smatch matches;
//   // loop through each line
//   for (std::string line; std::getline(ins, line);) {
//     // if it doesnt pass regex, exit early
//     if (!std::regex_search(line, matches, timestamp_regex)) {
//       return false;
//     }
//     // extract info
//     int month = std::stoi(matches[1].str());
//     int day = std::stoi(matches[2].str());
//     int minutes = std::stoi(matches[3].str());
//     std::string str = matches[4].str();

//     if (str.compare("wakes up") == 0) {
//       // if wake up, then decrement or zero minute->59 for current guard
//       if (guard_map.find(current_guard) == guard_map.end()) {
//         guard_map[current_guard] = std::array<int, 60>();
//       }
      
//       for (int i = minutes; i < 60; i++) {
//         const auto current_count = guard_map[current_guard][i];
//         guard_map[current_guard][i] = current_count == 0 ? 0 : (current_count - 1);
//       }
//       continue;
//     }

//     if (str.compare("falls asleep") == 0) {
//       // if falls asleep, then increment minute->59 for current guard
//       if (guard_map.find(current_guard) == guard_map.end()) {
//         guard_map[current_guard] = std::array<int, 60>();
//       }
      
//       for (int i = minutes; i < 60; i++) {
//         guard_map[current_guard][i]++;
//       }
//       continue;
//     }

//     // if neither wake up or falls asleep, it must be guard change
//     // so change current guard to id
//     std::smatch guard_matches;
//     if (!std::regex_search(str, guard_matches, guard_regex)) {
//       return false;
//     }
//     current_guard = std::stoi(guard_matches[1].str());
//   }

//   // now lets loop through the guards and find the one who has the most minutes asleep
//   int longest = 0;
//   int guard_id = -1;
//   for (const auto& g : guard_map) {
//     int total = 0;
//     for (const auto n : g.second) {
//       total += n;
//     }
//     if (total > longest) {
//       longest = total;
//       guard_id = g.first;
//     }
//   }

//   if (guard_id == -1) return false;
  
//   int biggest_minute = 0;
//   int minute = 0;
//   for (int i = 0; i < 60; i++) {
//     if (guard_map[guard_id][i] > biggest_minute) {
//       biggest_minute = guard_map[guard_id][i];
//       minute = i + 1;
//     }
//   }

//   std::cout << (guard_id * minute) << std::endl;

//   return true;
// }

}
