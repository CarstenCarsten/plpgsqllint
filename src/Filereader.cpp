#include "Filereader.hpp"

#include <fstream>
#include <iostream> // TODO just for cout could be removed

Filereader::Filereader() {
}

bool Filereader::isSeperator(char ch) {
        if(ch == ' ' || ch == '\t') {
                return true;
        } else {
                return false;
        }
}

bool Filereader::isNewline(char ch) {
        if(ch == '\n' || ch == '\r') {
                return true;
        } else {
                return false;
        }
}

std::vector<std::string> Filereader::readFile(std::string filename) {
        std::vector<std::string> tokens;
        char ch = ' ';
        std::fstream fin(filename.c_str(), std::fstream::in);
        std::string token;
        char prev = ' ';
        bool readTillNewline = false;

        while(fin >> std::noskipws >> ch) {
//                std::cout << ch;
                if(readTillNewline) {
                        if(isNewline(ch)) {
                                std::cout << token << std::endl;
                                tokens.push_back(token);
                                token = std::string("");
                                readTillNewline = false;
                        } else {
                                token.append(1,ch);
                        }
                } else {
                        switch(ch) {
                                case ' '  :
                                case '\t' :
                                        if(!isSeperator(prev)) {
                                                std::cout << token << std::endl;
                                                tokens.push_back(token);
                                                token = std::string("");
                                        }
                                        break;
                                case '-'  :
                                        token.append(1,ch);
                                        if(prev == '-') {
                                                readTillNewline = true;
                                        }
                                        break;
                                default   :
                                        token.append(1,ch);
                                        break;
                        }
                }
                prev = ch;
        }

        return tokens;
}
