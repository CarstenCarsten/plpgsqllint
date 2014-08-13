#include "DoParser.hpp"

#include <iostream>

DoParser::DoParser() {
}

void DoParser::parse() {
        std::string token = tokens[position++];

        // skip possible whitespace and newlines. the do statement was read by the parent
        while(position < tokens.size() && (isWhitespace(token) || isNewline(token))) {
                token = tokens[position++];
        }

        // check for the optional language field
        if(position < tokens.size() && isLanguage(token)) {
                // a language has been set
                token = tokens[position++];

                // skip possible ws and nl
                while(position < tokens.size() && (isWhitespace(token) || isNewline(token))) {
                        token = tokens[position++];
                }
                
                // check the lang_name and skip to the code block
                if(position < tokens.size() && isPlpgsql(token)) {
                        token = tokens[position++];
                        language = "plpgsql";
                        while(position < tokens.size() && (isWhitespace(token) || isNewline(token))) {
                                token = tokens[position++];
                        }
                // it is allowed to write the language parameter as string literal
                } else if(position < tokens.size() && isStringLiteral(token)) {
                        token = consumeStringLiteral();
                        
                }
        }
        std::cout << tokens[position++];
}
