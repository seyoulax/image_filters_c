#include "crop_filter.h"

namespace image_processor {

std::pair<BaseFilter*, FilterCreatingRes> CreateCropFilter(const FilterDescriptor& f_descriptor) {
    if (f_descriptor.filter_params.size() != 2) {
        return {nullptr, FilterCreatingRes::InvalidParametersNumber};
    }
    int param1 = 0, param2 = 0;
    std::optional<int> conv_res_param_1 = ConvertToIntFromChars(f_descriptor.filter_params[0]);
    std::optional<int> conv_res_param_2 = ConvertToIntFromChars(f_descriptor.filter_params[1]);
    if (conv_res_param_1.has_value() && conv_res_param_2.has_value()) {
        param1 = conv_res_param_1.value();
        param2 = conv_res_param_2.value();
        if ((param1 <= 0) || (param2 <= 0)) {
            return {nullptr, FilterCreatingRes::InvalidParametersValue};
        }
    } else {
        return {nullptr, FilterCreatingRes::InvalidParametersValue};
    }
    BaseFilter* filter = new CropFilter(static_cast<size_t>(param1),static_cast<size_t>(param2));
    return {filter, FilterCreatingRes::Ok};
};

void CropFilter::Apply(BmpImage& bmp) const {
    const BmpData& pixel_data = bmp.GetImagePixels();
    size_t truly_desired_height = std::min(this->desired_height_, bmp.GetImageHeight());
    size_t truly_desired_width = std::min(this->desired_width_, bmp.GetImageWidth());
    BmpData new_pixel_data = {truly_desired_height, std::vector<RGB> {truly_desired_width, {0,0,0}}};
    for (size_t i = 0; i < truly_desired_height; i++) {
        for (size_t j = 0; j < truly_desired_width; j++) {
            new_pixel_data[i][j] = pixel_data[i][j];
        }
    }
    bmp.SetBmpData(std::move(new_pixel_data));
}


}