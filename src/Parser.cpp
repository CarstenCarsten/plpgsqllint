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

bool Parser::isDo(std::string input) {
        return boost::iequals("DO", input);
}

bool Parser::isLanguage(std::string input) {
        return boost::iequals("LANGUAGE", input);
}

bool Parser::isNewline(std::string input) {
        return input.compare("\r\n") == 0 || input.compare("\n") == 0;
}

bool Parser::isPlpgsql(std::string input) {
        return boost::iequals("PLPGSQL", input);
}
bool Parser::isStringLiteral(std::string input) {
        return input.compare("$") == 0 || input.compare("'") == 0;
}

bool Parser::isWhitespace(std::string input) {
        return input.find_first_not_of(" \t") == std::string::npos;
}

std::string Parser::consumeStringLiteral() {
        return "";
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
