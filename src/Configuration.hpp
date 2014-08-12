#ifndef CONFIGURATION_HPP
#define CONFIGURATION_HPP

#include <string>

class Configuration {
        private:
                std::string inputfilename;
        public:
                Configuration();
                void parseCommandline(int argc, char* argv[]);
                std::string getInputfilename();
};

#endif
