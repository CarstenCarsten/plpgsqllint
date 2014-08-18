#include "CodeDoParser.hpp"

#include <iostream>

void CodeDoParser::readDeclare() {
}

void CodeDoParser::parseBooleanExpression() {
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
                parseBooleanExpression();
        }

        if(hasNext() && isEnd()) {
                next();
        }
        if(hasNext() && isSemicolon()) {
                next();
        }
}
