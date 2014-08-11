#ifndef CONFIGURATION_HPP
#define CONFIGURATION_HPP

#include <string>

class Configuration {
        public:
                Configuration();
                void parseCommandline(int argc, char* argv[]);
                std::string getInputFile(std::string filename);
};

#endif
