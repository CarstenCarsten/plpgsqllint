#ifndef FILEREADER_HPP
#define FILEREADER_HPP

#include <string>
#include <vector>

class Filereader {
        private:
                bool isAlphanumericOrUnderscore(char ch);
        public:
                Filereader();
                std::vector<std::string> readFile(std::string filename);
};

#endif
