#include "Filereader.hpp"

#include <fstream>
#include <iostream> // TODO just for cout could be removed

Filereader::Filereader() {
}

bool Filereader::isAlphanumericOrUnderscore(char ch) {
        if(ch > 47 && ch < 58) {
                return true;
        } else if(ch > 64 && ch < 90) {
                return true;
        } else if(ch > 96 && ch < 123) {
                return true;
        } else if(ch == 95) {
                return true;
        }
        return false;
}

std::vector<std::string> Filereader::readFile(std::string filename) {
        std::vector<std::string> tokens; // has all the strings conveniently seperated "HELLO  WORLD" -> "HELLO","   ","WORLD"
        char ch   = ' '; // current character that is added to the token
        char prev = ' '; // the previous element
        std::fstream fin(filename.c_str(), std::fstream::in); 
        std::string token; // the element that will be added to the tokens

        while(fin >> std::noskipws >> ch) {
                if((ch == ' ' || ch == '\t') && (prev == ' ' || prev == '\t')) {
                        token.append(1,ch);
                } else if(ch == '\n' && prev == '\r') {
                        token.append(1,ch);
                } else if(ch == '-' && prev == '-') {
                        token.append(1,ch);
                } else if(ch == '*' && prev == '/') {
                        token.append(1,ch);
                } else if(ch == '/' && prev == '*') {
                        token.append(1,ch);
                } else if(ch == '=' && prev == ':') {
                        token.append(1,ch);
                } else if(ch == '=' && prev == '!') {
                        token.append(1,ch);
                } else if(ch == ':' && prev == ':') {
                        token.append(1,ch);
                } else if(ch == '|' && prev == '|') {
                        token.append(1,ch);
                } else if(ch == '('  || ch == ')' || ch == ','  || ch == ';' || ch == '.'  ||
                          ch == '='  || ch == ':' || ch == '/'  || ch == '*' || ch == '\n' ||
                          ch == '\r' || ch == ' ' || ch == '\t' || ch == '-' || ch == '\'' ||
                          ch == '!'  || ch == '%' || ch == '|'  || ch == '#' || ch == '$') {
                        std::cout << token << std::endl;
                        tokens.push_back(token);
                        token = std::string("");
                        token.append(1,ch);
                } else if(isAlphanumericOrUnderscore(ch) && !isAlphanumericOrUnderscore(prev)){
                        std::cout << token << std::endl;
                        tokens.push_back(token);
                        token = std::string("");
                        token.append(1,ch);
                } else {
                        token.append(1,ch);
                }
                prev = ch;
        }
        std::cout << token << std::endl;
        tokens.push_back(token);        

        return tokens;
}
