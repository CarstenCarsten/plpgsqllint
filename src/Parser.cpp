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

bool Parser::isSingleLineStringLiteral() {
        return token.compare("'") == 0;
}

bool Parser::isStringLiteral() {
        return token.compare("$") == 0 || isSingleLineStringLiteral();
}

bool Parser::isWhitespace() {
        return token.find_first_not_of(" \t") == std::string::npos;
}


std::string Parser::consumeStringLiteral() {
        std::string stringLiteralContent;
        if(position < tokens.size() && token.compare("'") == 0) {
                token = tokens[position++];
                while(position < tokens.size() && !isNewline() && !isSingleLineStringLiteral()) {
                        stringLiteralContent.append(token);
                        token = tokens[position++];
                }
                if(isNewline()) {
                        std::cout << "[ERROR  ] string literal was not ended with '" << std::endl;
                }
                if(position < tokens.size() && isSingleLineStringLiteral()) {
                        token = tokens[position++];
                } else {
                        std::cout << "[ERROR  ] expected string literal to end with '" << std::endl;
                }
        } else if(position < tokens.size() && token.compare("$") == 0) {
                std::cout << "[ERROR  ] NOT IMPLEMENTED YET" << std::endl;       
        }
        return stringLiteralContent;
}

void Parser::skipWhitespacesAndNewlines() {
        while(position < tokens.size() && (isWhitespace() || isNewline())) {
                token = tokens[position++];
        }
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
