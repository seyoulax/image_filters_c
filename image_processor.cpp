////////////////////////////////////////////////////////////////////////////////
/// \file
/// \brief      Main module for Contest X Problem Y
/// \author     Student's Name
/// \version    0.1.0
/// \date       25.01.2021
///
/// Copy the task description here.
///
////////////////////////////////////////////////////////////////////////////////

#include <cassert>
#include <iostream>

#include "app.h"
#include "parser/parser.h"

void TestParser(int argc, char** argv) {
    image_processor::Parser parser;
    int parse_res = parser.Parse(argc, argv);
    assert(parse_res == 0);
    std::cout << 0;
}

void TestApp(int argc, char** argv) {
    image_processor::App app = image_processor::App();
    //standart running
    try {
        app.Init();
        app.Run(argc, argv);
    } catch (std::exception& e) {
        std::cout << e.what() << std::endl;
    }
}

int main(int argc, char** argv) {
    TestApp(argc, argv);
    // TestParser(argc, argv);

    return 0;
}
