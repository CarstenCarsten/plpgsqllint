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
                DoParser(std::vector<std::string> * tokens, unsigned int * pos);
                std::string language;
                void parse();
};

#endif
