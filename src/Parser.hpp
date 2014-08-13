#ifndef PARSER_HPP
#define PARSER_HPP

#include <string>
#include <vector>

class Parser {
        private:
                std::vector<Parser> children;
        protected:
                Parser();

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

                std::vector<std::string> * tokens;
                unsigned int * pos;
        public:
                Parser(std::vector<std::string> * tokens, unsigned int * pos);
                void parse();
};

#endif
