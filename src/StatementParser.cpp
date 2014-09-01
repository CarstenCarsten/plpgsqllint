#include "StatementParser.hpp"

#include "DoParser.hpp"
#include "PerformParser.hpp"

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

bool StatementParser::isAnd() {
        return boost::iequals("AND", (*tokens)[*pos]);
}


bool StatementParser::isBegin() {
        return boost::iequals("BEGIN", (*tokens)[*pos]);
}

bool StatementParser::isClosingBrackets() {
        return (*tokens)[*pos].compare("]") == 0;
}

bool StatementParser::isClosingChevrons() {
        return (*tokens)[*pos].compare(">") == 0;
}

bool StatementParser::isClosingParentheses() {
        return (*tokens)[*pos].compare(")") == 0;
}

bool StatementParser::isDeclare() {
        return boost::iequals("DECLARE", (*tokens)[*pos]);
}

bool StatementParser::isDelete() {
        return boost::iequals("DELETE", (*tokens)[*pos]);
}

bool StatementParser::isDo() {
        return boost::iequals("DO", (*tokens)[*pos]);
}

bool StatementParser::isDot() {
        return (*tokens)[*pos].compare(".") == 0;
}

bool StatementParser::isEnd() {
        return boost::iequals("END", (*tokens)[*pos]);
}

bool StatementParser::isEndDollarQuote(std::string startDollarQuote) {
        unsigned int currentPos = *pos;
        std::string endDollarQuote;
        if(hasNext() && isMultiLineStringLiteral()) {
                endDollarQuote.append((*tokens)[*pos]);
                next();
                if(hasNext() && isVariableName()) {
                        endDollarQuote.append((*tokens)[*pos]);
                        next();                
                        if(hasNext() && isMultiLineStringLiteral()) {
                                endDollarQuote.append((*tokens)[*pos]);
                                next();
                        } 
                }
        }
        *pos = currentPos;
        return startDollarQuote.compare(endDollarQuote) == 0;
}

bool StatementParser::isEquals() {
        return (*tokens)[*pos].compare("=") == 0;
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

bool StatementParser::isIf() {
        return boost::iequals("IF", (*tokens)[*pos]);
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

bool StatementParser::isNot() {
        return boost::iequals("NOT", (*tokens)[*pos]);
}

bool StatementParser::isNull() {
        return boost::iequals("NULL", (*tokens)[*pos]);
}

bool StatementParser::isOpeningBrackets() {
        return (*tokens)[*pos].compare("[") == 0;
}

bool StatementParser::isOpeningChevrons() {
        return (*tokens)[*pos].compare("<") == 0;
}


bool StatementParser::isOpeningParentheses() {
        return (*tokens)[*pos].compare("(") == 0;
}

bool StatementParser::isOr() {
        return boost::iequals("OR", (*tokens)[*pos]);
}

bool StatementParser::isPerform() {
        return boost::iequals("PERFORM", (*tokens)[*pos]);
}

bool StatementParser::isPlpgsql() {
        return boost::iequals("PLPGSQL", (*tokens)[*pos]);
}

bool StatementParser::isSelect() {
        return boost::iequals("SELECT", (*tokens)[*pos]);
}

bool StatementParser::isSemicolon() {
        return (*tokens)[*pos].compare(";") == 0;
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

bool StatementParser::isSlash() {
        return (*tokens)[*pos].compare("/") == 0;        
}

bool StatementParser::isStatement() {
        if(boost::iequals("DO", (*tokens)[*pos])) {
                return true;
        }
        if(boost::iequals("PERFORM", (*tokens)[*pos])) {
                return true;
        }
        return false;
}

bool StatementParser::isStringLiteral() {
        return isMultiLineStringLiteral() || isSingleLineStringLiteral();
}

bool StatementParser::isThen() {
        return boost::iequals("THEN", (*tokens)[*pos]);
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

void StatementParser::skipEscapedSingleLineStringLiteral() {
       *pos = *pos + (single_line_string_literal_level * 2);
}

void StatementParser::skipSingleLineStringLiteral() {
       *pos = *pos + single_line_string_literal_level;
}

void StatementParser::skipWhitespaces() {
        while(hasNext() && isWhitespace()) {
                next();
        }
}

void StatementParser::skipWhitespacesAndNewlines() {
        while(hasNext() && (isWhitespace() || isNewline())) {
                next();
        }
}

/*
 * This method expects that pos is on the first $
 */
unsigned int StatementParser::findEndPositionOfMultiLineStringLiteral() {
        unsigned int currentPos = *pos;
        unsigned int endingDollarQuotePos = *pos;
        if(hasNext() && isMultiLineStringLiteral()) {
                std::string dollarQuote = readDollarQuote();
                do {
                        while(hasNext() && !isMultiLineStringLiteral()) {
                                next();
                        }
                } while(hasNext() && !isEndDollarQuote(dollarQuote));
                if(isEndDollarQuote(dollarQuote)) {
                        endingDollarQuotePos = *pos;
                } else {
                        std::cout << "[ERROR  ] could not find endingDollarQuote" << std::endl;
                }
        }
        *pos = currentPos;
        return endingDollarQuotePos;
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

/*
 * This method expects that the position is currently on a string literal
 * either ' oder $
 */
std::string StatementParser::readStringLiteral() {
        std::string stringLiteralContent;
        if(hasNext() && isSingleLineStringLiteral()) {
                unsigned int endofSingleLineStringLiteral = findEndPositionOfSingleLineStringLiteral();
                skipSingleLineStringLiteral();
                while(*pos < endofSingleLineStringLiteral) {
                        stringLiteralContent.append((*tokens)[*pos]);
                        next();
                }
                skipSingleLineStringLiteral();
        } else if(hasNext() && isMultiLineStringLiteral()) {
                std::string startDollarQuote = readDollarQuote();
                while(hasNext() && !isEndDollarQuote(startDollarQuote)) {
                        stringLiteralContent.append((*tokens)[*pos]);
                        next();
                }
                if(isEndDollarQuote(startDollarQuote)) {
                        std::string endDollarQuote = readDollarQuote();
                } else {
                        std::cout << "[ERROR  ] could not find terminating dollar quote for {" << startDollarQuote << "}" << std::endl;                
                }
        }
        return stringLiteralContent;
}

std::string StatementParser::readVariableName() {
        // TODO return the variable name
        return "";
}

void StatementParser::parse() {
        // after a statement has been executed
        // a semicolon is allowed
        bool wasCommandExecuted = false;
        while(hasNext()) {        
                if(isWhitespace()) {
                        // NOOP
                } else if(isDo()) {
                        // I don't know where the do statement ends
                        // but there is no constraint for the do statement
                        // so it will simply return, once parsed the statement
                        std::cout << "[DEBUG  ] calling do parser {" << (*tokens)[*pos] << "}" << std::endl;

                        DoParser doParser(tokens, pos, token_length);
                        children.push_back(doParser);
                        doParser.parse();
                        wasCommandExecuted = true;
                } else if(isPerform()) {
                        PerformParser performParser(tokens, pos, token_length);
                        children.push_back(performParser);
                        performParser.parse();
                        wasCommandExecuted = true;
                } else if(isSelect()) {
                        std::cout << "[ERROR  ] calling select parser" << std::endl;
                } else if(isDelete()) {
                       std::cout << "[ERROR  ] calling delete parser" << std::endl;
                }
                if(hasNext() && isSemicolon() && wasCommandExecuted) {
                        wasCommandExecuted = false;
                }
                next();
        }
}
