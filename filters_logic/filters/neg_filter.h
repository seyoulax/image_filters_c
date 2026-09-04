#ifndef IMAGE_PROCESSOR_NEG_FILTER_H
#define IMAGE_PROCESSOR_NEG_FILTER_H

#include "bmp.h"
#include "base_filter.h"
#include "parser.h"

namespace image_processor {

std::pair<BaseFilter*, FilterCreatingRes> CreateNegFilter(const FilterDescriptor& f_descriptor);

class NegFilter : public BaseFilter {

public:

    NegFilter(){}

    void Apply(BmpImage& bmp) const override;
};

}

#endif  // IMAGE_PROCESSOR_NEG_FILTER_H
