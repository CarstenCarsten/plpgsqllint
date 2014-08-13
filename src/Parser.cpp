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

bool Parser::isDo() {
        return boost::iequals("DO", token);
}

bool Parser::isLanguage() {
        return boost::iequals("LANGUAGE", token);
}

bool Parser::isNewline() {
        return token.compare("\r\n") == 0 || token.compare("\n") == 0;
}

bool Parser::isPlpgsql() {
        return boost::iequals("PLPGSQL", token);
}
bool Parser::isStringLiteral() {
        return token.compare("$") == 0 || token.compare("'") == 0;
}

bool Parser::isWhitespace() {
        return token.find_first_not_of(" \t") == std::string::npos;
}

std::string Parser::consumeStringLiteral() {
        return "";
}

void Parser::parse() {
        while(position < tokens.size()) {
                token = tokens[position++];
        
                if(isWhitespace()) {
                        // NOOP
                } else if(isDo()) {
                        DoParser doParser;
                        children.push_back(doParser);
                        doParser.parse();
                } else {
                        std::cout << token;
                }
        }
}
