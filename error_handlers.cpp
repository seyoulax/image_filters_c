#include "error_handlers.h"

#include <format>
#include <iostream>

namespace image_processor {
bool HandleParseRes(const Parser::ParseRes res) {
    switch (res) {
        case Parser::ParseRes::Ok:
            return true;
        case Parser::ParseRes::InputFilenameNotPasses:
            std::cerr << "Parser: Input filename not passed or arguments order broken";
            return false;
        case Parser::ParseRes::OutputFilenameNotPasses:
            std::cerr << "Parser: Output filename not passed or arguments order broken";
            return false;
        case Parser::ParseRes::EmptyArgs:
            std::cerr << "Parser: No arguments passed";
            return false;
    }
    // unknow error
    return false;
}

bool HandleBmpReadRes(const BmpReader::ReadBmpRes res) {
    switch (res) {
        case BmpReader::ReadBmpRes::Ok:
            return true;
        case BmpReader::ReadBmpRes::FailedOpenFile:
            std::cerr << "BmpReader: cannot open file";
            return false;
        case BmpReader::ReadBmpRes::FailedReadSignature:
            std::cerr << "BmpReader: failed to read signature";
            return false;
        case BmpReader::ReadBmpRes::BmpTypeError:
            std::cerr << "BmpReader: not a BMP file (signature mismatch)";
            return false;
        case BmpReader::ReadBmpRes::FailedSkipHeader:
            std::cerr << "BmpReader: failed to skip file header fields";
            return false;
        case BmpReader::ReadBmpRes::FailedReadBitOffset:
            std::cerr << "BmpReader: failed to read pixel offset (bfOffBits)";
            return false;
        case BmpReader::ReadBmpRes::FailedReadHeaderSize:
            std::cerr << "BmpReader: failed to read DIB header size (biSize)";
            return false;
        case BmpReader::ReadBmpRes::DibHeaderTypeNotSupported:
            std::cerr << "BmpReader: unsupported DIB header (need BITMAPINFOHEADER, 40 bytes)";
            return false;
        case BmpReader::ReadBmpRes::FailedReadWidth:
            std::cerr << "BmpReader: failed to read width";
            return false;
        case BmpReader::ReadBmpRes::InvalidNotPositiveWidth:
            std::cerr << "BmpReader: non-positive width";
            return false;
        case BmpReader::ReadBmpRes::InvalidNotPositiveHeight:
            std::cerr << "BmpReader: non-positive height";
            return false;
        case BmpReader::ReadBmpRes::FailedReadHeight:
            std::cerr << "BmpReader: failed to read height";
            return false;
        case BmpReader::ReadBmpRes::FailedReadColorPlanes:
            std::cerr << "BmpReader: failed to read color planes (biPlanes)";
            return false;
        case BmpReader::ReadBmpRes::PlaneNumNotSupported:
            std::cerr << "BmpReader: biPlanes != 1 is not supported";
            return false;
        case BmpReader::ReadBmpRes::FailedReadNumBitPerPixel:
            std::cerr << "BmpReader: failed to read bits-per-pixel (biBitCount)";
            return false;
        case BmpReader::ReadBmpRes::BitNumNoSupported:
            std::cerr << "BmpReader: only 24 bpp supported";
            return false;
        case BmpReader::ReadBmpRes::FailedReadCompression:
            std::cerr << "BmpReader: failed to read compression (biCompression)";
            return false;
        case BmpReader::ReadBmpRes::NoCompressionSupported:
            std::cerr << "BmpReader: only BI_RGB (no compression) supported";
            return false;
        case BmpReader::ReadBmpRes::InvalidPixelOffset:
            std::cerr << "BmpReader: invalid pixel offset (seek failed)";
            return false;
        case BmpReader::ReadBmpRes::UnexpectedEOF:
            std::cerr << "BmpReader: unexpected EOF while reading pixel data";
            return false;
    }
    // unknow error
    return false;
}

bool HandleBmpWriteRes(const BmpWriter::BmpWriteRes res) {
    switch (res) {
        case BmpWriter::BmpWriteRes::Ok:
            return true;
        case BmpWriter::BmpWriteRes::InvalidImageSize:
            std::cerr << "BmpWriter: Height and width of the image should be positive";
            return false;
        case BmpWriter::BmpWriteRes::FailedToCreateFile:
            std::cerr << "BmpWriter: Failed to create or read destination file";
            return false;
    }
    // unknown error
    return false;
};

bool HandlePipeFillingRes(const PipeFillingRes res) {
    switch (res.first) {
        case FilterCreatingRes::Ok:
            return true;
        case FilterCreatingRes::InvalidParametersNumber:
            std::cerr << std::format("FilterCreator: Parameters number of filters {} is incorrect", res.second);
            return false;
        case FilterCreatingRes::InvalidParametersValue:
            std::cerr << std::format("FilterCreator: Parameters values of filter {} is incorrect", res.second);
            return false;
    }
    // unknown error
    return false;
};

}