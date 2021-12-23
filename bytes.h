#ifndef KNASK_BYTES_H
#define KNASK_BYTES_H

#include <cstddef>
#include <cstdint>

namespace bytes {

uint8_t u8_from_be(std::byte *bs);
uint16_t u16_from_be(std::byte *bs);
uint32_t u32_from_be(std::byte *bs);
uint64_t u64_from_be(std::byte *bs);
int8_t i8_from_be(std::byte *bs);
int16_t i16_from_be(std::byte *bs);
int32_t i32_from_be(std::byte *bs);
int64_t i64_from_be(std::byte *bs);
float f32_from_be(std::byte *bs);
double f64_from_be(std::byte *bs);

} // namespace bytes

#endif // KNASK_BYTES_H
