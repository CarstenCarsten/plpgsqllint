#include "StatementParser.hpp"

#include "DoParser.hpp"

#include <boost/algorithm/string/predicate.hpp>

#include <iostream>

StatementParser::StatementParser() {
}

StatementParser::StatementParser(std::vector<std::string> * tokens, unsigned int * pos,  unsigned int token_length ) {
        this->tokens       = tokens;
        this->pos          = pos;
        this->token_length = token_length;
        this->single_line_string_literal_level = 1;
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
        bool done = false;
        unsigned int upticks = 0;
        unsigned int runs = 0;

        while(!done && hasNext()) {
                runs++;
                if((*tokens)[*pos].compare("'") == 0) {
                        upticks++;
                } else {
                        done = true;
                }
                if(runs >= (single_line_string_literal_level*2)) {
                        done = true;
                } else {
                        next();
                }
        }
        *pos = *pos - (runs - 1);
        return upticks == (single_line_string_literal_level*2);
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

// single line string literals can be escaped therefore all this
// counting and skipping I am not sure if that is necessary
// but currently it makes sense, at least in my mind
bool StatementParser::isSingleLineStringLiteral() {
        bool done = false;
        unsigned int upticks = 0;
        unsigned int runs = 0;
     
        while(!done && hasNext()) {
                runs++;
                if((*tokens)[*pos].compare("'") == 0) {
                        upticks++;
                } else {
                        done = true;
                }
                if(runs >= single_line_string_literal_level) {
                        done = true;
                } else {
                        next();
                }
        }
        *pos = *pos - (runs - 1);
        return upticks == single_line_string_literal_level;
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
        return *pos < token_length;
}

void StatementParser::next() {
        *pos = *pos + 1;
}

void StatementParser::before() {
        *pos = *pos - 1;
}

void StatementParser::skipSingleLineStringLiteral() {
       *pos = *pos + single_line_string_literal_level;
}

void StatementParser::skipEscapedSingleLineStringLiteral() {
       *pos = *pos + (single_line_string_literal_level * 2);
}

unsigned int StatementParser::findEndPositionOfSingleLineStringLiteral() {
        unsigned int currentPos = *pos;
        unsigned int endSingleLineStringLiteralPos = *pos;
        if(hasNext() && isSingleLineStringLiteral()) {
                skipSingleLineStringLiteral();
                while(hasNext() && !isNewline()
                      && !isSingleLineStringLiteral()
                      && isEscapedSingleLineStringLiteral()) {
                        if(isEscapedSingleLineStringLiteral()) {
                                skipEscapedSingleLineStringLiteral();
                        } else {
                                next();
                        }
                        
                }
                if(isNewline()) {
                        std::cout << "[ERROR  ] string literal was not ended correctly, but instead newline" << std::endl;
                }
                if(hasNext() && isSingleLineStringLiteral()) {
                        endSingleLineStringLiteralPos = *pos;
                } else {
                        std::cout << "[ERROR  ] expected end of single line string literal" << std::endl;
                }
        } else {
                if(!hasNext()) {
                        std::cout << "[ERROR  ] Expected a string literal, but nothing left to read" << std::endl;                
                } else {
                        std::cout << "[ERROR  ] Expected a string literal, but current position is no string literal" << std::endl;
                }
        }
        *pos = currentPos;
        return endSingleLineStringLiteralPos;
}

std::string StatementParser::readStringLiteral() {
        std::string stringLiteralContent;
        if(hasNext() && isSingleLineStringLiteral()) {
                skipSingleLineStringLiteral();
                while(hasNext() && !isNewline()
                      && !isSingleLineStringLiteral()
                      && isEscapedSingleLineStringLiteral()) {
                        if(isEscapedSingleLineStringLiteral()) {
                                for(unsigned int i = 0; i < single_line_string_literal_level * 2; i++) {
                                        stringLiteralContent.append((*tokens)[*pos]);
                                }
                        } else {
                                stringLiteralContent.append((*tokens)[*pos]);
                                next();
                        }
                }
                if(isNewline()) {
                        std::cout << "[ERROR  ] string literal was not ended with '" << std::endl;
                }
                if(hasNext() && isSingleLineStringLiteral()) {
                        skipSingleLineStringLiteral();
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
