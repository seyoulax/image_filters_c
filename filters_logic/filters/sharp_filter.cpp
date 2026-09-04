#include "sharp_filter.h"

namespace image_processor {

std::pair<BaseFilter*, FilterCreatingRes> CreateSharpFilter(const FilterDescriptor& f_descriptor) {
    BaseFilter* filter = new SharpFilter();
    return {filter, FilterCreatingRes::Ok};
}

void SharpFilter::Apply(BmpImage& bmp) const {
    ApplyKernel(bmp);
}

}