#ifndef IMAGE_PROCESSOR_BASE_FILTER_H
#define IMAGE_PROCESSOR_BASE_FILTER_H

#include <string>
#include <map>
#include <optional>

#include "bmp.h"
#include "parser.h"

namespace image_processor {

std::optional<int> ConvertToIntFromChars(const std::string& s);
std::optional<float> ConvertToFloatFromChars(const std::string& s);

enum FilterCreatingRes {
    Ok,
    InvalidParametersNumber,
    InvalidParametersValue
};

class BaseFilter{
public:
    virtual ~BaseFilter() = default;
    virtual void Apply(BmpImage& bmp) const = 0;
};

using CreateFilterPtr = std::pair<BaseFilter*, FilterCreatingRes>(*)(const FilterDescriptor&);
inline std::map<std::string, CreateFilterPtr> filter_creators;

}

#endif
