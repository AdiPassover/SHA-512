#include "sha512.hpp"
#include "preprocessing.hpp"
#include "logical_functions.hpp"
#include "constants.hpp"

#include <iostream>


Hash sha512::hash(const ByteVector &data) {
    ByteVector padded_data = preprocessing::pad(data);
    std::vector<Block> blocks = preprocessing::parse_blocks(padded_data);
    Hash h = H0;

    for (Block block : blocks) {
        MessageSchedule w;
        for (size_t t = 0; t < MESSAGE_SCHEDULE_SIZE; ++t) {
            if (t < 16)
                w[t] = block[t];
            else
                w[t] = logical::sigma1(w[t-2]) + w[t-7] + logical::sigma0(w[t-15]) + w[t-16];
        }

        Hash work;
        for (size_t i = 0; i < HASH_SIZE/8; ++i) work[i] = h[i];

        for (size_t t = 0; t < MESSAGE_SCHEDULE_SIZE; ++t) {
            uint64_t t1 = work[7] + logical::big_sigma1(work[4]) + logical::ch(work[4], work[5], work[6]) + K[t] + w[t];
            uint64_t t2 = logical::big_sigma0(work[0]) + logical::maj(work[0], work[1], work[2]);
            work[7] = work[6];
            work[6] = work[5];
            work[5] = work[4];
            work[4] = work[3] + t1;
            work[3] = work[2];
            work[2] = work[1];
            work[1] = work[0];
            work[0] = t1 + t2;
        }

        for (size_t i = 0; i < HASH_SIZE/8; ++i) {
            h[i] += work[i];
        }
    }

    return h;
}