#ifndef IMAGE_PROCESSOR_PARSER_H
#define IMAGE_PROCESSOR_PARSER_H

#include <string>
#include <vector>

namespace image_processor {

struct FilterDescriptor {
    size_t GetFilterParamsCount() const {
        return filter_params.size();
    }
    std::string filter_name;
    std::vector<std::string> filter_params;
};


class Parser {
public:
    Parser()
        : input_filename_(std::string{})
        , output_filename_(std::string{})
        , filters_(std::vector<FilterDescriptor> {})
    {}

    enum ParseRes {
        Ok,
        InputFilenameNotPasses,
        OutputFilenameNotPasses,
        EmptyArgs,
    };

public:
    ParseRes Parse(int argc, char** argv);

    const std::string& GetInputFilename() const {
        return this->input_filename_;
    }
    const std::string& GetOutputFilename() const {
        return this->output_filename_;
    }
    const std::vector<FilterDescriptor>& GetFilters() const {
        return this->filters_;
    }

private:

    ParseRes ParseInternal(int argc, char** argv);

private:
    std::string input_filename_;
    std::string output_filename_;
    std::vector<FilterDescriptor> filters_;

};
}

#endif  // IMAGE_PROCESSOR_PARSER_H
