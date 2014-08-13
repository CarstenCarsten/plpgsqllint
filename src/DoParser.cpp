#include "DoParser.hpp"

#include <iostream>

DoParser::DoParser() {
}

void DoParser::parse() {
        token = tokens[position++];

        // skip possible whitespace and newlines. the do statement was read by the parent
        skipWhitespacesAndNewlines();

        // check for the optional language field
        if(position < tokens.size() && isLanguage()) {
                // a language has been set
                token = tokens[position++];

                // skip possible ws and nl
                skipWhitespacesAndNewlines();
                
                // check the lang_name and skip to the code block
                if(position < tokens.size() && isPlpgsql()) {
                        token = tokens[position++];
                        language = "plpgsql";
                        skipWhitespacesAndNewlines();
                // it is allowed to write the language parameter as string literal
                } else if(position < tokens.size() && isStringLiteral()) {
                        std::cout << "[WARNING] string literal as language parameter" << std::endl;
                        consumeStringLiteral();
                        
                }
        }
        std::cout << tokens[position++];
}
