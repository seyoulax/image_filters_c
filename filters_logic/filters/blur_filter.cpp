#include "blur_filter.h"

#include <algorithm>
#include <cmath>

namespace image_processor {

std::pair<BaseFilter*, FilterCreatingRes> CreateBlurFilter(const FilterDescriptor& f_descriptor) {

    if (f_descriptor.filter_params.size() != 1) {
        return {nullptr, FilterCreatingRes::InvalidParametersNumber};
    }
    float sigma = 0.0f;
    std::optional<float> conv_res_param = ConvertToFloatFromChars(f_descriptor.filter_params[0]);
    if (conv_res_param.has_value()) {
        sigma = conv_res_param.value();
        // if ((sigma > 1) || (sigma < 0)) {
        //     return {nullptr, FilterCreatingRes::InvalidParametersValue};
        // }
    } else {
        return {nullptr, FilterCreatingRes::InvalidParametersValue};
    }
    BaseFilter* filter = new BlurFilter(sigma);
    return {filter, FilterCreatingRes::Ok};
}

void BlurFilter::PrecomputeKernelWeights(std::vector<float>& weights, const float sigma) const{
    if (sigma <= 0.0f) {               // защита от деления на ноль
        weights.assign(1, 1.0f);
        return;
    }
    int r = std::max(1, static_cast<int>(std::ceil(sigma * 3.0f)));
    weights.resize(2 * r + 1);
    float sigma_square = 2.0f * sigma * sigma;
    float weights_sum = 0.0f;
    for (int i = -r; i <= r; i++) {
        float cur_weight = std::exp(-(i * i) / sigma_square);
        weights[i + r] = cur_weight;
        weights_sum += cur_weight;
    }
    for (float& weight : weights) {
        weight /= weights_sum;
    }
}

void BlurFilter::Apply(BmpImage& bmp) const {
    const BmpData& pixels = bmp.GetImagePixels();
    size_t H = pixels.size();
    size_t W = pixels[0].size();
    BmpData new_pixels = {H, std::vector<RGB> {W, {0.0f,0.0f,0.0f}}};
    BmpData temp_pixels = {H, std::vector<RGB> {W, {0.0f,0.0f,0.0f}}};
    int H_ = static_cast<int>(H);
    int W_ = static_cast<int>(W);
    std::vector<float> weights;
    PrecomputeKernelWeights(weights, sigma_);
    int r = static_cast<int>(weights.size() / 2);

    for (int y = 0; y < H_; ++y) {
        for (int x = 0; x < W_; ++x) {
            float r_wei_sum = 0.0f;
            float g_wei_sum = 0.0f;
            float b_wei_sum = 0.0f;
            for (int k = -r; k <= r; ++k) {
                size_t y_index = std::clamp(y + k, 0, H_ - 1);
                r_wei_sum += pixels[y_index][x].r * weights[k + r];
                g_wei_sum += pixels[y_index][x].g * weights[k + r];
                b_wei_sum += pixels[y_index][x].b * weights[k + r];
            }
            temp_pixels[y][x] = {r_wei_sum, g_wei_sum, b_wei_sum};
        }
    }

    for (int y = 0; y < H_; ++y) {
        for (int x = 0; x < W_; ++x) {
            float r_wei_sum = 0.0f;
            float g_wei_sum = 0.0f;
            float b_wei_sum = 0.0f;
            for (int k = -r; k <= r; ++k) {
                size_t x_index = std::clamp(x + k, 0, W_ - 1);
                r_wei_sum += temp_pixels[y][x_index].r * weights[k + r];
                g_wei_sum += temp_pixels[y][x_index].g * weights[k + r];
                b_wei_sum += temp_pixels[y][x_index].b * weights[k + r];
            }
            new_pixels[y][x] = {r_wei_sum, g_wei_sum, b_wei_sum};
        }
    }

    bmp.SetBmpData(std::move(new_pixels));
}


}