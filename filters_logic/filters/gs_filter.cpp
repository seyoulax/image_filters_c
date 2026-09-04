#include "gs_filter.h"

namespace image_processor {

std::pair<BaseFilter*, FilterCreatingRes> CreateGrayscaleFilter(const FilterDescriptor& f_descriptor) {
    BaseFilter* filter = new GrayscaleFilter();
    return {filter, FilterCreatingRes::Ok};
};

void GrayscaleFilter::Apply(BmpImage& bmp) const {
    const BmpData& pixels = bmp.GetImagePixels();
    BmpData new_pixels = {pixels.size(), std::vector<RGB> {pixels[0].size(), {0, 0,0 }}};
    for (size_t i = 0; i < new_pixels.size(); i++) {
        for (size_t j = 0; j < new_pixels[i].size(); j++) {
            double value = 0.299 * pixels[i][j].r + 0.114 * pixels[i][j].b + 0.587 * pixels[i][j].g;
            new_pixels[i][j].r = value;
            new_pixels[i][j].b = value;
            new_pixels[i][j].g = value;
        }
    }
    bmp.SetBmpData(std::move(new_pixels));
}

}