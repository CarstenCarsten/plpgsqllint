#include "DoParser.hpp"

#include <iostream>

DoParser::DoParser(std::vector<std::string> * tokens, unsigned int * pos) {
        this->tokens = tokens;
        this->pos = pos;
}

void DoParser::parse() {
        next();

        // skip possible whitespace and newlines. the do statement was read by the parent
        skipWhitespacesAndNewlines();

        // check for the optional language field
        if(hasNext() && isLanguage()) {
                // a language has been set
                next();

                // skip possible ws and nl
                skipWhitespacesAndNewlines();
                
                // check the lang_name and skip to the code block
                if(hasNext() && isPlpgsql()) {
                        next();
                        language = "plpgsql";
                        skipWhitespacesAndNewlines();
                // it is allowed to write the language parameter as string literal
                } else if(hasNext() && isStringLiteral()) {
                        std::cout << "[WARNING] string literal as language parameter" << std::endl;
                        language = readStringLiteral();
                        skipWhitespacesAndNewlines();
                } else {
                        std::cout << "[ERROR  ] language field was set, but no language parameter!" << std::endl;
                }
        } else if (hasNext() && isStringLiteral()) {
                // TODO
                // 1. get the string literal
                // 2. in case of single line convert '' to '
                // 3. create a new Parser Object with all the tokens in the middle
        }
      //  std::cout << tokens[position++];
}
