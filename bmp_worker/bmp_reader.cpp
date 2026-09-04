#include "bmp_reader.h"

#include <cstdint>
#include <fstream>
#include <stdexcept>
#include <vector>
#include <iostream>

const int BYTE_SIZE = 8;
const int NUM_UNUSED_BYTES_IN_FILE_HEADER = 8;
const int NUM_BYTES_IN_DIB_HEADER = 40;
const int NUM_BITS_PER_PIXEL = 24;
const float MAX_COLOR_VALUE = 255.0f;

std::uint32_t ConvertLEtoUint32(const unsigned char* b4) {
    std::uint32_t result = static_cast<std::uint32_t>(b4[0]) |
                            (static_cast<std::uint32_t>(b4[1]) << BYTE_SIZE) |
                            (static_cast<std::uint32_t>(b4[2]) << BYTE_SIZE*2) |
                            (static_cast<std::uint32_t>(b4[3]) << BYTE_SIZE*3);
    return result;
}

std::uint16_t ConvertLEtoUint16(const unsigned char* b2) {
    std::uint16_t result = static_cast<std::uint16_t>(b2[0]) |
                            (static_cast<std::uint16_t>(b2[1]) << BYTE_SIZE);
    return result;
}

namespace image_processor {

BmpReader::ReadBmpRes BmpReader::Read(BmpImage& target_image) const {

    // reading file
    std::ifstream f(filename_, std::ios::binary);
    if (!f) {
        return BmpReader::ReadBmpRes::FailedOpenFile;
    }

    // check for the file correctness
    unsigned char sig[2];

    //signature
    if (!f.read(reinterpret_cast<char*>(sig), 2)) {
        return BmpReader::ReadBmpRes::FailedReadSignature;
    }
    if (sig[0] != 'B' || sig[1] != 'M') {
        return BmpReader::ReadBmpRes::BmpTypeError;
    }

    //fileheader
    f.seekg(NUM_UNUSED_BYTES_IN_FILE_HEADER, std::ios::cur);
    if (!f) {
        return BmpReader::ReadBmpRes::FailedSkipHeader;
    }

    //a bit offset
    unsigned char b4[4];
    if (!f.read(reinterpret_cast<char*>(b4), 4)) {
        return BmpReader::ReadBmpRes::FailedReadBitOffset;
    }
    std::uint32_t off_bits = ConvertLEtoUint32(b4);

    //header size
    if (!f.read(reinterpret_cast<char*>(b4), 4)) {
        return BmpReader::ReadBmpRes::FailedReadHeaderSize;
    }
    std::uint32_t bi_size = ConvertLEtoUint32(b4);

    if (bi_size != NUM_BYTES_IN_DIB_HEADER) {
        return BmpReader::ReadBmpRes::DibHeaderTypeNotSupported;
    }

    //width
    if (!f.read(reinterpret_cast<char*>(b4), 4)) {
        return BmpReader::ReadBmpRes::FailedReadWidth;
    }
    std::int32_t width = static_cast<int32_t>(ConvertLEtoUint32(b4));

    if (width <= 0) {
        return BmpReader::ReadBmpRes::InvalidNotPositiveWidth;
    }

    //height
    if (!f.read(reinterpret_cast<char*>(b4), 4)) {
        return BmpReader::ReadBmpRes::FailedReadHeight;
    }
    std::int32_t height_val = static_cast<int32_t>(ConvertLEtoUint32(b4));

    int height_abs = (height_val < 0) ? -height_val : height_val;

    if (height_abs <= 0) {
        return BmpReader::ReadBmpRes::InvalidNotPositiveHeight;
    }

    bool bottom_up = (height_val > 0);

    //color planes
    unsigned char b2[2];
    if (!f.read(reinterpret_cast<char*>(b2), 2)) {
        return BmpReader::ReadBmpRes::FailedReadColorPlanes;
    }
    std::uint16_t planes = ConvertLEtoUint16(b2);

    if (planes != 1) {
        return BmpReader::ReadBmpRes::PlaneNumNotSupported;
    }

    // num bit per image pixel
    if (!f.read(reinterpret_cast<char*>(b2), 2)) {
        return BmpReader::ReadBmpRes::FailedReadNumBitPerPixel;
    }

    std::uint16_t bit_count = ConvertLEtoUint16(b2);

    if (bit_count != NUM_BITS_PER_PIXEL) {
        return BmpReader::ReadBmpRes::BitNumNoSupported;
    }

    // compression
    if (!f.read(reinterpret_cast<char*>(b4), 4)) {
        return BmpReader::ReadBmpRes::FailedReadCompression;
    }
    std::uint32_t compression = ConvertLEtoUint32(b4);

    if (compression != 0) {
        return BmpReader::ReadBmpRes::NoCompressionSupported;
    }

    f.seekg(off_bits, std::ios::beg);

    // pixel offset
    if (!f) {
        return BmpReader::ReadBmpRes::InvalidPixelOffset;
    }

    // num bit in row
    const std::uint32_t row_bytes = static_cast<std::uint32_t>(width) * 3;
    const std::uint32_t padding   = (4 - (row_bytes % 4)) % 4;
    const std::uint32_t row_stride_file = row_bytes + padding;

    // pixel data
    BmpData data(static_cast<std::size_t>(height_abs),
                 std::vector<RGB>(static_cast<std::size_t>(width)));

    // row temp
    std::vector<unsigned char> row (row_stride_file);

    // reading rows
    for (int r = 0; r < height_abs; ++r) {
        if (!f.read(reinterpret_cast<char*>(row.data()), row_stride_file)) {
            return BmpReader::ReadBmpRes::UnexpectedEOF;
        }

        // row vector
        int dst_row = bottom_up ? (height_abs - 1 - r) : r;
        std::vector<RGB>& out_row = data[static_cast<std::size_t>(dst_row)];

        for (int x = 0; x < width; ++x) {
            std::size_t i = static_cast<std::size_t>(3 * x);
            RGB pixel;
            pixel.r = static_cast<float>(row[i + 2]) / MAX_COLOR_VALUE;
            pixel.g = static_cast<float>(row[i + 1]) / MAX_COLOR_VALUE;
            pixel.b = static_cast<float>(row[i + 0]) / MAX_COLOR_VALUE;
            out_row[static_cast<std::size_t>(x)] = pixel;
        }
    }

    // moving data vector to param
    target_image.SetBmpData(std::move(data));

    return BmpReader::ReadBmpRes::Ok;
}

}