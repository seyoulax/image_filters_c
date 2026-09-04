#ifndef IMAGE_PROCESSOR_APP_H
#define IMAGE_PROCESSOR_APP_H

#include <string>
#include <vector>
#include <map>

namespace image_processor {
    inline std::map<std::string, std::vector<std::pair<std::string, std::string>>> filters_info;
    class App {
    public:
        App(){};
        void Init();
        void Run(int argc, char** argv);
        void PrintHelp() const;
    };
}

#endif
