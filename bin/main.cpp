#include <iostream>
#include <cstdio>
#include <vector>
#include <limits>

#include "codec.h"

enum Mode {
    ENCODE,
    DECODE,
    VALIDATE,
    ERROR
};

struct InputArgs {
    Mode mode;
    uint64_t block_bits;
    uint64_t data_bits;
    uint64_t src_bits;
    std::vector<uint8_t> data;
};

int StringToInt(const char *string) {
    if (string == nullptr || string[0] == '\0') {
        return std::numeric_limits<int>::min();
    }
    
    int result = 0;
    int start = 0;
    bool is_negative = false;
    
    if (string[0] == '-') {
        start = 1;
        is_negative = true;
    }
    
    for (int i = start; string[i] != '\0'; i++) {
        if(string[i] < '0' || string[i] > '9') {
            return std::numeric_limits<int>::min();
        }
        result = result * 10 + (string[i] - '0');
    }
    
    if (is_negative) {
        result = -result;
    }
    
    return result;
}

std::vector<uint8_t> ConvertToChanks(std::string bit_sequence) {
    uint64_t bytes = (bit_sequence.length() + 7) / 8;
    std::vector<uint8_t> data(bytes, 0);

    for(int i = 0;i < bit_sequence.length();i++) {
        if(bit_sequence[i] == '0') {
            HammingCodec::SetBit(data.data(), i, 0);
        }
        else {
            HammingCodec::SetBit(data.data(), i, 1);
        }
    }

    return data;
}

InputArgs Parse(int argc, char** argv) {
    InputArgs result;

    std::string mode(argv[1]);
    if(mode == "encode") {
        result.mode = Mode::ENCODE;

        result.block_bits = StringToInt(argv[2]);
        result.block_bits = StringToInt(argv[3]);
        if(result.data_bits < 0 || result.block_bits < 0) {
            result.mode = Mode::ERROR;
            fprintf(stderr, "Hammming: In function Parse(int, char**)\n\tInvalid integer '%s'\nNote: >0\n", argv[2]);
            return result;
        }
        result.src_bits = std::string(argv[4]).length();
        result.data = ConvertToChanks(argv[4]);
    }
    else if(mode == "decode") {
        result.mode = Mode::DECODE;

        result.block_bits = StringToInt(argv[2]);
        if(result.block_bits < 0) {
            result.mode = Mode::ERROR;
            fprintf(stderr, "Hammming: In function Parse(int, char**)\n\tInvalid integer '%s'\nNote: >0\n", argv[2]);
            return result;
        }

        result.src_bits = std::string(argv[3]).length();
        result.data = ConvertToChanks(argv[3]);
    }
    else if(mode == "is_valid") {
        result.mode = Mode::VALIDATE;

        result.block_bits = StringToInt(argv[2]);
        if(result.block_bits < 0) {
            result.mode = Mode::ERROR;
            fprintf(stderr, "Hammming: In function Parse(int, char**)\n\tInvalid integer '%s'\nNote: >0\n", argv[2]);
            return result;
        }

        result.src_bits = std::string(argv[3]).length();
        result.data = ConvertToChanks(argv[3]);
    }
    else {
        result.mode = Mode::ERROR;
        fprintf(stderr, "Hammming: In function Parse(int, char**)\n\tUnkown argument type '%s'\n", argv[1]);
        return result;
    }

    return result;
}

void PrintBits(std::vector<uint8_t>& data, uint64_t total_bits) {
    for(int i = 0;i < total_bits;i++) {
        if(HammingCodec::GetBit(data.data(), i)) {
            std::cout << '1';
        }
        else {
            std::cout << '0';
        }
    }
    std::cout << '\n';
}

int main(int argc, char** argv) {
    InputArgs args = Parse(argc, argv);

    switch (args.mode) {
        case Mode::ENCODE: {
            std::vector<uint8_t> encoded_data = HammingCodec::Encode(args.data.data(), args.src_bits, args.data_bits, args.block_bits);
            PrintBits(encoded_data, HammingCodec::CalculateTotalSize(args.data_bits, args.src_bits));
            break;
        }
        
        default:
            break;
    }
    
    return 0;
}