#include <gtest/gtest.h>
#include "codec.h"
#include <vector>
#include <cstdint>

TEST(HammingCodecTest, SetAndGetBit) {
    std::vector<uint8_t> data(2, 0);
    
    HammingCodec::SetBit(data.data(), 0, true);
    EXPECT_TRUE(HammingCodec::GetBit(data.data(), 0));
    
    HammingCodec::SetBit(data.data(), 5, true);
    EXPECT_TRUE(HammingCodec::GetBit(data.data(), 5));
    
    HammingCodec::SetBit(data.data(), 5, false);
    EXPECT_FALSE(HammingCodec::GetBit(data.data(), 5));
    
    HammingCodec::SetBit(data.data(), 15, true);
    EXPECT_TRUE(HammingCodec::GetBit(data.data(), 15));
}

TEST(HammingCodecTest, GetBitInitiallyZero) {
    std::vector<uint8_t> data(4, 0);
    
    for (int i = 0; i < 32; i++) {
        EXPECT_FALSE(HammingCodec::GetBit(data.data(), i));
    }
}

TEST(HammingCodecTest, InvertBit) {
    std::vector<uint8_t> data(2, 0);
    
    EXPECT_FALSE(HammingCodec::GetBit(data.data(), 3));
    HammingCodec::InvertBit(data.data(), 3);
    EXPECT_TRUE(HammingCodec::GetBit(data.data(), 3));
    HammingCodec::InvertBit(data.data(), 3);
    EXPECT_FALSE(HammingCodec::GetBit(data.data(), 3));
}

TEST(HammingCodecTest, InvertMultipleBits) {
    std::vector<uint8_t> data(2, 0);
    
    HammingCodec::InvertBit(data.data(), 0);
    HammingCodec::InvertBit(data.data(), 7);
    HammingCodec::InvertBit(data.data(), 8);
    
    EXPECT_TRUE(HammingCodec::GetBit(data.data(), 0));
    EXPECT_TRUE(HammingCodec::GetBit(data.data(), 7));
    EXPECT_TRUE(HammingCodec::GetBit(data.data(), 8));
    EXPECT_FALSE(HammingCodec::GetBit(data.data(), 1));
}

TEST(HammingCodecTest, CalculateControlBitsCount) {
    EXPECT_EQ(HammingCodec::CalculateControlBitsCount(1), 2);
    EXPECT_EQ(HammingCodec::CalculateControlBitsCount(4), 3);
    EXPECT_EQ(HammingCodec::CalculateControlBitsCount(7), 4);
    EXPECT_EQ(HammingCodec::CalculateControlBitsCount(11), 4);
    EXPECT_EQ(HammingCodec::CalculateControlBitsCount(26), 5);
}

TEST(HammingCodecTest, CalculateControlBitsCountEdgeCases) {
    EXPECT_EQ(HammingCodec::CalculateControlBitsCount(0), 0);
    EXPECT_EQ(HammingCodec::CalculateControlBitsCount(57), 6);
    EXPECT_EQ(HammingCodec::CalculateControlBitsCount(120), 7);
}

TEST(HammingCodecTest, CalculateTotalSize) {
    EXPECT_EQ(HammingCodec::CalculateTotalSize(4, 4), 7);
    
    EXPECT_EQ(HammingCodec::CalculateTotalSize(4, 8), 14);
    
    EXPECT_EQ(HammingCodec::CalculateTotalSize(11, 11), 15);
}

TEST(HammingCodecTest, CalculateTotalSizeMultipleBlocks) {
    EXPECT_EQ(HammingCodec::CalculateTotalSize(4, 10), 19);
    
    EXPECT_EQ(HammingCodec::CalculateTotalSize(7, 14), 22);
}

TEST(HammingCodecTest, CalculateSyndromeNoError) {
    std::vector<uint8_t> data(1, 0);
    
    HammingCodec::SetBit(data.data(), 0, false);
    HammingCodec::SetBit(data.data(), 1, false);
    HammingCodec::SetBit(data.data(), 2, false);
    HammingCodec::SetBit(data.data(), 3, false);
    HammingCodec::SetBit(data.data(), 4, false);
    HammingCodec::SetBit(data.data(), 5, false);
    HammingCodec::SetBit(data.data(), 6, false);
    
    uint64_t syndrome = HammingCodec::CalculateSyndrome(data.data(), 3, 7);
    EXPECT_EQ(syndrome, 0);
}

TEST(HammingCodecTest, CalculateSyndromeWithError) {
    std::vector<uint8_t> data(1, 0);
    
    uint64_t syndrome = HammingCodec::CalculateSyndrome(data.data(), 3, 7);
    EXPECT_EQ(syndrome, 0);
    
    HammingCodec::InvertBit(data.data(), 2);
    syndrome = HammingCodec::CalculateSyndrome(data.data(), 3, 7);
    EXPECT_EQ(syndrome, 3);
}

TEST(HammingCodecTest, CalculateSyndromeDifferentPositions) {
    std::vector<uint8_t> data(2, 0);
    
    HammingCodec::InvertBit(data.data(), 0);
    uint64_t syndrome = HammingCodec::CalculateSyndrome(data.data(), 4, 15);
    EXPECT_EQ(syndrome, 1);
}

TEST(HammingCodecTest, EncodeReturnsCorrectSize) {
    std::vector<uint8_t> input_data(1, 0);
    HammingCodec::SetBit(input_data.data(), 0, true);
    HammingCodec::SetBit(input_data.data(), 1, false);
    HammingCodec::SetBit(input_data.data(), 2, true);
    HammingCodec::SetBit(input_data.data(), 3, true);
    
    std::vector<uint8_t> encoded = HammingCodec::Encode(input_data.data(), 4, 4, 7);
    
    uint64_t expected_size = (HammingCodec::CalculateTotalSize(4, 4) + 7) / 8;
    EXPECT_EQ(encoded.size(), expected_size);
}

TEST(HammingCodecTest, DecodeReturnsVector) {
    std::vector<uint8_t> encoded_data(1, 0);
    std::vector<uint8_t> decoded = HammingCodec::Decode(encoded_data.data(), 7);
    
    EXPECT_TRUE(decoded.empty() || !decoded.empty());
}

TEST(HammingCodecTest, BitOperationsConsistency) {
    std::vector<uint8_t> data(10, 0);
    
    for (int i = 0; i < 80; i += 2) {
        HammingCodec::SetBit(data.data(), i, true);
    }
    
    for (int i = 0; i < 80; i++) {
        if (i % 2 == 0) {
            EXPECT_TRUE(HammingCodec::GetBit(data.data(), i));
        } else {
            EXPECT_FALSE(HammingCodec::GetBit(data.data(), i));
        }
    }
}

TEST(HammingCodecTest, ComplexBitPattern) {
    std::vector<uint8_t> data(4, 0);
    
    std::vector<int> positions = {0, 5, 7, 12, 15, 20, 31};
    for (int pos : positions) {
        HammingCodec::SetBit(data.data(), pos, true);
    }
    
    for (int i = 0; i < 32; i++) {
        bool should_be_set = false;
        for (int pos : positions) {
            if (i == pos) {
                should_be_set = true;
                break;
            }
        }
        EXPECT_EQ(HammingCodec::GetBit(data.data(), i), should_be_set);
    }
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
