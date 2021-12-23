#include "parser.h"
#include <charconv>
#include <cstdint>
#include <cstring>
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
    if (is_numeric(remaining[0])) {
      break;
    } else if (remaining.compare(0, 2, "u8") == 0) {
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
    } else {
      pos++;
    }
  }

  // collect bytes to parse
  while (pos < len) {
    std::string_view remaining {&arg_str.at(pos)};
    if (is_numeric(arg_str[pos])) {
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

  for (uint64_t spec_pos {0}; spec_pos < args.specs.size(); spec_pos++) {
    switch (args.specs[spec_pos]) {
    case Spec::u8: {
      parsed.emplace_back(static_cast<uint8_t>(args.bytes[byte_pos]));
      byte_pos++;
      break;
    }
    case Spec::u16: {
      uint16_t value;
      std::byte bytes[2] {args.bytes[byte_pos + 1], args.bytes[byte_pos]};
      std::memcpy(&value, bytes, sizeof(value));
      parsed.emplace_back(value);
      byte_pos += 2;
      break;
    }
    case Spec::u32: {
      uint32_t value;
      std::byte bytes[4] {args.bytes[byte_pos + 3], args.bytes[byte_pos + 2],
                          args.bytes[byte_pos + 1], args.bytes[byte_pos]};
      std::memcpy(&value, bytes, sizeof(value));
      parsed.emplace_back(value);
      byte_pos += 4;
      break;
    }
    case Spec::u64: {
      uint64_t value;
      std::byte bytes[8] {args.bytes[byte_pos + 7], args.bytes[byte_pos + 6],
                          args.bytes[byte_pos + 5], args.bytes[byte_pos + 4],
                          args.bytes[byte_pos + 3], args.bytes[byte_pos + 2],
                          args.bytes[byte_pos + 1], args.bytes[byte_pos]};
      std::memcpy(&value, bytes, sizeof(value));
      parsed.emplace_back(value);
      byte_pos += 8;
      break;
    }
    case Spec::i8: {
      parsed.emplace_back(static_cast<int8_t>(args.bytes[byte_pos]));
      byte_pos++;
      break;
    }
    case Spec::i16: {
      int16_t value;
      std::byte bytes[2] {args.bytes[byte_pos + 1], args.bytes[byte_pos]};
      std::memcpy(&value, bytes, sizeof(value));
      parsed.emplace_back(value);
      byte_pos += 2;
      break;
    }
    case Spec::i32: {
      int32_t value;
      std::byte bytes[4] {args.bytes[byte_pos + 3], args.bytes[byte_pos + 2],
                          args.bytes[byte_pos + 1], args.bytes[byte_pos]};
      std::memcpy(&value, bytes, sizeof(value));
      parsed.emplace_back(value);
      byte_pos += 4;
      break;
    }
    case Spec::i64: {
      int64_t value;
      std::byte bytes[8] {args.bytes[byte_pos + 7], args.bytes[byte_pos + 6],
                          args.bytes[byte_pos + 5], args.bytes[byte_pos + 4],
                          args.bytes[byte_pos + 3], args.bytes[byte_pos + 2],
                          args.bytes[byte_pos + 1], args.bytes[byte_pos]};
      std::memcpy(&value, bytes, sizeof(value));
      parsed.emplace_back(value);
      byte_pos += 8;
      break;
    }
    case Spec::f32: {
      float value;
      std::byte bytes[4] {args.bytes[byte_pos + 3], args.bytes[byte_pos + 2],
                          args.bytes[byte_pos + 1], args.bytes[byte_pos]};
      std::memcpy(&value, bytes, sizeof(value));
      parsed.emplace_back(value);
      byte_pos += 4;
      break;
    }
    case Spec::f64: {
      double value;
      std::byte bytes[8] {args.bytes[byte_pos + 7], args.bytes[byte_pos + 6],
                          args.bytes[byte_pos + 5], args.bytes[byte_pos + 4],
                          args.bytes[byte_pos + 3], args.bytes[byte_pos + 2],
                          args.bytes[byte_pos + 1], args.bytes[byte_pos]};
      std::memcpy(&value, bytes, sizeof(value));
      parsed.emplace_back(value);
      byte_pos += 8;
      break;
    }
    case Spec::str:
      break;
    }
  }
  return parsed;
}
} // namespace parser
