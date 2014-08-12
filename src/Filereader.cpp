#include "Filereader.hpp"

#include <fstream>
#include <iostream> // TODO just for cout could be removed

Filereader::Filereader() {
}

void Filereader::parse(char ch) {
        switch(ch) {
                case '\n':
                        break;
                default:
                        break;
        }
}


std::vector<std::string> Filereader::readFile(std::string filename) {
        std::vector<std::string> tokens;
        char ch;

        std::fstream fin(filename.c_str(), std::fstream::in);
        while (fin >> std::noskipws >> ch) {
                std::cout << ch;
                parse(ch);
        }

        return tokens;
}
