#ifndef SHA_512_PREPROCESSING_HPP
#define SHA_512_PREPROCESSING_HPP

#include "types.hpp"

namespace preprocessing {

    ByteVector pad(const ByteVector &data);

    std::vector<Block> parse_blocks(const ByteVector& padded_data);

}

#endif //SHA_512_PREPROCESSING_HPP
