#include "CodeDoParser.hpp"

#include <iostream>

void CodeDoParser::readDeclare() {
}

// these are in IF conditionals, but perhaps somewhere else as well
void CodeDoParser::parseBooleanExpression() {
        skipWhitespacesAndNewlines();
        if(hasNext() && isOpeningParentheses()) {
                // inside the brackets of a 
                parseBooleanExpression();
//                skipWhitespacesAndNewlines();
                if(!hasNext() || !isClosingParentheses()) {
                        std::cout << "[ERROR  ] missing closing Parentheses" << std::endl;
                }
        }
        if(hasNext() && isEquals()) {
                next();
        }
        if(hasNext() && isVariableName() && !isThen()) {
                readVariableName();
        }
        if(hasNext() && isThen()) {
                return;
        }
        if(hasNext() && isClosingParentheses()) {
                return;
        }
        if(hasNext() && isAnd()) {
                next();
        }
        if(hasNext() && isOr()) {
                next();
        }
        if(hasNext() && isNot()) {
                next();
        }
        if(hasNext() && isDot()) {
                next();
        }
        if(hasNext() && isOpeningBracket()) {
                next();
        }
        if(hasNext() && isClosingBracket()) {
                next();
        }
//        skipWhitespacesAndNewlines();
}

void CodeDoParser::parse() {
        // 
        skipWhitespacesAndNewlines();
        if(hasNext() && isDeclare()) {
                // TODO Declare not implemented yet
                next();
//                readDeclare();
        }
        skipWhitespacesAndNewlines();
        if(hasNext() && isBegin()) {
                next();
        }
        skipWhitespacesAndNewlines();

        if(hasNext() && isStatement()) {
                // There is no need to limit the length of the statement
                StatementParser statementParser(tokens, pos, token_length);
                statementParser.parse();
        } else if(hasNext() && isIf()) {
                next();
                parseBooleanExpression();
        }

        if(hasNext() && isEnd()) {
                next();
        }
        if(hasNext() && isSemicolon()) {
                next();
        }
}
