#include "logical_functions.hpp"

uint64_t SHR(uint64_t x, unsigned int n);
uint64_t ROTR(uint64_t x, unsigned int n);

constexpr unsigned int BIG_SIGMA0_CONSTANTS[] = { 28, 34, 39 };
constexpr unsigned int BIG_SIGMA1_CONSTANTS[] = { 14, 18, 41 };
constexpr unsigned int SIGMA0_CONSTANTS[]     = { 1, 8, 7 };
constexpr unsigned int SIGMA1_CONSTANTS[]     = { 19, 61, 6 };


namespace logical {

    uint64_t ch(uint64_t x, uint64_t y, uint64_t z) {
        return (x & y) ^ (~x & z);
    }

    uint64_t maj(uint64_t x, uint64_t y, uint64_t z) {
        return (x & y) ^ (x & z) ^ (y & z);
    }

    uint64_t sigma0(uint64_t x) {
        return ROTR(x, SIGMA0_CONSTANTS[0]) ^ ROTR(x, SIGMA0_CONSTANTS[1]) ^ SHR(x, SIGMA0_CONSTANTS[2]);
    }

    uint64_t sigma1(uint64_t x) {
        return ROTR(x, SIGMA1_CONSTANTS[0]) ^ ROTR(x, SIGMA1_CONSTANTS[1]) ^ SHR(x, SIGMA1_CONSTANTS[2]);
    }

    uint64_t big_sigma0(uint64_t x) {
        uint64_t ans = 0;
        for (unsigned int i : BIG_SIGMA0_CONSTANTS) ans ^= ROTR(x, i);
        return ans;
    }

    uint64_t big_sigma1(uint64_t x) {
        uint64_t ans = 0;
        for (unsigned int i : BIG_SIGMA1_CONSTANTS) ans ^= ROTR(x, i);
        return ans;
    }

}


uint64_t SHR(uint64_t x, unsigned int n) {
    return x >> n;
}
uint64_t ROTR(uint64_t x, unsigned int n) {
    return (x >> n) | (x << (64 - n));
}