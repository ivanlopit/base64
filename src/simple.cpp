#include "incr4k/base64/simple.h"

#include <algorithm>
#include <cctype>
#include <cstdint>

#include "incr4k/base64/block.h"

namespace incr4k
{
namespace base64
{
std::string
encode(const std::vector<uint8_t> &blob)
{
    std::string result;

    base64::encode(blob, result);

    return result;
}

void
encode(const std::vector<uint8_t> &blob, std::string &result)
{
    auto in_size = blob.size();
    if (in_size == 0U)
    {
        return;
    }
    auto steps = (in_size - 1U) / 3U;
    auto out_size = (steps + 1U) * 4U;

    if (result.size() < out_size)
    {
        result.resize(out_size, '\0');
    }

    auto bblk_ptr = blob.data();
    auto cblk_ptr = &result[0];

    for (auto s = 0U; s < steps; bblk_ptr += 3U, cblk_ptr += 4U, ++s)
    {
        encode_block(bblk_ptr, cblk_ptr);
    }

    const auto left = in_size - steps * 3;

    if (left)
    {
        encode_block_finalize(bblk_ptr, left, cblk_ptr);
    }
}

std::vector<uint8_t>
decode(const std::string &str)
{
    std::vector<uint8_t> result;

    base64::decode(str, result);

    return result;
}

void
decode(const std::string &str, std::vector<uint8_t> &result)
{
    auto in_size = str.size();
    if (in_size == 0)
    {
        return;
    }
    int steps = --in_size / 4U;
    auto out_size = (steps + 1) * 3U;

    while (str[in_size--] == '=')
    {
        --out_size;
    }

    if (result.size() < out_size)
    {
        result.resize(out_size, '\0');
    }

    auto cblk_ptr = str.data();
    auto bblk_ptr = &result[0];

    for (int s = 0; s < steps; cblk_ptr += 4U, bblk_ptr += 3U, ++s)
    {
        decode_block(cblk_ptr, bblk_ptr);
    }
    decode_block_finalize(cblk_ptr, bblk_ptr);
}

}  // namespace base64
}  // namespace incr4k
