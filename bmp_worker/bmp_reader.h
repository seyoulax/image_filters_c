#ifndef IMAGE_PROCESSOR_BMP_READER_H
#define IMAGE_PROCESSOR_BMP_READER_H

#include <string>

#include "bmp.h"

namespace image_processor {

class BmpReader {
public:
    enum ReadBmpRes {
        Ok,
        FailedOpenFile,
        FailedReadSignature,
        BmpTypeError,
        FailedSkipHeader,
        FailedReadBitOffset,
        FailedReadHeaderSize,
        DibHeaderTypeNotSupported,
        FailedReadWidth,
        InvalidNotPositiveWidth,
        InvalidNotPositiveHeight,
        FailedReadHeight,
        FailedReadColorPlanes,
        PlaneNumNotSupported,
        FailedReadNumBitPerPixel,
        BitNumNoSupported,
        FailedReadCompression,
        NoCompressionSupported,
        InvalidPixelOffset,
        UnexpectedEOF
    };

    BmpReader()
        : BmpReader(nullptr)
    {}

    explicit BmpReader(const std::string& filename)
        : filename_(filename)
    {}

public:

    ReadBmpRes Read(BmpImage& target_image) const;

private:
    const std::string& filename_;
};

}

#endif  // IMAGE_PROCESSOR_BMP_READER_H
