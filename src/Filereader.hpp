#ifndef FILEREADER_HPP
#define FILEREADER_HPP

#include <string>
#include <vector>

class Filereader {
        private:
                bool isSeperator(char ch);
                bool isNewline(char ch);
        public:
                Filereader();
                std::vector<std::string> readFile(std::string filename);
};

#endif
