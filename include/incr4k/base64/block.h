#pragma once

#include <stdint.h>
#include <string>

namespace incr4k
{
namespace base64
{
using size = std::string::size_type;

void encode_block(const uint8_t *bblk, char *cblk);
void encode_block_finalize(const uint8_t *bblk, size left, char *cblk);

void decode_block(const char *cblk, uint8_t *bblk);
void decode_block_finalize(const char *cblk, uint8_t *bblk);

}  // namespace base64
}  // namespace incr4k
