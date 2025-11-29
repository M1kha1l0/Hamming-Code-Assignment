#include "codec.h"

namespace codec {
    void HammingCodec::SetBit(void* byte_sequence, uint64_t index, bool bit) {
        uint8_t* data = static_cast<uint8_t*>(byte_sequence);
        if(bit) {
            data[index / 8] |= (1 << (index % 8));
        }
        else {
            data[index / 8] &= ~(1 << (index % 8));
        }
    }
    
    bool HammingCodec::GetBit(void* byte_sequence, uint64_t index) {
        uint8_t* data = static_cast<uint8_t*>(byte_sequence);
        return (data[index / 8] >> (index % 8)) & 1;
    }
    
    void HammingCodec::InvertBit(void* byte_sequence, uint64_t index) {
        uint8_t* data = static_cast<uint8_t*>(byte_sequence);
        data[index / 8] ^= (1 << (index % 8));
    }
    
} // namespace codec