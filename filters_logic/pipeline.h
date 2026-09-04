#ifndef IMAGE_PROCESSOR_PIPELINE_H
#define IMAGE_PROCESSOR_PIPELINE_H

#include "base_filter.h"
#include "bmp.h"

namespace image_processor {

class Pipeline {
public:
    Pipeline(){};
    Pipeline(const Pipeline&) = delete;

    void Add(BaseFilter* filter);

    void Apply(BmpImage& bmp) const;

private:
    std::vector<BaseFilter*> filters_;

};

}

#endif  // IMAGE_PROCESSOR_PIPELINE_H
