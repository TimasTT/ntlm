#include "ntlm.hpp"

static const std::string base64_chars =
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz"
        "0123456789+/";

static inline bool is_base64(unsigned char c) {
    return (isalnum(c) || (c == '+') || (c == '/'));
}

static std::string base64_to_bytes(std::string &base64_four_symbols) {  // 4 base64 symbols to 3 bytes transfer
    for (size_t i = 0; i < 4; i++) {
        base64_four_symbols[i] = base64_chars.find(base64_four_symbols[i]);
    }

    std::string three_bytes;
    three_bytes.push_back((base64_four_symbols[0] << 2) + ((base64_four_symbols[1] & 0x30) >> 4));
    three_bytes.push_back(((base64_four_symbols[1] & 0xf) << 4) + ((base64_four_symbols[2] & 0x3c) >> 2));
    three_bytes.push_back(((base64_four_symbols[2] & 0x3) << 6) + base64_four_symbols[3]);

    return three_bytes;
}

static std::string bytes_to_base64(std::string &three_bytes) {  // 3 bytes to 4 base64 symbols transfer
    std::string base64_four_symbols;
    base64_four_symbols.push_back((three_bytes[0] & 0xfc) >> 2);
    base64_four_symbols.push_back(((three_bytes[0] & 0x03) << 4) + ((three_bytes[1] & 0xf0) >> 4));
    base64_four_symbols.push_back(((three_bytes[1] & 0x0f) << 2) + ((three_bytes[2] & 0xc0) >> 6));
    base64_four_symbols.push_back(three_bytes[2] & 0x3f);

    return base64_four_symbols;
}

std::string base64_encode(const std::string &bytes_str) {
    size_t bytes_str_len = bytes_str.size();
    std::string result;

    auto it = bytes_str.begin();
    std::string bytes_array;
    int base64_encode_size = 3; // 3 bytes = 4 base64 symbols.

    while (bytes_str_len--) {
        bytes_array.push_back(*it++);
        if (bytes_array.size() == base64_encode_size) {
            std::string base64_str = bytes_to_base64(bytes_array);

            for (auto base64_symbol: base64_str) {
                result.push_back(base64_chars[base64_symbol]);
            }

            bytes_array.clear();
        }
    }

    if (!bytes_array.empty()) {
        size_t bytes_array_rem = bytes_array.size();

        for (size_t i = bytes_array.size(); i < base64_encode_size; ++i) {
            bytes_array.push_back('\0');
        }

        std::string base64_str = bytes_to_base64(bytes_array);

        for (size_t i = 0; i < bytes_array_rem + 1; ++i) {
            result.push_back(base64_chars[base64_str[i]]);
        }

        while (bytes_array_rem++ < base64_encode_size) {
            result.push_back('=');
        }
    }

    return result;
}

std::string base64_decode(const std::string &base64_str) {
    size_t base64_str_len = base64_str.size();
    std::string result;

    auto it = base64_str.begin();
    std::string base64_array;
    int base64_decode_size = 4; // 3 bytes = 4 base64 symbols.

    while (base64_str_len-- && (*it != '=') && is_base64(*it)) {
        base64_array.push_back(*it++);
        if (base64_array.size() == base64_decode_size) {
            std::string byte_array = base64_to_bytes(base64_array);

            for (auto bytes_array_it: byte_array) {
                result.push_back(bytes_array_it);
            }

            base64_array.clear();
            byte_array.clear();
        }
    }

    if (!base64_array.empty()) {
        size_t base64_array_rem = base64_array.size();
        for (size_t i = base64_array.size(); i < base64_decode_size; ++i) {
            base64_array[i] = 0;
        }

        std::string byte_array = base64_to_bytes(base64_array);

        for (size_t i = 0; i < base64_array_rem - 1; ++i) {
            result.push_back(byte_array[i]);
        }
    }

    return result;
}
