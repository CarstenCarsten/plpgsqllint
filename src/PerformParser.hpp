#ifndef PERFORMPARSER_HPP
#define PERFORMPARSER_HPP

#include "StatementParser.hpp"

#include <string>
#include <vector>

class PerformParser: public StatementParser {
        private:
                std::vector<StatementParser> children;
        protected:
        public:
                PerformParser(std::vector<std::string> * tokens, unsigned int * pos, unsigned int token_length) : StatementParser(tokens,pos,token_length) {};
                void parse();
};

#endif
