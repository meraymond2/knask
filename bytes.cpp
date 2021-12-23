#include "bytes.h"
#include <cstring>

namespace bytes {

/*
 * If complete portability were a concern, I would need to check at runtime
 * whether the current system was little or big endian. I’d also need to be
 * careful that the compiler didn’t simplify it to a compile-time constant.
 *
 * I’m not that worried about it.
 */

uint8_t u8_from_be(std::byte *bs) { return static_cast<uint8_t>(bs[0]); };

uint16_t u16_from_be(std::byte *bs) {
  uint16_t value;
  std::byte bytes[2] {bs[1], bs[0]};
  std::memcpy(&value, bytes, sizeof(value));
  return value;
};

uint32_t u32_from_be(std::byte *bs) {
  uint32_t value;
  std::byte bytes[4] {bs[3], bs[2], bs[1], bs[0]};
  std::memcpy(&value, bytes, sizeof(value));
  return value;
};
uint64_t u64_from_be(std::byte *bs) {
  uint64_t value;
  std::byte bytes[8] {bs[7], bs[6], bs[5], bs[4], bs[3], bs[2], bs[1], bs[0]};
  std::memcpy(&value, bytes, sizeof(value));
  return value;
};

int8_t i8_from_be(std::byte *bs) { return static_cast<int8_t>(bs[0]); };

int16_t i16_from_be(std::byte *bs) {
  int16_t value;
  std::byte bytes[2] {bs[1], bs[0]};
  std::memcpy(&value, bytes, sizeof(value));
  return value;
};

int32_t i32_from_be(std::byte *bs) {
  int32_t value;
  std::byte bytes[4] {bs[3], bs[2], bs[1], bs[0]};
  std::memcpy(&value, bytes, sizeof(value));
  return value;
};

int64_t i64_from_be(std::byte *bs) {
  int64_t value;
  std::byte bytes[8] {bs[7], bs[6], bs[5], bs[4], bs[3], bs[2], bs[1], bs[0]};
  std::memcpy(&value, bytes, sizeof(value));
  return value;
};

float f32_from_be(std::byte *bs) {
  float value;
  std::byte bytes[4] {bs[3], bs[2], bs[1], bs[0]};
  std::memcpy(&value, bytes, sizeof(value));
  return value;
};

double f64_from_be(std::byte *bs) {
  double value;
  std::byte bytes[8] {bs[7], bs[6], bs[5], bs[4], bs[3], bs[2], bs[1], bs[0]};
  std::memcpy(&value, bytes, sizeof(value));
  return value;
};

} // namespace bytes