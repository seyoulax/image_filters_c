#ifndef IMAGE_PROCESSOR_ERROR_HANDLERS_H
#define IMAGE_PROCESSOR_ERROR_HANDLERS_H

#include "parser.h"
#include "bmp_reader.h"
#include "bmp_writer.h"
#include "base_filter.h"
#include "filter_factory.h"

namespace image_processor {

bool HandleParseRes(const Parser::ParseRes res);
bool HandleBmpReadRes(const BmpReader::ReadBmpRes res);
bool HandleBmpWriteRes(const BmpWriter::BmpWriteRes);
bool HandlePipeFillingRes(const PipeFillingRes);

}

#endif  // IMAGE_PROCESSOR
