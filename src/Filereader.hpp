#ifndef FILEREADER_HPP
#define FILEREADER_HPP

#include <string>
#include <vector>

class Filereader {
        private:
                void parse(char ch);
        public:
                Filereader();
                std::vector<std::string> readFile(std::string filename);
};

#endif
