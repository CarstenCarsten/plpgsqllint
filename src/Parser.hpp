#ifndef PARSER_HPP
#define PARSER_HPP

#include <string>
#include <vector>

class Parser {
        private:
                std::vector<Parser> children;
        protected:
                Parser();
                std::string token;  // TODO has to go, i need direkt acces to the tokens array

                bool isDo();
                bool isEndDollarQuote(std::string startDollarQuote);
                bool isEscapedSingleLineStringLiteral();
                bool isLanguage();
                bool isMultiLineStringLiteral();
                bool isNewline();
                bool isPlpgsql();
                bool isSingleLineStringLiteral();
                bool isStringLiteral();
                bool isVariableName();
                bool isWhitespace();

                bool hasNext();
                void next();
                void before();

                std::string readStringLiteral();
                std::string readDollarQuote();
                void skipWhitespacesAndNewlines();

                static std::vector<std::string> tokens; // TODO has to become ptr, and given to children
                static unsigned int position; // TODO has to become ptr, and given to children
        public:
                Parser(std::vector<std::string> tokensvector);
                void parse();
};

#endif
