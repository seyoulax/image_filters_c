#ifndef IMAGE_PROCESSOR_BMP_H
#define IMAGE_PROCESSOR_BMP_H

#include <vector>
#include <cstdint>

namespace image_processor {

struct RGB {
    float r, g, b;
    const float& operator[](const size_t i) const {
        return i == 0 ? r : (i == 1 ? g : b);
    }
};

using BmpData = std::vector<std::vector<RGB>>;

class BmpImage {
public:
    BmpImage(){};

public:

    void SetBmpData(BmpData pixels) {
        this->height_ = pixels.size();
        this->width_ = this->height_ ? pixels[0].size() : 0;
        this->pixels_ = std::move(pixels);
    }

    const BmpData& GetImagePixels() const {
        return this->pixels_;
    }

    size_t GetImageWidth() const {
        return this->width_;
    }

    size_t GetImageHeight() const {
        return this->height_;
    }

private:
    BmpData pixels_;
    size_t width_ = 0;
    size_t height_ = 0;
};
}

#endif  // IMAGE_PROCESSOR_BMP_H
