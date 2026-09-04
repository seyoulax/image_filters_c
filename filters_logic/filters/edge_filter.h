#ifndef IMAGE_PROCESSOR_EDGE_FILTER_H
#define IMAGE_PROCESSOR_EDGE_FILTER_H

#include "bmp.h"
#include "base_filter.h"
#include "matrix_filter.h"
#include "parser.h"

const float EDGE_KERNEL_COEF = 4.0f;

namespace image_processor {

std::pair<BaseFilter*, FilterCreatingRes> CreateEdgeFilter(const FilterDescriptor& f_descriptor);

class EdgeFilter : public MatrixFilter {

public:

    explicit EdgeFilter(float threshold)
        : MatrixFilter(
            {
            0.0f, -1.0f, 0.0f,
           -1.0f, EDGE_KERNEL_COEF, -1.0f,
            0.0f, -1.0f, 0.0f
            }
        )
        , threshold_(threshold)
    {}

    void Apply(BmpImage& bmp) const override;

private:
    float threshold_;
};

}

#endif  // IMAGE_PROCESSOR_EDGE_FILTER_H
