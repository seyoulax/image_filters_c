#include "app.h"

#include <iostream>
#include <ostream>
#include <string>

//bmp
#include "bmp.h"
#include "bmp_reader.h"
#include "bmp_writer.h"
//helpers
#include "parser.h"
#include "error_handlers.h"
//filters
#include "crop_filter.h"
#include "gs_filter.h"
#include "neg_filter.h"
#include "edge_filter.h"
#include "sharp_filter.h"
#include "blur_filter.h"
#include "base_filter.h"
#include "filter_factory.h"
#include "pipeline.h"

#include <format>

namespace image_processor {

void App::Init() {
    filter_creators.insert({"crop", &CreateCropFilter});
    filter_creators.insert({"gs", &CreateGrayscaleFilter});
    filter_creators.insert({"neg", &CreateNegFilter});
    filter_creators.insert({"sharp", &CreateSharpFilter});
    filter_creators.insert({"edge", &CreateEdgeFilter});
    filter_creators.insert({"blur", &CreateBlurFilter});

    filters_info.insert(
    {"blur",
        {
            {"blur", "applies gaussian blur"},
            {"sigma", "standart deviation while applying gaussian blur"}
            }
        }
    );
    filters_info.insert(
    {"gs",
        {
            {"gs", "convert an image to grayscale"},
            }
        }
    );
    filters_info.insert(
    {"crop",
        {
            {"crop", "crop image to desired width and height"},
            {"width", "desired width of the image. Must be positive"},
            {"height", "desired height of the image. Must be positive"},
            }
        }
    );
    filters_info.insert(
    {"neg",
        {
            {"neg", "inverse image colors"}
            }
        }
    );
    filters_info.insert(
    {"edge",
        {
            {"edge", "Apply -gs and then find edges on the image using passed threshold"},
            {"threshold", "Used to determine if the pixel is edge or not"}
            }
        }
    );
    filters_info.insert(
    {"sharp",
        {
            {"sharp", "Make image more sharp using specific filter"}
            }
        }
    );

}

void App::PrintHelp() const {
    std::cout << "Welcome to best Image processor in the internet!" << std::endl << std::endl;
    std::cout << "To start you should pass arguments in the following format:" << std::endl;
    std::cout << "[path to programm] [path to input image file] [path to output image file] " <<
                 "[-filter_1] [filter param 1] ... [filter param n] " <<
                 "[-filter_2] [filter param 1] ... [filter param n] ..."  << std::endl;

    for (std::pair<std::string, std::vector<std::pair<std::string, std::string>>> cur_filter : filters_info) {
        for (std::pair<std::string, std::string> cur_filter_param : cur_filter.second) {
            if (cur_filter_param.first == cur_filter.first) {
                std::cout << std::endl << std::format(
                  "Filter -{} {}. Number of filter parameters: {}",
                    cur_filter_param.first, cur_filter_param.second, cur_filter.second.size() - 1) << std::endl;
            } else {
                std::cout << std::format(
                "Parameter {} {}",
                cur_filter_param.first, cur_filter_param.second) << std::endl;
            }
        }
    }
}

void App::Run(int argc, char** argv) {
    // Parse arguments returning ParseRes
    Parser parser = Parser();
    Parser::ParseRes parser_res = parser.Parse(argc, argv);
    if (parser_res == Parser::InputFilenameNotPasses) {
        PrintHelp();
        return;
    }
    bool parse_res_flg = HandleParseRes(parser_res);
    if (!parse_res_flg) {
        return;
    }

    const std::string& input_filename = parser.GetInputFilename();
    const std::string& output_filename = parser.GetOutputFilename();

    //Reading the file
    BmpImage image = BmpImage();
    BmpReader image_reader = BmpReader(input_filename);
    BmpReader::ReadBmpRes read_bmp_res = image_reader.Read(image);
    bool read_bmp_res_flg = HandleBmpReadRes(read_bmp_res);
    if (!read_bmp_res_flg) {
        return;
    }

    const std::vector<FilterDescriptor>& f_descriptors = parser.GetFilters();

    // creating Pipeline
    Pipeline pipe = Pipeline();

    // creating FilterFactory
    FilterFactory filter_factory = FilterFactory();
    PipeFillingRes pipe_fill_res = filter_factory.FillPipeline(f_descriptors, pipe);
    bool pipe_fill_res_flg = HandlePipeFillingRes(pipe_fill_res);
    if (!pipe_fill_res_flg) {
        return;
    }

    // Applying pipeline
    pipe.Apply(image);

    // Writing File
    BmpWriter image_writer = BmpWriter(output_filename);
    BmpWriter::BmpWriteRes write_bmp_res = image_writer.Write(image);
    HandleBmpWriteRes(write_bmp_res);
}

}