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
    uint64_t total_bits;
    uint64_t data_bits;
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
    uint64_t byte_counts = (bit_sequence.length() + 7) / 8;
    std::vector<uint8_t> data;
    data.resize(byte_counts, 0);

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
    std::vector<uint8_t> data;
    if(mode == "encode") {
        result.mode = Mode::ENCODE;

        result.total_bits = StringToInt(argv[2]);
        result.total_bits = StringToInt(argv[3]);
        if(result.data_bits < 0 || result.total_bits < 0) {
            result.mode = Mode::ERROR;
            fprintf(stderr, "Hammming: In function Parse(int, char**)\n\tInvalid integer '%s'\nNote: >0\n", argv[2]);
            return result;
        }

        result.data = ConvertToChanks(argv[4]);
    }
    else if(mode == "decode") {
        result.mode = Mode::DECODE;

        result.total_bits = StringToInt(argv[2]);
        if(result.total_bits < 0) {
            result.mode = Mode::ERROR;
            fprintf(stderr, "Hammming: In function Parse(int, char**)\n\tInvalid integer '%s'\nNote: >0\n", argv[2]);
            return result;
        }

        result.data = ConvertToChanks(argv[3]);
    }
    else if(mode == "is_valid") {
        result.mode = Mode::VALIDATE;

        result.total_bits = StringToInt(argv[2]);
        if(result.total_bits < 0) {
            result.mode = Mode::ERROR;
            fprintf(stderr, "Hammming: In function Parse(int, char**)\n\tInvalid integer '%s'\nNote: >0\n", argv[2]);
            return result;
        }

        result.data = ConvertToChanks(argv[3]);
    }
    else {
        result.mode = Mode::ERROR;
        fprintf(stderr, "Hammming: In function Parse(int, char**)\n\tUnkown argument type '%s'\n", argv[1]);
        return result;
    }

    return result;
}

void PrintBits(std::vector<uint8_t>& bits, uint64_t bits_count) {
    for(int i = 0;i < bits_count;i++) {
        if(HammingCodec::GetBit(bits.data(), i)) {
            fprintf(stdout, "1");
        }
        else {
            fprintf(stdout, "0");
        }
    }
    fprintf(stdout, "\n");
}

int main(int argc, char** argv) {
    InputArgs args = Parse(argc, argv);

    switch (args.mode) {
        case Mode::ENCODE: {
            std::vector<uint8_t> encoded_data = HammingCodec::Encode(args.data.data(), args.data_bits, args.total_bits);
            PrintBits(encoded_data, args.total_bits);
            break;
        }
        
        case Mode::DECODE: {
            std::vector<uint8_t> decoded_data = HammingCodec::Decode(args.data.data(), args.total_bits);
            PrintBits(decoded_data, args.total_bits);
            break;
        }
        
        case Mode::VALIDATE: {
            fprintf(stdout, "%d\n", HammingCodec::IsValid(args.data.data(), args.total_bits));
            break;
        }
            
        default: {
            return 1;
        }
    }
    
    return 0;
}