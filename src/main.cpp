#include <iostream>
#include <fstream>
#include <ios>

#include "solution.hpp"

int main(int argc, char** argv) {
  // check if day is given
  if (argc < 2) {
    std::cerr << "You must supply a day" << std::endl;
    return 1;
  }
  // check if infile
  std::istream *ins;
  if (argc > 2) {
    ins = new std::ifstream(argv[2], std::ios::in);
    if (!ins->good()) {
      std::cerr << "error opening file '" << argv[2] << "'" << std::endl;
      return 2;
    }
  } else {
    ins = &std::cin;
  }

  switch (std::atoi(argv[1])) {
    case 1: aoc18::solve<aoc18::Day::Day01>(*ins, std::cout); break;
    default:
      std::cerr << "Unknown day '" << argv[1] << "'" << std::endl;
      return 3;
  }
}

