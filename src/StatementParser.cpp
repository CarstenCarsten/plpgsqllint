#include "StatementParser.hpp"

#include "DoParser.hpp"

#include <boost/algorithm/string/predicate.hpp>

#include <iostream>

StatementParser::StatementParser() {
}

StatementParser::StatementParser(std::vector<std::string> * tokens, unsigned int * pos,  unsigned int * token_length ) {
        this->tokens       = tokens;
        this->pos          = pos;
        this->token_length = token_length;
}

bool StatementParser::isDo() {
        return boost::iequals("DO", (*tokens)[*pos]);
}

bool StatementParser::isEndDollarQuote(std::string startDollarQuote) {
        std::string endDollarQuote = readDollarQuote();
        before();
        before();
        before();
        return startDollarQuote.compare(endDollarQuote) == 0;
}

bool StatementParser::isEscapedSingleLineStringLiteral() {
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

bool StatementParser::isLanguage() {
        return boost::iequals("LANGUAGE", (*tokens)[*pos]);
}

bool StatementParser::isMultiLineStringLiteral() {
        return (*tokens)[*pos].compare("$") == 0;
}

bool StatementParser::isNewline() {
        return (*tokens)[*pos].compare("\r\n") == 0 || (*tokens)[*pos].compare("\n") == 0;
}

bool StatementParser::isPlpgsql() {
        return boost::iequals("PLPGSQL", (*tokens)[*pos]);
}

bool StatementParser::isSingleLineStringLiteral() {
        return (*tokens)[*pos].compare("'") == 0;
}

bool StatementParser::isStringLiteral() {
        return isMultiLineStringLiteral() || isSingleLineStringLiteral();
}

bool StatementParser::isVariableName() {
        return (*tokens)[*pos].find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ01234567890_") == std::string::npos;
}

bool StatementParser::isWhitespace() {
        return (*tokens)[*pos].find_first_not_of(" \t") == std::string::npos;
}

bool StatementParser::hasNext() {
        return *pos < *token_length;
}

void StatementParser::next() {
        *pos = *pos + 1;
}

void StatementParser::before() {
        *pos = *pos - 1;
}

std::string StatementParser::readStringLiteral() {
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

std::string StatementParser::readDollarQuote() {
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

void StatementParser::skipWhitespacesAndNewlines() {
        while(hasNext() && (isWhitespace() || isNewline())) {
                next();
        }
}

void StatementParser::parse() {
        while(hasNext()) {        
                if(isWhitespace()) {
                        // NOOP
                } else if(isDo()) {
                        // I don't know where the do statement ends
                        // but there is no constraint for the do statement
                        // so it will simply return, once parsed the statement
                        DoParser doParser(tokens,pos, token_length);
                        children.push_back(doParser);
                        doParser.parse();
                } else {
                        std::cout << (*tokens)[*pos];
                }
                next();
        }
}
