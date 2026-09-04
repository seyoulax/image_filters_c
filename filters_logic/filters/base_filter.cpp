#include "base_filter.h"

#include <charconv>
#include <optional>

namespace image_processor {
std::optional<int> ConvertToIntFromChars(const std::string& s) {
    int value = 0;
    const char* last = s.data() + s.size();
    auto [ptr, ec] = std::from_chars(s.data(), last, value);
    if (ec == std::errc() && ptr == last) {
        return value;
    }
    return std::nullopt;
}

std::optional<float> ConvertToFloatFromChars(const std::string& s) {
    float value = 0.0f;
    const char* last  = s.data() + s.size();
    auto [ptr, ec] = std::from_chars(s.data(), last, value);
    if (ec == std::errc() && ptr == last) {
        return value;
    }
    return std::nullopt;
}

}