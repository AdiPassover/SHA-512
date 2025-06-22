cmake_minimum_required(VERSION 3.27)
project(SHA_512)

set(CMAKE_CXX_STANDARD 17)

add_executable(SHA_512 main.cpp
        sha512_utils/logical_functions.cpp
        sha512_utils/constants.hpp
        sha512_utils/preprocessing.hpp
        sha512_utils/preprocessing.cpp
        sha512_utils/types.hpp
        sha512_utils/sha512.hpp
        sha512_utils/sha512.cpp)
