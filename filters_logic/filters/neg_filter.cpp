#include "neg_filter.h"

namespace image_processor {

std::pair<BaseFilter*, FilterCreatingRes>  CreateNegFilter(const FilterDescriptor& f_descriptor) {
    BaseFilter* filter = new NegFilter();
    return {filter, FilterCreatingRes::Ok};
}

void NegFilter::Apply(BmpImage& bmp) const {
    const BmpData& pixels = bmp.GetImagePixels();
    BmpData new_pixels = {pixels.size(), std::vector<RGB> {pixels[0].size(), {0, 0,0 }}};
    for (size_t i = 0; i < new_pixels.size(); i++) {
        for (size_t j = 0; j < new_pixels[i].size(); j++) {
            new_pixels[i][j].r = 1 - pixels[i][j].r;
            new_pixels[i][j].b = 1 - pixels[i][j].b;
            new_pixels[i][j].g = 1 - pixels[i][j].g;
        }
    }
    bmp.SetBmpData(std::move(new_pixels));
}

}