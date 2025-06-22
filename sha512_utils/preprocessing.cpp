#include "preprocessing.hpp"

#include <stdexcept>

namespace preprocessing {

    ByteVector pad(const ByteVector &data) {
        ByteVector padded_data = data;
        padded_data.push_back(0x80);
        while ((data.size() * 8) % (BLOCK_SIZE*8) != (BLOCK_SIZE*8)-BLOCK_SIZE) {
            padded_data.push_back(0x00);
        }

        size_t original_size = data.size();
        __uint128_t original_num_bits = static_cast<__uint128_t>(original_size) * 8;
        for (int i = 15; i >= 0; --i) {
            padded_data.push_back(static_cast<uint8_t>((original_num_bits >> (i * 8)) & 0xFF));
        }

        return padded_data;
    }

    std::vector<Block> parse_blocks(const ByteVector & padded_data) {
        if (padded_data.size() % BLOCK_SIZE != 0)
            throw std::runtime_error("Padded data size (" + std::to_string(padded_data.size()) +
                    ") is not a multiple of the block size (" + std::to_string(BLOCK_SIZE) + " bytes)");

        size_t num_blocks = padded_data.size() / BLOCK_SIZE;
        std::vector<Block> blocks;
        blocks.reserve(num_blocks);

        for (size_t i = 0; i < num_blocks; ++i) {
            Block block;
            for (size_t j = 0; j < BLOCK_SIZE/8; ++j) {
                block[j] = 0;
                for (size_t k = 0; k < 8; ++k) {
                    block[j] |= static_cast<uint64_t>(padded_data[i*BLOCK_SIZE + j*8 + k]) << (56 - k*8);
                }
            }
            blocks.push_back(block);
        }

        return blocks;
    }

}