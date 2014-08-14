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
                // TODO use pass-through constructor here
                DoParser(std::vector<std::string> * tokens, unsigned int * pos, unsigned int * token_length);
                std::string language;
                void parse();
};

#endif
