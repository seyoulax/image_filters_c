#ifndef IMAGE_PROCESSOR_FILTER_FACTORY_H
#define IMAGE_PROCESSOR_FILTER_FACTORY_H

#include "parser.h"
#include "pipeline.h"

namespace image_processor {

using PipeFillingRes = std::pair<FilterCreatingRes, std::string>;

class FilterFactory {

public:

    FilterFactory(){};

    PipeFillingRes FillPipeline(const std::vector<FilterDescriptor>& f_ds, Pipeline& pipe) const;

};

}

#endif  // IMAGE_PROCESSOR_FILTER_FACTORY_H
