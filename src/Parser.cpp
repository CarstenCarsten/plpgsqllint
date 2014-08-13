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

bool Parser::isEndDollarQuote(std::string startDollarQuote) {
        std::string endDollarQuote = readDollarQuote();
        before();
        before();
        before();
        return startDollarQuote.compare(endDollarQuote) == 0;
}

bool Parser::isEscapedSingleLineStringLiteral() {
        bool result = false;
        if(hasNext() && isSingleLineStringLiteral()) {
                next();
                if(hasNext() && isSingleLineStringLiteral()) {
                        result = true;
                }
                before();
        }
        return result;
}

bool Parser::isLanguage() {
        return boost::iequals("LANGUAGE", token);
}

bool Parser::isMultiLineStringLiteral() {
        return token.compare("$") == 0;
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
        return isMultiLineStringLiteral() || isSingleLineStringLiteral();
}

bool Parser::isVariableName() {
        return token.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ01234567890_") == std::string::npos;
}

bool Parser::isWhitespace() {
        return token.find_first_not_of(" \t") == std::string::npos;
}

bool Parser::hasNext() {
        return position < tokens.size();
}

void Parser::next() {
        token = tokens[position++];
}

void Parser::before() {
        token = tokens[--position];
}

std::string Parser::readStringLiteral() {
        std::string stringLiteralContent;
        if(hasNext() && isSingleLineStringLiteral()) {
                next();
                while(hasNext() && !isNewline()
                      && !isSingleLineStringLiteral()
                      && !isEscapedSingleLineStringLiteral()) {
                        stringLiteralContent.append(token);
                        next();
                }
                if(isNewline()) {
                        std::cout << "[ERROR  ] string literal was not ended with '" << std::endl;
                }
                if(hasNext() && isSingleLineStringLiteral()) {
                        next();
                } else {
                        std::cout << "[ERROR  ] expected string literal to end with '" << std::endl;
                }
        } else if(hasNext() && isMultiLineStringLiteral()) {
                std::string startDollarQuote = readDollarQuote();
                while(hasNext() && !isEndDollarQuote(startDollarQuote)) {
                        stringLiteralContent.append(token);
                        next();
                }
                if(isEndDollarQuote(startDollarQuote)) {
                        std::string endDollarQuote = readDollarQuote();
                } else {
                        std::cout << "[ERROR  ] could not find terminating dollar quote" << std::endl;                
                }
        }
        return stringLiteralContent;
}

std::string Parser::readDollarQuote() {
        std::string dollarQuote;
        if(hasNext() && isMultiLineStringLiteral()) {
                dollarQuote.append(token);
                next();
                if(hasNext() && isVariableName()) {
                        dollarQuote.append(token);
                        next();                
                        if(hasNext() && isMultiLineStringLiteral()) {
                                dollarQuote.append(token);
                                next();
                        } else {
                                std::cout << "[ERROR  ] expected a ending dollar sign for dollar quote" << std::endl;
                        }
                } else {
                        std::cout << "[ERROR  ] expected a variable name for dollar quoting" << std::endl;
                }
        } else {
                std::cout << "[ERROR  ] expected a starting dollar sign for dollar quote" << std::endl;
        }
        return dollarQuote;
}

void Parser::skipWhitespacesAndNewlines() {
        while(hasNext() && (isWhitespace() || isNewline())) {
                next();
        }
}

void Parser::parse() {
        while(hasNext()) {
                next();
        
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
