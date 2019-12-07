#pragma once

#include <stdint.h>
#include <string>
#include <vector>

namespace incr4k
{
namespace base64
{
std::string encode(const std::vector<uint8_t> &blob);
void encode(const std::vector<uint8_t> &blob, std::string &result);

std::vector<uint8_t> decode(const std::string &str);
void decode(const std::string &str, std::vector<uint8_t> &result);

}  // namespace base64
}  // namespace incr4k
