#include <iostream>
#include <vector>
#include <variant>
#include "parser.h"

std::string concat_args(char *args[], int size) {
    std::string concatenated{};
    if (size > 0) {
        concatenated.append(args[0]);
    }
    for (int i = 1; i < size; i++) {
        concatenated.append(" ");
        concatenated.append(args[i]);
    }
    return concatenated;
}

int main(int argc, char *argv[]) {
    // 1. Concatenate arguments into string
    std::string arg_string{concat_args(argv + 1, argc - 1)}; // the + 1 is implicitly + 1 * sizeof(char *)
    // 2. Tokenise argument-string
    parser::ParseArgs to_parse {parser::tokenise_args(arg_string)};
    // 3. Parse bytes according to specs
    std::vector<parser::Parsed> parsed{parser::parse(to_parse)};
    // 4. Print output
    for (parser::Parsed val: parsed) {
        std::visit(parser::PrintParsed(), val);
    }
    return 0;
}
