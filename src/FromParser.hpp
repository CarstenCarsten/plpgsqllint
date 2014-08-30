#ifndef FROMPARSER_HPP
#define FROMPARSER_HPP

#include "StatementParser.hpp"

#include <string>
#include <vector>

class FromParser: public StatementParser {
        private:
                std::vector<StatementParser> children;
        protected:
        public:
                FromParser(std::vector<std::string> * tokens, unsigned int * pos, unsigned int token_length) : StatementParser(tokens,pos,token_length) {};
                void parse();
};

#endif
