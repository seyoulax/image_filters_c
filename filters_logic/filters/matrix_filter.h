#ifndef CPP_HSE_MATRIX_FILTER_H
#define CPP_HSE_MATRIX_FILTER_H

#include <array>

#include "base_filter.h"

const int KERNEL3X3_SIZE = 9;

namespace image_processor {

class MatrixFilter : public BaseFilter {

public:

    struct ComputeFilterColorAndCoords {
        size_t x, y, color;
    };

    using Kernel3x3 = std::array<float, KERNEL3X3_SIZE>;

protected:

    Kernel3x3 init_kernel;
    MatrixFilter(Kernel3x3 kernel)
        : init_kernel(kernel)
    {}

    float SingleApplyKernel(const ComputeFilterColorAndCoords& coords, const BmpData& pixels) const;

    void ApplyKernel(BmpImage& bmp) const;

};

}

#endif
