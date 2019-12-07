#include "incr4k/base64/block.h"

namespace incr4k
{
namespace base64
{
namespace
{
const char B64_CE[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

char B64_CD_impl[] = {62, 0,  0,  0,  63, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 0,
                      0,  0,  0,  0,  0,  0,  0,  1,  2,  3,  4,  5,  6,  7,  8,  9,
                      10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25,
                      0,  0,  0,  0,  0,  0,  26, 27, 28, 29, 30, 31, 32, 33, 34, 35,
                      36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51};
}  // namespace

#define B64_ET_1(ptr) B64_CE[ptr[0U] >> 2U]
#define B64_ET_2s(ptr) B64_CE[((ptr[0U] & 0x03) << 4U)]
#define B64_ET_2(ptr) B64_CE[((ptr[0U] & 0x03) << 4U) | ((ptr[1U] & 0xf0) >> 4U)]
#define B64_ET_3(ptr) B64_CE[((ptr[1U] & 0x0f) << 2) | ((ptr[2U] & 0xc0) >> 6U)]
#define B64_ET_3s(ptr) B64_CE[((ptr[1U] & 0x0f) << 2)]
#define B64_ET_4(ptr) B64_CE[ptr[2U] & 0x3f]

#define B64_CD(c) B64_CD_impl[c - 43u]

#define B64_DT_1(ptr) (B64_CD(cblk[0]) << 2) | ((B64_CD(cblk[1]) & 0x30) >> 4)
#define B64_DT_2r(ptr) ((B64_CD(cblk[1]) & 0xf) << 4)
#define B64_DT_2l(ptr) ((B64_CD(cblk[2]) & 0x3c) >> 2)
#define B64_DT_2(ptr) (B64_DT_2l(ptr) | B64_DT_2r(ptr))
#define B64_DT_3(ptr) ((B64_CD(cblk[2]) & 0x3) << 6) | B64_CD(cblk[3])

void
encode_block(const uint8_t *bblk, char *cblk)
{
    cblk[0U] = B64_ET_1(bblk);
    cblk[1U] = B64_ET_2(bblk);
    cblk[2U] = B64_ET_3(bblk);
    cblk[3U] = B64_ET_4(bblk);
}

void
encode_block_finalize(const uint8_t *bblk, size left, char *cblk)
{
    cblk[0U] = B64_ET_1(bblk);
    cblk[1U] = (left > 1) ? B64_ET_2(bblk) : B64_ET_2s(bblk);
    cblk[2U] = (left > 2) ? B64_ET_3(bblk) : (left > 1) ? B64_ET_3s(bblk) : '=';
    cblk[3U] = (left > 2) ? B64_ET_4(bblk) : '=';
}

void
decode_block(const char *cblk, uint8_t *bblk)
{
    bblk[0] = B64_DT_1(cblk);
    bblk[1] = B64_DT_2(cblk);
    bblk[2] = B64_DT_3(cblk);
}

void
decode_block_finalize(const char *cblk, uint8_t *bblk)
{
    auto c0 = cblk[1] != '=';

    bblk[0] = B64_DT_1(cblk);
    auto c1 = cblk[2] != '=';
    if (c1)
    {
        auto c2 = cblk[3] != '=';
        bblk[1] = B64_DT_2l(cblk) + (c1 ? B64_DT_2r(cblk) : 0);
        if (c2)
        {
            bblk[2] = B64_DT_3(cblk);
        }
    }
}

}  // namespace base64
}  // namespace incr4k
