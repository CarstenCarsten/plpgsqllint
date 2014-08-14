#ifndef CODEDOPARSER_HPP
#define CODEDOPARSER_HPP

#include "StatementParser.hpp"

#include <string>
#include <vector>

class CodeDoParser: public StatementParser {
        private:
                std::vector<StatementParser> children;
        protected:
        public:
                CodeDoParser(std::vector<std::string> * tokens, unsigned int * pos, unsigned int token_length) : StatementParser(tokens,pos,token_length) {};
                std::string language;
                void parse();
};

#endif
