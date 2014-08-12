#include "DoParser.hpp"

#include <iostream>

DoParser::DoParser() {
}

void DoParser::parse() {
        while(position < tokens.size()) {
                std::string token = tokens[position++];
        
                if(isWhitespace(token)) {
                        // NOOP
                } else if(isDo(token)) {
                        DoParser doParser;
                        children.push_back(doParser);
                        doParser.parse();
                } else {
                        std::cout << token;
                }
        }
        std::cout << tokens[position++];
}
