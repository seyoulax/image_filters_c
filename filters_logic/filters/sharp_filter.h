#ifndef IMAGE_PROCESSOR_SHARP_FILTER_H
#define IMAGE_PROCESSOR_SHARP_FILTER_H

#include "bmp.h"
#include "base_filter.h"
#include "matrix_filter.h"
#include "parser.h"

const float SHARP_KERNEL_COEF = 5.0f;

namespace image_processor {

std::pair<BaseFilter*, FilterCreatingRes> CreateSharpFilter(const FilterDescriptor& f_descriptor);

class SharpFilter : public MatrixFilter {

public:

    SharpFilter()
        : MatrixFilter(
            {
            0.0f, -1.0f, 0.0f,
           -1.0f,SHARP_KERNEL_COEF, -1.0f,
            0.0f, -1.0f, 0.0f
            }
        )
    {}

    void Apply(BmpImage& bmp) const override;
};

}

#endif  // IMAGE_PROCESSOR_SHARP_FILTER_H
