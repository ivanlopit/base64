
#include <gtest/gtest.h>
#include <incr4k/base64/block.h>

#include <array>

using namespace incr4k;

TEST(block_api, test_full_block)
{
    std::array<uint8_t, 3> blob{};
    std::array<char, 4> chars{};
    std::array<uint8_t, 3> result{};

    for (int i1 = 0; i1 < 256; ++i1)
    {
        for (int i2 = 0; i2 < 256; ++i2)
        {
            for (int i3 = 0; i3 < 256; ++i3)
            {
                blob[0] = i1;
                blob[1] = i2;
                blob[2] = i3;

                base64::encode_block(blob.data(), chars.data());
                base64::decode_block(chars.data(), result.data());
                EXPECT_EQ(blob, result);
            }
        }
    }
}

TEST(block_api, test_1_3_part_block)
{
    std::array<uint8_t, 1> blob{};
    std::array<char, 4> chars{};
    std::array<uint8_t, 1> result{};

    for (int i1 = 0; i1 < 256; ++i1)
    {
        blob[0] = i1;

        base64::encode_block_finalize(blob.data(), 1, chars.data());
        base64::decode_block_finalize(chars.data(), result.data());
        EXPECT_EQ(blob, result);
    }
}

TEST(block_api, test_2_3_part_block)
{
    std::array<uint8_t, 2> blob{};
    std::array<char, 4> chars{};
    std::array<uint8_t, 2> result{};

    for (int i1 = 0; i1 < 256; ++i1)
    {
        for (int i2 = 0; i2 < 256; ++i2)
        {
            blob[0] = i1;
            blob[1] = i2;

            base64::encode_block_finalize(blob.data(), 2, chars.data());
            base64::decode_block_finalize(chars.data(), result.data());
            EXPECT_EQ(blob, result);
        }
    }
}
