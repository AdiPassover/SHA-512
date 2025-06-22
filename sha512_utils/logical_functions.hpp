#ifndef SHA_512_LOGICAL_FUNCTIONS_HPP
#define SHA_512_LOGICAL_FUNCTIONS_HPP

#include <cstdint>

namespace logical {

    uint64_t ch(uint64_t x, uint64_t y, uint64_t z);
    uint64_t maj(uint64_t x, uint64_t y, uint64_t z);
    uint64_t sigma0(uint64_t x);
    uint64_t sigma1(uint64_t x);
    uint64_t big_sigma0(uint64_t x);
    uint64_t big_sigma1(uint64_t x);

}

#endif //SHA_512_LOGICAL_FUNCTIONS_HPP
