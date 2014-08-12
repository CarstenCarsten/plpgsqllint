#ifndef DOPARSER_HPP
#define DOPARSER_HPP

#include "Parser.hpp"

#include <vector>

class DoParser: public Parser {
        private:
                std::vector<Parser> children;
        protected:
        public:
                DoParser();
                void parse();
};

#endif
