#include "pipeline.h"

namespace image_processor {

void Pipeline::Add(BaseFilter* filter) {
    filters_.push_back(filter);
}

void Pipeline::Apply(BmpImage& bmp) const {
    for (const BaseFilter* filter : filters_) {
        filter->Apply(bmp);
    }
}

}