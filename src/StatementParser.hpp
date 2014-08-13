#ifndef STATEMENTPARSER_HPP
#define STATEMENTPARSER_HPP

#include <string>
#include <vector>

class StatementParser {
        private:
                std::vector<StatementParser> children;
        protected:
                StatementParser();

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
                StatementParser(std::vector<std::string> * tokens, unsigned int * pos);
                void parse();
};

#endif
