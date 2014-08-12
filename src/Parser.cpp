#include "Parser.hpp"

#include "DoParser.hpp"

#include <boost/algorithm/string/predicate.hpp>

#include <iostream>

std::vector<std::string> Parser::tokens;
unsigned int Parser::position = 0;

Parser::Parser() {
}

Parser::Parser(std::vector<std::string> tokensvector) {
        tokens = tokensvector;
}

bool Parser::isWhitespace(std::string input) {
        return input.find_first_not_of(" \t") == std::string::npos;
}

bool Parser::isDo(std::string input) {
        return boost::iequals("DO", input);
}

void Parser::parse() {
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
}
