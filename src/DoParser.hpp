#ifndef DOPARSER_HPP
#define DOPARSER_HPP

#include "StatementParser.hpp"

#include <string>
#include <vector>

class DoParser: public StatementParser {
        private:
                std::vector<StatementParser> children;
        protected:
        public:
                DoParser(std::vector<std::string> * tokens, unsigned int * pos, unsigned int token_length) : StatementParser(tokens,pos,token_length) {};
                std::string language;
                void parse();
};

#endif
