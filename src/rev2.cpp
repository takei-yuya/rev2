#include <iostream>
#include <fstream>
#include <string>

#include <stdlib.h>
#include <getopt.h>

#include "splitter.hpp"
#include "config.h"

void Usage(std::ostream& ofs, int argc, char** argv)
{
  ofs
    << "Usage: " << argv[0] << " [OPTION...] [FILE]..." << std::endl
    << "reverse lines of input" << std::endl
    << std::endl
    << "  -n, --length=NUM           reverse line by each NUM-chars." << std::endl
    << "  -d, --delim=DELIMS         reverse line in words split by DELIMS" << std::endl
    << "  -j, --join=JOIN            join each sub-string by JOIN" << std::endl
    << "  -h, --help                 display this help and exit" << std::endl
    << "  -v, --version              display version information and exit" << std::endl
    << "" << std::endl
    << "If no FILEs are specified, the standard input is read" << std::endl
    << "If JOIN is not given, use empty string for length, or use first char of DELIMS for words" << std::endl
    << "" << std::endl
    << "e.g." << std::endl
    << "echo \"foo bar baz\" | " << argv[0] << "             # \"zab rab oof\"" << std::endl
    << "echo \"foobarbaz\"   | " << argv[0] << " -n3         # \"bazbarfoo\"" << std::endl
    << "echo \"foo,bar,baz\" | " << argv[0] << " -d,         # \"baz,bar,foo\"" << std::endl
    << "echo \"foo,bar,baz\" | " << argv[0] << " -d, -j' '   # \"baz bar foo\"" << std::endl
    << "echo \"foo,bar+baz\" | " << argv[0] << " -d,+        # \"baz,bar,foo\"" << std::endl
    ;
}

std::string Reverse(Splitter* splitter, const std::string& join, const std::string& str)
{
  std::string result;

  Splitter::Bounds bounds;
  splitter->Split(str, bounds);
  while (!bounds.empty()) {
    const Splitter::Bound& bound = bounds.back();
    result.append(str.begin() + bound.first, str.begin() + bound.second);

    bounds.pop_back();
    if (bounds.empty()) {
      break;
    }
    result.append(join);
  }

  return result;
}



int main(int argc, char** argv)
{
  SplitterOption splitter_option;
  splitter_option.type = SplitterOption::SPLITTER_TYPE_LENGTH;
  splitter_option.length = 1;

  std::string join;
  bool join_given = false;

  while (true) {
    static struct option long_options[] = {
      { "length", required_argument, 0, 'n' },
      { "delim", required_argument, 0, 'd' },
      { "join", required_argument, 0, 'j' },
      { "help", no_argument, 0, 'h' },
      { "version", no_argument, 0, 'v' },
      { 0, 0, 0, 0 },
    };
    int c = getopt_long(argc, argv, "n:d:j:hv", long_options, NULL);
    if (c == -1) break;

    switch (c) {
    case 'n':
      splitter_option.type = SplitterOption::SPLITTER_TYPE_LENGTH;
      splitter_option.length = atoi(optarg);
      break;
    case 'd':
      splitter_option.type = SplitterOption::SPLITTER_TYPE_WORD;
      splitter_option.delims = optarg;
      if (!join_given) join = optarg[0];
      break;
    case 'j':
      join = optarg;
      join_given = true;
      break;
    case 'h':
      Usage(std::cout, argc, argv);
      return 0;
    case 'v':
      std::cout << PACKAGE_STRING << std::endl;
      return 0;
    default:
      Usage(std::cerr, argc, argv);
      return -1;
    }
  }

  Splitter* splitter = CreateSplitter(splitter_option);

  if (optind < argc) {
    std::string line;
    for (int i = optind; i < argc; ++i) {
      std::ifstream ifs(argv[i]);
      while(std::getline(ifs, line)) {
        std::cout << Reverse(splitter, join, line) << std::endl;
      }
    }
  } else {
    std::string line;
    while(std::getline(std::cin, line)) {
      std::cout << Reverse(splitter, join, line) << std::endl;
    }
  }

  delete splitter;
  return 0;
}

