#include <iostream>
#include <variant>
#include <vector>

#include "parser.h"

std::string concat_args(char *args[], int size) {
  std::string concatenated {};
  // can’t use the range-based for-loop on arrays, so old style loop
  for (uint64_t i = 0; i < size; i++) {
    // will add whitespace to the first element, which is ok here,
    // because whitespace is ignored, except as a delimiter between numbers
    concatenated.append(" ");
    concatenated.append(args[i]);
  }
  return concatenated;
}

int main(int argc, char *argv[]) {
  // 1. Concatenate arguments into single string
  // the pointer + 1 is implicitly ptr + 1 * sizeof(char*)
  // so it’s not necessary to add the exact # of bytes to the ptr
  std::string arg_string {concat_args(argv + 1, argc - 1)};
  // 2. Tokenise argument-string
  parser::ParseArgs to_parse {parser::tokenise_args(arg_string)};
  // 3. Parse bytes according to specs
  std::vector<parser::Parsed> parsed {parser::parse(to_parse)};
  // 4. Print output
  for (parser::Parsed val : parsed) {
    // still a little hazy on std::visit, but as I understand it, it
    // is the nearest equivalent to pattern matching on a std::variant
    std::visit(parser::PrintParsed(), val);
  }
  return 0;
}
