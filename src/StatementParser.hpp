#ifndef STATEMENTPARSER_HPP
#define STATEMENTPARSER_HPP

#include <string>
#include <vector>

class StatementParser {
        private:
                std::vector<StatementParser> children;
        protected:
                StatementParser();

                bool isAnd();
                bool isBegin();
                bool isClosingBracket();
                bool isClosingParentheses();
                bool isDeclare();
                bool isDo();
                bool isDot();
                bool isEnd();
                bool isEndDollarQuote(std::string startDollarQuote);
                bool isEquals();
                bool isEscapedSingleLineStringLiteral();
                bool isIf();
                bool isLanguage();
                bool isMultiLineStringLiteral();
                bool isNewline();
                bool isNot();
                bool isNull();
                bool isOpeningBracket();
                bool isOpeningParentheses();
                bool isOr();
                bool isPerform();
                bool isPlpgsql();
                bool isSemicolon();
                bool isSingleLineStringLiteral();
                bool isStatement();
                bool isStringLiteral();
                bool isThen();
                bool isVariableName();
                bool isWhitespace();

                bool hasNext();
                void next();
                void before();

                void skipEscapedSingleLineStringLiteral();
                void skipSingleLineStringLiteral();
                void skipWhitespaces();
                void skipWhitespacesAndNewlines();

                unsigned int findEndPositionOfMultiLineStringLiteral();
                unsigned int findEndPositionOfSingleLineStringLiteral();

                std::string readDollarQuote();
                std::string readStringLiteral();
                std::string readVariableName();

                std::vector<std::string> * tokens;
                unsigned int * pos;
                unsigned int token_length;
        public:
                StatementParser(std::vector<std::string> * tokens, unsigned int * pos, unsigned int token_length);
                unsigned int single_line_string_literal_level;
                void parse();
};

#endif
