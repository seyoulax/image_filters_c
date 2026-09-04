#include "filter_factory.h"

#include "base_filter.h"
#include "crop_filter.h"
#include "gs_filter.h"

namespace image_processor {

PipeFillingRes FilterFactory::FillPipeline(const std::vector<FilterDescriptor>& f_ds, Pipeline& pipe) const {
    for (const FilterDescriptor& filter_d : f_ds) {
        CreateFilterPtr cur_filter_creator = filter_creators[filter_d.filter_name];
        std::pair<BaseFilter*, FilterCreatingRes> cur_filter = cur_filter_creator(filter_d);
        if (cur_filter.second != FilterCreatingRes::Ok) {
            return {cur_filter.second, filter_d.filter_name};
        }
        if (filter_d.filter_name == "edge") {
            FilterDescriptor gs_d = FilterDescriptor{.filter_name="gs", .filter_params = std::vector<std::string>()};
            std::pair<BaseFilter*, FilterCreatingRes> gs_filter = CreateGrayscaleFilter(gs_d);
            pipe.Add(gs_filter.first);
        }
        pipe.Add(cur_filter.first);
    }
    return {FilterCreatingRes::Ok, ""};
}

}