#ifndef IMAGE_PROCESSOR_BMP_WRITER_H
#define IMAGE_PROCESSOR_BMP_WRITER_H

#include <string>

#include "bmp.h"

namespace image_processor {

class BmpWriter {
public:

    enum BmpWriteRes {
        Ok,
        FailedToCreateFile,
        InvalidImageSize
    };

    explicit BmpWriter(const std::string& filename)
        : filename_(filename)
    {}

    BmpWriteRes Write(const BmpImage& target_image) const;

private:
    std::string filename_;
};

}

#endif  // IMAGE_PROCESSOR_BMP_WRITER_H
