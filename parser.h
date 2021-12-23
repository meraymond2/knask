#include <iostream>
#include <variant>
#include <vector>

#ifndef KNASK_PARSER_H
#define KNASK_PARSER_H

namespace parser {

enum class Spec { u8, u16, u32, u64, i8, i16, i32, i64, f32, f64, str };

typedef std::variant<uint8_t, uint16_t, uint32_t, uint64_t, int8_t, int16_t,
                     int32_t, int64_t, float, double, std::string>
    Parsed;

struct ParseArgs {
  std::vector<Spec> specs;
  std::vector<std::byte> bytes;

  ParseArgs(std::vector<Spec> specs, std::vector<std::byte> bytes)
      : specs(std::move(specs)), bytes(std::move(bytes)) {}
};

ParseArgs tokenise_args(std::string arg_str);

std::vector<Parsed> parse(ParseArgs args);

struct PrintParsed {
  void operator()(uint8_t &val) {
    std::cout << "u8: " << static_cast<uint16_t>(val) << std::endl;
  }

  void operator()(uint16_t &val) { std::cout << "u16: " << val << std::endl; }

  void operator()(uint32_t &val) { std::cout << "u32: " << val << std::endl; }

  void operator()(uint64_t &val) { std::cout << "u64: " << val << std::endl; }

  void operator()(int8_t &val) {
    std::cout << "i8: " << static_cast<int16_t>(val) << std::endl;
  }

  void operator()(int16_t &val) { std::cout << "i16: " << val << std::endl; }

  void operator()(int32_t &val) { std::cout << "i32: " << val << std::endl; }

  void operator()(int64_t &val) { std::cout << "i64: " << val << std::endl; }

  void operator()(float &val) { std::cout << "f32: " << val << std::endl; }

  void operator()(double &val) { std::cout << "f64: " << val << std::endl; }

  void operator()(std::string &val) {
    std::cout << "str: " << val << std::endl;
  }
};

} // namespace parser
#endif // KNASK_PARSER_H
