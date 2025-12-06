#pragma once
#include <cstdio>
#include <cstdint>
#include <vector>

class HammingCodec {
    public:
        static uint64_t CalculateControlBitsCount(uint64_t data_bits);
    
        static uint64_t CalculateTotalSize(uint64_t data_bits, uint64_t src_bits);
    
        static uint64_t CalculateSyndrome(uint8_t* data, uint64_t control_bit_count, uint64_t total_bits);

        static void SetBit(void* array, uint64_t index, bool value);

        static bool GetBit(void* array, uint64_t index);

        static void InvertBit(void* array, uint64_t index);
            
        static std::vector<uint8_t> Encode(void *byte_sequence, uint64_t src_bits, uint64_t data_bits, uint64_t block_bits);

        static std::vector<uint8_t> Decode(void* byte_sequence, uint64_t total_bits);
};