#include <iostream>
#include <stdexcept>
#include "sha512_utils/types.hpp"
#include "sha512_utils/sha512.hpp"

ByteVector str_to_bytes(char* string);
ByteVector file_to_bytes(char* file_path);

int main(int argc, char* argv[]) {

    if (argc != 3)
        throw std::length_error("Expected 3 arguments.");

    ByteVector plaintext;
    if (argv[1][1] == 's')
        plaintext = str_to_bytes(argv[2]);
    else if (argv[1][1] == 'f')
        plaintext = file_to_bytes(argv[2]);
    else
        throw std::invalid_argument("Only supports hashing a string [-s] or a file [-f]");

    Hash hash = sha512::hash(plaintext);
    ByteVector hash_bytes;
    for (uint64_t block : hash) {
        for (int i = 0; i < 8; ++i)
            hash_bytes.push_back(static_cast<uint8_t>((block >> (56 - i * 8)) & 0xFF));
    }

    for (uint8_t byte : hash_bytes) {
        printf("%02x", byte);
    }
    std::cout << std::endl;

    return 0;
}


ByteVector str_to_bytes(char* string) {
    ByteVector bytes;
    while (*string) {
        bytes.push_back(static_cast<uint8_t>(*string));
        string++;
    }
    return bytes;
}

ByteVector file_to_bytes(char* file_path) {
    ByteVector bytes;
    FILE* file = fopen(file_path, "rb");
    if (!file) {
        throw std::runtime_error("Could not open file: " + std::string(file_path));
    }

    uint8_t buffer[1024];
    size_t bytes_read;
    while ((bytes_read = fread(buffer, 1, sizeof(buffer), file)) > 0) {
        bytes.insert(bytes.end(), buffer, buffer + bytes_read);
    }

    fclose(file);
    return bytes;
}