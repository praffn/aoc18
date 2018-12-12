#include <iostream>
#include <fstream>
#include <ios>
#include <unistd.h>

#include "solution.hpp"

void usage();
void run_day(std::istream& ins, int day, bool benchmark);

int main(int argc, char **argv)
{
  std::istream *ins = NULL;
  std::ifstream *fins = NULL;
  bool benchmark = false;
  char *filename = NULL;
  int day = 0;

  char c;
  bool err = false;
  while ((c = getopt(argc, argv, "bi:")) != -1) {
    switch (c) {
    case 'b':
      benchmark = true;
      break;
    case 'i':
      filename = optarg;
      break;
    case '?':
      err = true;
      break;
    }
  }

  if (optind < argc) {
    day = std::atoi(argv[optind]);
    if (day < 1 || day > 25) {
      std::cerr << "unknown day \"" << argv[optind] << "\"" << std::endl;
    }
  } else {
    std::cerr << "you must supply a date" << std::endl;
    err = true;
  }

  if (filename != NULL) {
    fins = new std::ifstream(filename, std::ios::in);
    if (!fins->good()) {
      std::cerr << "error opening file \"" << filename << "\"" << std::endl;
      err = true;
    }
    ins = fins;
  } else {
    ins = &std::cin;
  }

  if (err) {
    usage();
    exit(EXIT_FAILURE);
  }

  run_day(*ins, day, benchmark);
  if (fins != NULL) fins->close();
}

void usage()
{
  std::cerr << "usage: aoc18 [-b] [-i filename] day" << std::endl;
  std::cerr << "   -b"  << '\t' << "benchmark" << std::endl;
  std::cerr << "   -i"  << '\t' << "input file. if not supplied stdin will be used" << std::endl;
  std::cerr << "   day" << '\t' << "the day to run. Must be int in range 1-25" << std::endl;
}

void run_day(std::istream& ins, int day, bool benchmark) {
  bool (*solver)(std::istream& ins, aoc18::Solution* solution) = nullptr;
  switch (day) {
  case 01: solver = aoc18::solve<aoc18::Day::Day01>; break;
  case 02: solver = aoc18::solve<aoc18::Day::Day02>; break;
  case 03: solver = aoc18::solve<aoc18::Day::Day03>; break;
  case 04: solver = aoc18::solve<aoc18::Day::Day04>; break;
  case 05: solver = aoc18::solve<aoc18::Day::Day05>; break;
  case 06: solver = aoc18::solve<aoc18::Day::Day06>; break;
  default:
    std::cerr << "day " << day << "is not yet implemented" << std::endl;
    return;
  }

  aoc18::Solution solution;
  std::clock_t start, end;
  start = std::clock();
  if (!solver(ins, &solution)) {
    std::cerr << "error running day " << day << std::endl;
    return;
  }
  end = std::clock();
  double cpu_time = ((double) (end - start)) / CLOCKS_PER_SEC;

  std::cout << "+------------------------" << std::endl;
  std::cout << "| DAY " << day << std::endl;
  std::cout << "|" << std::endl;
  std::cout << "| First : " << solution.first << std::endl;
  std::cout << "| Second: " << solution.second << std::endl;
  if (benchmark) {
    std::cout << "|" << std::endl << "| Runtime: " << cpu_time << std::endl;
  }
  std::cout << "+------------------------" << std::endl;
}
