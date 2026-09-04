#include "edge_filter.h"

namespace image_processor {

std::pair<BaseFilter*, FilterCreatingRes> CreateEdgeFilter(const FilterDescriptor& f_descriptor) {
    if (f_descriptor.filter_params.size() != 1) {
        return {nullptr, FilterCreatingRes::InvalidParametersNumber};
    }
    float threshold = 0.0f;
    std::optional<float> conv_res_param = ConvertToFloatFromChars(f_descriptor.filter_params[0]);
    if (conv_res_param.has_value()) {
        threshold = conv_res_param.value();
        if ((threshold > 1) || (threshold < 0)) {
            return {nullptr, FilterCreatingRes::InvalidParametersValue};
        }
    } else {
        return {nullptr, FilterCreatingRes::InvalidParametersValue};
    }
    BaseFilter* filter = new EdgeFilter(threshold);
    return {filter, FilterCreatingRes::Ok};
};

void EdgeFilter::Apply(BmpImage& bmp) const {
    ApplyKernel(bmp);
    const BmpData& pixels = bmp.GetImagePixels();
    BmpData new_pixels = {pixels.size(), std::vector<RGB> {pixels[0].size(), {0, 0,0 }}};
    for (size_t i = 0; i < new_pixels.size(); i++) {
        for (size_t j = 0; j < new_pixels[i].size(); j++) {
            float value = (pixels[i][j].r > threshold_ ? 1.0f : 0.0f);
            new_pixels[i][j].r = value;
            new_pixels[i][j].g = value;
            new_pixels[i][j].b = value;
        }
    }
    bmp.SetBmpData(std::move(new_pixels));
}

}