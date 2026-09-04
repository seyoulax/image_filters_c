#include "parser.h"

#include <iostream>

namespace image_processor {
Parser::ParseRes Parser::Parse(int argc, char** argv) {
    if (argc == 0) {
        return ParseRes::EmptyArgs;
    }
    if (argc == 1) {
        return ParseRes::InputFilenameNotPasses;
    }
    if (argc == 2) {
        return ParseRes::OutputFilenameNotPasses;
    }
    return ParseInternal(argc, argv);
}

Parser::ParseRes Parser::ParseInternal(int argc, char** argv) {
    this->input_filename_ = argv[1];
    this->output_filename_ = argv[2];
    FilterDescriptor cur_filter;
    for (int i = 3; i < argc; i++) {
        std::string arg = argv[i];
        if (arg.starts_with('-')) {
            if (i != 3) {
                this->filters_.push_back(cur_filter);
            }
            cur_filter = FilterDescriptor();
            cur_filter.filter_name = arg.substr(1, arg.size() - 1);
            cur_filter.filter_params = std::vector<std::string>();
        } else {
            cur_filter.filter_params.push_back(arg);
        }
    }
    if (argc != 3) {
        this->filters_.push_back(cur_filter);
    }
    return ParseRes::Ok;
}
}