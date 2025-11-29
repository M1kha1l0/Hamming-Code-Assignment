#include <vector>
#include <string>

namespace codec {
    class HammingCodec {
        public:
            static void SetBit(void* byte_sequence, uint64_t index, bool bit);

            static bool GetBit(void* byte_sequence, uint64_t index);

            static void InvertBit(void* byte_sequence, uint64_t index);
    };

} // namespace codec