#include "Parser.hpp"

#include "DoParser.hpp"

#include <boost/algorithm/string/predicate.hpp>

#include <iostream>

Parser::Parser() {
}

Parser::Parser(std::vector<std::string> * tokens, unsigned int * pos ) {
        this->tokens = tokens;
        this->pos    = pos;
}

bool Parser::isDo() {
        return boost::iequals("DO", (*tokens)[*pos]);
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
        return boost::iequals("LANGUAGE", (*tokens)[*pos]);
}

bool Parser::isMultiLineStringLiteral() {
        return (*tokens)[*pos].compare("$") == 0;
}

bool Parser::isNewline() {
        return (*tokens)[*pos].compare("\r\n") == 0 || (*tokens)[*pos].compare("\n") == 0;
}

bool Parser::isPlpgsql() {
        return boost::iequals("PLPGSQL", (*tokens)[*pos]);
}

bool Parser::isSingleLineStringLiteral() {
        return (*tokens)[*pos].compare("'") == 0;
}

bool Parser::isStringLiteral() {
        return isMultiLineStringLiteral() || isSingleLineStringLiteral();
}

bool Parser::isVariableName() {
        return (*tokens)[*pos].find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ01234567890_") == std::string::npos;
}

bool Parser::isWhitespace() {
        return (*tokens)[*pos].find_first_not_of(" \t") == std::string::npos;
}

bool Parser::hasNext() {
        return *pos < tokens->size();
}

void Parser::next() {
        *pos = *pos + 1;
}

void Parser::before() {
        *pos = *pos - 1;
}

std::string Parser::readStringLiteral() {
        std::string stringLiteralContent;
        if(hasNext() && isSingleLineStringLiteral()) {
                next();
                while(hasNext() && !isNewline()
                      && !isSingleLineStringLiteral()
                      && !isEscapedSingleLineStringLiteral()) {
                        stringLiteralContent.append((*tokens)[*pos]);
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
                        stringLiteralContent.append((*tokens)[*pos]);
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
                dollarQuote.append((*tokens)[*pos]);
                next();
                if(hasNext() && isVariableName()) {
                        dollarQuote.append((*tokens)[*pos]);
                        next();                
                        if(hasNext() && isMultiLineStringLiteral()) {
                                dollarQuote.append((*tokens)[*pos]);
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
                if(isWhitespace()) {
                        // NOOP
                } else if(isDo()) {
                        DoParser doParser(tokens,pos);
                        children.push_back(doParser);
                        doParser.parse();
                } else {
                        std::cout << (*tokens)[*pos];
                }
                next();
        }
}
