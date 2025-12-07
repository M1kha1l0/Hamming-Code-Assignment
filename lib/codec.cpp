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

    while((1 << result) < (total_bits + 1)) {
        result++;
    }

    return result;
}

uint64_t HammingCodec::CalculateTotalSize(uint64_t data_bits) {
    return CalculateControlBitsCount(data_bits) + data_bits;
}

uint64_t HammingCodec::CalculateSyndrome(uint8_t* data, uint64_t total_bits) {
    uint64_t syndrome = 0;
    uint64_t control_bit_count = HammingCodec::CalculateControlBitsCount(total_bits);
    
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
            
std::vector<uint8_t> HammingCodec::Encode(void *byte_sequence, uint64_t data_bits, uint64_t total_bits) {
    uint64_t control_bit_count = CalculateControlBitsCount(data_bits);
    std::vector<uint8_t> encoded_data((total_bits + 7) / 8, 0);
        
    uint8_t* data = static_cast<uint8_t*>(byte_sequence);

    uint64_t data_bit_index = 0;
    for(uint64_t i = 1;i <= total_bits;i++) {
        if((i & (i-1)) != 0) {
            if(data_bit_index < data_bits) {
                SetBit(encoded_data.data(), i - 1, GetBit(data, data_bit_index));
                data_bit_index++;
            }
        }
    }

    for(uint64_t control_bit_pos = 1;control_bit_pos <= total_bits;control_bit_pos <<= 1) {
        uint8_t control_bit = 0;
        for(int i = 1; i <= total_bits;i++) {
            if(control_bit_pos & i) {
                control_bit ^= GetBit(encoded_data.data(), i-1);
            }
        }

        SetBit(encoded_data.data(), control_bit_pos-1, control_bit);
    }

    return encoded_data;
}

std::vector<uint8_t> HammingCodec::Decode(void* byte_sequence, uint64_t total_bits) {
    uint64_t control_bit_count = CalculateControlBitsCount(total_bits);

    std::vector<uint8_t> decoded_data((total_bits - control_bit_count + 7) / 8, 0);
    uint8_t* data = static_cast<uint8_t*>(byte_sequence);

    uint64_t syndrome = CalculateSyndrome(data, total_bits);

    if (syndrome != 0 && syndrome <= total_bits) {
        InvertBit(data, syndrome - 1);
    }

    int result_bit_index = 0;
    for(uint64_t i = 1;i <= total_bits;i++) {
        if((i & (i - 1)) != 0) {
            SetBit(decoded_data.data(), result_bit_index, GetBit(data, i - 1));
            result_bit_index++;
        }
    }
                
    return decoded_data;
}

bool HammingCodec::Validate(void* byte_sequence, uint64_t total_bits) {
    uint8_t* data = static_cast<uint8_t*>(byte_sequence);
    if(CalculateSyndrome(data, total_bits) != 0) return false;
    return true;
}

void HammingCodec::PrintBits(void* bit_sequence, uint64_t total_bits, std::ostream& stream) {
    uint8_t* data = static_cast<uint8_t*>(bit_sequence);
    for(int i = 0;i < total_bits;i++) {
        if(GetBit(data, i)) {
            stream << '1';
        }
        else {
            stream << '0';
        }
    }
    stream << '\n';
}