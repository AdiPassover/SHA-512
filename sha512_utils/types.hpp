#ifndef SHA_512_TYPES_HPP
#define SHA_512_TYPES_HPP

#include <cstdint>
#include <array>
#include <vector>
#include <cstddef>

constexpr size_t BLOCK_SIZE = 128; // SHA-512 block size in bytes (1024 bits)
constexpr size_t HASH_SIZE = 64; // SHA-512 hash size in bytes (512 bits)
constexpr size_t MESSAGE_SCHEDULE_SIZE = 80; // SHA-512 message schedule size

typedef std::vector<uint8_t> ByteVector;
typedef std::array<uint64_t, BLOCK_SIZE/8> Block;
typedef std::array<uint64_t, HASH_SIZE/8> Hash;
typedef std::array<uint64_t, MESSAGE_SCHEDULE_SIZE> MessageSchedule;


#endif //SHA_512_TYPES_HPP
