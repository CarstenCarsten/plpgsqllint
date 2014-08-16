#include "DoParser.hpp"

#include "CodeDoParser.hpp"

#include <iostream>

void DoParser::parse() {
        // skip the do word.
        next();

        // skip possible whitespace and newlines. the do statement was read by the next above
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
        }
        // now the codeblock MUST exist, and it must be a string literal
        if (hasNext() && isStringLiteral()) {
                // TODO
                // 1. get the string literal
                // 1a) if is singlelinestringlieral
                CodeDoParser codeDoParser(tokens,pos,12);
                codeDoParser.single_line_string_literal_level = single_line_string_literal_level + 1;
                // 2. find the end stringliteral, it is the same dollar quote that matches
                // 3. 
                // 4. create a new parser, set the end to the stringliteral end
                // 5. check for stringliteral, it should be now at position, if not, error
        } else {
                std::cout << "[ERROR  ] code block for do could not be found." << std::endl;
        }
      //  std::cout << tokens[position++];
}
