#include "bmp_writer.h"

#include <fstream>
#include <cstdint>
#include <cmath>
#include <algorithm>

const int BYTE_SIZE = 8;
const int NUM_BYTES_IN_DIB_HEADER = 40;
const int NUM_BITS_PER_PIXEL = 24;
const int BIT_OFFSET = 54;
const int MASK_ONLY_SMALLEST_BYTE = 0xFF;
const int IMAGE_RESOLUTION = 2835;

void WriteU16Le(std::ostream& os, uint16_t v) {
    char b[2] = {
        static_cast<char>(v & MASK_ONLY_SMALLEST_BYTE),
        static_cast<char>((v >> BYTE_SIZE) & MASK_ONLY_SMALLEST_BYTE)
    };
    os.write(b, 2);
}

void WriteU32Le(std::ostream& os, uint32_t v) {
    char b[4] = {
        static_cast<char>(v & MASK_ONLY_SMALLEST_BYTE),
        static_cast<char>((v >> BYTE_SIZE) & MASK_ONLY_SMALLEST_BYTE),
        static_cast<char>((v >> BYTE_SIZE * 2) & MASK_ONLY_SMALLEST_BYTE),
        static_cast<char>((v >> BYTE_SIZE * 3) & MASK_ONLY_SMALLEST_BYTE)
    };
    os.write(b, 4);
}

void WriteI32Le(std::ostream& os, int32_t v) {
    WriteU32Le(os, static_cast<uint32_t>(v));
}

namespace image_processor {

BmpWriter::BmpWriteRes BmpWriter::Write(const BmpImage& target_image) const {
    const BmpData& target_image_pixels = target_image.GetImagePixels();
    if (target_image_pixels.empty() || target_image_pixels[0].empty()) {
        return BmpWriteRes::InvalidImageSize;
    }

    const uint32_t height = static_cast<uint32_t>(target_image_pixels.size());
    const uint32_t width  = static_cast<uint32_t>(target_image_pixels[0].size());

    const uint32_t bytes_per_pixel = NUM_BITS_PER_PIXEL / BYTE_SIZE;
    const uint32_t row_bytes = width * bytes_per_pixel;
    const uint32_t padding = (4 - (row_bytes % 4)) % 4;
    const uint32_t pixel_array_size = (row_bytes + padding) * height;
    const uint32_t file_size = BIT_OFFSET + pixel_array_size;

    std::ofstream file(filename_, std::ios::binary);
    if (!file.is_open()) {
        return BmpWriteRes::FailedToCreateFile;
    }

    const char signature[2] = {'B', 'M'};
    file.write(signature, 2);
    WriteU32Le(file, file_size);
    WriteU16Le(file, 0);
    WriteU16Le(file, 0);
    WriteU32Le(file, BIT_OFFSET);

    WriteU32Le(file, NUM_BYTES_IN_DIB_HEADER);
    WriteI32Le(file, static_cast<int32_t>(width));
    WriteI32Le(file, -static_cast<int32_t>(height));
    WriteU16Le(file, 1);
    WriteU16Le(file, NUM_BITS_PER_PIXEL);
    WriteU32Le(file, 0);
    WriteU32Le(file, pixel_array_size);
    WriteI32Le(file, IMAGE_RESOLUTION);
    WriteI32Le(file, IMAGE_RESOLUTION);
    WriteU32Le(file, 0);
    WriteU32Le(file, 0);

    const char pad[3] = {0, 0, 0};
    for (uint32_t y = 0; y < height; ++y) {
        const std::vector<RGB>& row = target_image_pixels[y];
        for (uint32_t x = 0; x < width; ++x) {
            const RGB& px = row[x];
            const char bgr[3] = {
                static_cast<char>(std::lround(std::clamp(px.b, 0.0f, 1.0f) * 255.0f)),
                static_cast<char>(std::lround(std::clamp(px.g, 0.0f, 1.0f) * 255.0f)),
                static_cast<char>(std::lround(std::clamp(px.r, 0.0f, 1.0f) * 255.0f))
            };
            file.write(bgr, 3);
        }
        file.write(pad, padding);
    }

    return BmpWriteRes::Ok;
}

} // namespace image_processor