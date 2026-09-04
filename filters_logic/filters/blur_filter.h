#ifndef IMAGE_PROCESSOR_BLUR_FILTER_H
#define IMAGE_PROCESSOR_BLUR_FILTER_H

#include "base_filter.h"

namespace image_processor {

std::pair<BaseFilter*, FilterCreatingRes> CreateBlurFilter(const FilterDescriptor& f_descriptor);

class BlurFilter : public BaseFilter {

public:

    explicit BlurFilter(float sigma)
        : sigma_(sigma)
    {}

    void Apply(BmpImage& bmp) const override;

    void PrecomputeKernelWeights(std::vector<float>& weights, float sigma) const;

private:
    float sigma_;

};

}

#endif  // IMAGE_PROCESSOR_BLUR_FILTER_H
