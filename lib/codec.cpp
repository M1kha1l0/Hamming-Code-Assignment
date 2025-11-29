#include "codec.h"

void HammingCodec::SetBit(void* array, uint64_t index, bool bit) {
    uint8_t* data = static_cast<uint8_t*>(array);
    if(bit) {
        data[index / 8] |= (1 << (index % 8));
    }
    else {
        data[index / 8] &= ~(1 << (index % 8));
    }
}

bool HammingCodec::GetBit(void* array, uint64_t index) {
    uint8_t* data = static_cast<uint8_t*>(array);
    return (data[index / 8] >> (index % 8)) & 1;
}

void HammingCodec::InvertBit(void* array, uint64_t index) {
    uint8_t* data = static_cast<uint8_t*>(array);
    data[index / 8] ^= (1 << (index % 8));
}

uint64_t HammingCodec::CalculateControlBitsCount(uint64_t bytes_block_size) {
    uint64_t result = 0;

    while((1 << result) < (bytes_block_size*8 + result + 1)) {
        result++;
    }

    return result;
}

uint64_t HammingCodec::CalculateTotalSize(uint64_t bytes_block_size) {
    uint64_t bits = CalculateControlBitsCount(bytes_block_size);
    return bytes_block_size + (bits + 7) / 8;
}

uint64_t HammingCodec::CalculateSyndrome(uint8_t* data, uint64_t control_bit_count, uint64_t total_bits) {
    uint64_t syndrome = 0;
    
    for(uint64_t i = 0; i < control_bit_count; i++) {
        uint64_t control_bit_pos = (1 << i);
        
        uint8_t calculated_control_bit = 0;
        for(uint64_t j = 1; j <= total_bits; j++) {
            if(j == control_bit_pos) continue;
            if(j & control_bit_pos) {
                calculated_control_bit ^= GetBit(data, j-1);
            }
        }
        
        if(calculated_control_bit != GetBit(data, control_bit_pos - 1)) {
            syndrome |= control_bit_pos;
        }
    }
    
    return syndrome;
}
            
std::vector<uint8_t> HammingCodec::Encode(void *byte_sequence, uint64_t data_bits, uint64_t control_bits) {
    std::vector<uint8_t> result;
    uint8_t* data = static_cast<uint8_t*>(byte_sequence);
    
    return result;
}

std::vector<uint8_t> HammingCodec::Decode(void* byte_sequence, uint64_t data_bits, uint64_t control_bits) {
    std::vector<uint8_t> result;
    uint8_t* data = static_cast<uint8_t*>(byte_sequence);

    return result;
}