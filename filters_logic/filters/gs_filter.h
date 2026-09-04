#ifndef IMAGE_PROCESSOR_GS_FILTER_H
#define IMAGE_PROCESSOR_GS_FILTER_H

#include "bmp.h"
#include "base_filter.h"
#include "parser.h"

namespace image_processor {

std::pair<BaseFilter*, FilterCreatingRes> CreateGrayscaleFilter(const FilterDescriptor& f_descriptor);

class GrayscaleFilter : public BaseFilter {

public:

    GrayscaleFilter(){}

    void Apply(BmpImage& bmp) const override;
};

}

#endif
