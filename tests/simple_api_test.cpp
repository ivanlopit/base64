#include <gtest/gtest.h>
#include <incr4k/base64/simple.h>

#include <vector>

using namespace incr4k;

TEST(simple_api, full_test)
{
    auto str = base64::encode({});
    ASSERT_TRUE(str.empty());

    auto blob = base64::decode(str);
    ASSERT_TRUE(blob.empty());

    std::vector<std::pair<std::vector<uint8_t>, std::string>> test_vectors{

        {{}, ""},
        {{'f'}, "Zg=="},
        {{'f', 'o'}, "Zm8="},
        {{'f', 'o', 'o'}, "Zm9v"},
        {{'f', 'o', 'o', 'b'}, "Zm9vYg=="},
        {{'f', 'o', 'o', 'b', 'a'}, "Zm9vYmE="},
        {{'f', 'o', 'o', 'b', 'a', 'r'}, "Zm9vYmFy"},

    };

    for (auto& rv : test_vectors)
    {
        auto str = base64::encode(rv.first);
        ASSERT_EQ(rv.second, str);

        auto blob = base64::decode(rv.second);
        ASSERT_EQ(rv.first, blob);
    }
}
