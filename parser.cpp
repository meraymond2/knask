#include "parser.h"
#include "bytes.h"
#include <charconv>
#include <cstdint>

#include <vector>

namespace parser {

bool is_numeric(uint8_t c) { return c >= 48 && c <= 57; }

ParseArgs tokenise_args(std::string arg_str) {
  uint64_t pos {0};
  std::vector<Spec> specs {};
  std::vector<std::byte> bytes {};
  uint64_t len {arg_str.length()};

  // collect specs
  while (pos < len) {
    std::string_view remaining {&arg_str.at(pos)};
    if (remaining.compare(0, 2, "u8") == 0) {
      specs.push_back(Spec::u8);
      pos += 2;
    } else if (remaining.compare(0, 3, "u16") == 0) {
      specs.push_back(Spec::u16);
      pos += 3;
    } else if (remaining.compare(0, 3, "u32") == 0) {
      specs.push_back(Spec::u32);
      pos += 3;
    } else if (remaining.compare(0, 3, "u64") == 0) {
      specs.push_back(Spec::u64);
      pos += 3;
    } else if (remaining.compare(0, 2, "i8") == 0) {
      specs.push_back(Spec::i8);
      pos += 2;
    } else if (remaining.compare(0, 3, "i16") == 0) {
      specs.push_back(Spec::i16);
      pos += 3;
    } else if (remaining.compare(0, 3, "i32") == 0) {
      specs.push_back(Spec::i32);
      pos += 3;
    } else if (remaining.compare(0, 3, "i64") == 0) {
      specs.push_back(Spec::i64);
      pos += 3;
    } else if (remaining.compare(0, 3, "f32") == 0) {
      specs.push_back(Spec::f32);
      pos += 3;
    } else if (remaining.compare(0, 3, "f64") == 0) {
      specs.push_back(Spec::f64);
      pos += 3;
    } else if (remaining.compare(0, 3, "str") == 0) {
      specs.push_back(Spec::str);
      pos += 3;
    } else if (is_numeric(remaining[0])) {
      // TODO: error handling if number is greater than 255
      uint64_t start {pos};
      while (pos < len && is_numeric(arg_str[pos])) {
        pos++;
      }
      uint8_t i {};
      std::from_chars(remaining.data(), remaining.data() + pos - start, i);
      bytes.push_back(static_cast<std::byte>(i));
    } else {
      pos++;
    }
  }

  return ParseArgs {specs, bytes};
}

std::vector<Parsed> parse(ParseArgs args) {
  std::vector<Parsed> parsed {};
  uint64_t byte_pos {0};

  // TODO: I’m not checking that there are enough bytes remaining for each spec.
  for (auto spec : args.specs) {
    switch (spec) {
    case Spec::u8: {
      parsed.emplace_back(bytes::u8_from_be(&args.bytes.at(byte_pos)));
      byte_pos++;
      break;
    }
    case Spec::u16: {
      parsed.emplace_back(bytes::u16_from_be(&args.bytes.at(byte_pos)));
      byte_pos += 2;
      break;
    }
    case Spec::u32: {
      parsed.emplace_back(bytes::u32_from_be(&args.bytes.at(byte_pos)));
      byte_pos += 4;
      break;
    }
    case Spec::u64: {
      parsed.emplace_back(bytes::u64_from_be(&args.bytes.at(byte_pos)));
      byte_pos += 8;
      break;
    }
    case Spec::i8: {
      parsed.emplace_back(bytes::i8_from_be(&args.bytes.at(byte_pos)));
      byte_pos++;
      break;
    }
    case Spec::i16: {
      parsed.emplace_back(bytes::i16_from_be(&args.bytes.at(byte_pos)));
      byte_pos += 2;
      break;
    }
    case Spec::i32: {
      parsed.emplace_back(bytes::i32_from_be(&args.bytes.at(byte_pos)));
      byte_pos += 4;
      break;
    }
    case Spec::i64: {
      parsed.emplace_back(bytes::i64_from_be(&args.bytes.at(byte_pos)));
      byte_pos += 8;
      break;
    }
    case Spec::f32: {
      parsed.emplace_back(bytes::f32_from_be(&args.bytes.at(byte_pos)));
      byte_pos += 4;
      break;
    }
    case Spec::f64: {
      parsed.emplace_back(bytes::f64_from_be(&args.bytes.at(byte_pos)));
      byte_pos += 8;
      break;
    }
    case Spec::str:
      std::vector<char> s {};
      while (byte_pos < args.bytes.size() &&
             args.bytes[byte_pos] != std::byte {0}) {
        s.push_back(static_cast<char>(args.bytes[byte_pos]));
        byte_pos++;
      }
      // consume null
      byte_pos++;
      s.push_back(0x00);

      parsed.emplace_back(std::string {s.data()});
      break;
    }
  }
  return parsed;
}

} // namespace parser
