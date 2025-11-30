#pragma once
#include <cstdio>
#include <cstdint>
#include <vector>

class HammingCodec {
    private:
        static uint64_t CalculateControlBitsCount(uint64_t total_bits);
    
        static uint64_t CalculateTotalSize(uint64_t bytes_block_size);
    
        static uint64_t CalculateSyndrome(uint8_t* data, uint64_t control_bit_count, uint64_t total_bits);

    public:
        static void SetBit(void* array, uint64_t index, bool value);

        static bool GetBit(void* array, uint64_t index);

        static void InvertBit(void* array, uint64_t index);
            
        static std::vector<uint8_t> Encode(void* byte_sequence, uint64_t data_bits, uint64_t total_bits);

        static bool IsValid(void* byte_sequence, uint64_t total_bits);

        static std::vector<uint8_t> Decode(void* byte_sequence, uint64_t total_bits);
};