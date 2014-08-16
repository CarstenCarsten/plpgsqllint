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
                        std::cout << "[DEBUG  ] read Language {" << language << "}" << std::endl;
                        skipWhitespacesAndNewlines();
                } else {
                        std::cout << "[ERROR  ] language field was set, but no language parameter!" << std::endl;
                }
        }
        // now there could be spaces or newlines before the codeblock
        skipWhitespacesAndNewlines();
        std::cout << "[DEBUG  ] now code block {" << (*tokens)[*pos] << "}" << std::endl;
 
        // now the codeblock MUST exist, and it must be a string literal
        if (hasNext() && isStringLiteral()) {
                if(isSingleLineStringLiteral()) {
                        //find end of singlelinestringliteral
                        unsigned int endpos = findEndPositionOfSingleLineStringLiteral();
                        // skip the current singlelineStringliteral, so that the code can be analysed
                        skipSingleLineStringLiteral();
                        // create the code block parser, and read the code
                        CodeDoParser codeDoParser(tokens,pos,endpos);
                        codeDoParser.single_line_string_literal_level = single_line_string_literal_level + 1;
                        codeDoParser.parse();
                        // after the parsing we should be at the endpos
                        if(*pos != endpos) {
                                std::cout << "[DEBUG  ] pos{" << *pos << "} endpos{" << endpos << "}" << std::endl;
                        }
                        if(!hasNext()) {
                                std::cout << "[ERROR  ] expected end of string literal, but nothing left to parse" << std::endl;
                        }
                        if(!isSingleLineStringLiteral()) {
                                std::cout << "[ERROR  ] expected end of stringliteral" << std::endl;
                        }
                        skipSingleLineStringLiteral();
                } else if (isMultiLineStringLiteral()) {
                        unsigned int endpos = findEndPositionOfMultiLineStringLiteral();
                        std::string beginningDollarQuote = readDollarQuote();
                        CodeDoParser codeDoParser(tokens, pos, endpos);
                        codeDoParser.parse();
                        if(*pos != endpos) {
                                std::cout << "[DEBUG  ] pos{" << *pos << "} endpos{" << endpos << "} in multilineStringLiteral" << std::endl;
                        }
                        if(!hasNext()) {
                                std::cout << "[ERROR  ] expected end of dollar quote, but nothing left to parse" << std::endl;
                        }
                        if(!isMultiLineStringLiteral()) {
                                std::cout << "[ERROR  ] expected closing multilineStringLiteral" << std::endl;
                        }
                        std::string endingDollarQuote = readDollarQuote();
                        if(beginningDollarQuote.compare(endingDollarQuote)) {
                                std::cout << "[ERROR  ] dollar quotes were not identical start{" << beginningDollarQuote << "} end{" << endingDollarQuote << "}" << std::endl;
                        }
                }
        } else {
                std::cout << "[ERROR  ] code block for do could not be found. position {" << (*tokens)[*pos] << "}" << std::endl;
        }
}
