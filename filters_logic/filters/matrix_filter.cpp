#include "matrix_filter.h"

namespace image_processor {

float MatrixFilter::SingleApplyKernel(const MatrixFilter::ComputeFilterColorAndCoords& coords, const BmpData& pixels) const {
    const int& x = static_cast<int>(coords.x);
    const int& y = static_cast<int>(coords.y);
    const size_t& c = coords.color;
    const int x_left = std::max(x - 1, 0);
    const int x_right = std::min(x + 1, static_cast<int>(pixels[0].size() - 1));
    const int y_top = std::max(y - 1, 0);
    const int y_bottom = std::min(y + 1, static_cast<int>(pixels.size() - 1));
    float sum = 0.0f;
    for (int i = 0; i < KERNEL3X3_SIZE; i++) {
        int cur_x = x;
        int cur_y = y;
        if (i / 3 == 0) {
            cur_y = y_top;
        } else if (i / 3 == 2) {
            cur_y = y_bottom;
        }
        if (i % 3 == 0) {
            cur_x = x_left;
        } else if (i % 3 == 2) {
            cur_x = x_right;
        }
        sum += init_kernel[i] * pixels[cur_y][cur_x][c];
    }
    return std::min(1.0f, std::max(0.0f, sum));
}

void MatrixFilter::ApplyKernel(BmpImage& bmp) const {
    const BmpData& pixels = bmp.GetImagePixels();
    BmpData new_pixels = {pixels.size(), std::vector<RGB> {pixels[0].size(), {0, 0,0 }}};
    for (size_t i = 0; i < new_pixels.size(); i++) {
        for (size_t j = 0; j < new_pixels[i].size(); j++) {
            new_pixels[i][j].r = SingleApplyKernel({.x = j, .y = i, .color = 0}, pixels);
            new_pixels[i][j].g = SingleApplyKernel({.x = j, .y = i, .color = 1}, pixels);
            new_pixels[i][j].b = SingleApplyKernel({.x = j, .y = i, .color = 2}, pixels);
        }
    }
    bmp.SetBmpData(std::move(new_pixels));
}

}