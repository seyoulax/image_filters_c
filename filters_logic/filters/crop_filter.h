#ifndef IMAGE_PROCESSOR_CROP_FILTER_H
#define IMAGE_PROCESSOR_CROP_FILTER_H

#include "bmp.h"
#include "base_filter.h"
#include "parser.h"

namespace image_processor {

std::pair<BaseFilter*, FilterCreatingRes>  CreateCropFilter(const FilterDescriptor& f_descriptor);

class CropFilter : public BaseFilter {

public:

    CropFilter()
        : CropFilter(0, 0)
    {}

    CropFilter(size_t desired_width, size_t desired_height)
        : desired_width_(desired_width)
        , desired_height_(desired_height)
    {}

    void Apply(BmpImage& bmp) const override;

private:
    size_t desired_width_;
    size_t desired_height_;
};

}

#endif  // IMAGE_PROCESSOR_CROP_FILTER_H
