#ifndef INSERTPARSER_HPP
#define INSERTPARSER_HPP

#include "StatementParser.hpp"

#include <string>
#include <vector>

class InsertParser: public StatementParser {
        private:
                std::vector<StatementParser> children;
        protected:
        public:
                InsertParser(std::vector<std::string> * tokens, unsigned int * pos, unsigned int token_length) : StatementParser(tokens,pos,token_length) {};
                void parse();
};

#endif
