#ifndef WHEREPARSER_HPP
#define WHEREPARSER_HPP

#include "StatementParser.hpp"

#include <string>
#include <vector>

class WhereParser: public StatementParser {
        private:
                std::vector<StatementParser> children;
        protected:
        public:
                WhereParser(std::vector<std::string> * tokens, unsigned int * pos, unsigned int token_length) : StatementParser(tokens,pos,token_length) {};
                void parse();
};

#endif
