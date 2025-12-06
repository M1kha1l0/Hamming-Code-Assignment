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

uint64_t HammingCodec::CalculateControlBitsCount(uint64_t total_bits) {
    uint64_t result = 0;

    while((1 << result) < (total_bits + result + 1)) {
        result++;
    }

    return result;
}

uint64_t HammingCodec::CalculateTotalSize(uint64_t data_bits, uint64_t src_bits) {
    uint64_t data_blocks = (src_bits + data_bits - 1) / data_bits;
    return data_blocks * CalculateControlBitsCount(data_bits) + src_bits;
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
            
std::vector<uint8_t> HammingCodec::Encode(void *byte_sequence, uint64_t src_bits, uint64_t data_bits, uint64_t block_bits) {
    std::vector<uint8_t> encoded_data((CalculateTotalSize(data_bits, src_bits) + 7) / 8, 0);
    uint8_t* data = static_cast<uint8_t*>(byte_sequence);

    for(int i = 0; i < src_bits; i += data_bits) {
        for(int j = 0; j < data_bits;j++) {
            // выбираем блоки по data_bits
            // кодируем
            // итоговую последовательность бит записываем в массив чанков
        }
    }

    
    return encoded_data;
}

std::vector<uint8_t> HammingCodec::Decode(void* byte_sequence, uint64_t total_bits) {
    std::vector<uint8_t> result;
    uint8_t* data = static_cast<uint8_t*>(byte_sequence);

    return result;
}