#ifndef DOPARSER_HPP
#define DOPARSER_HPP

#include "Parser.hpp"

#include <string>
#include <vector>

class DoParser: public Parser {
        private:
                std::vector<Parser> children;
        protected:
        public:
                DoParser(std::vector<std::string> * tokens, unsigned int * pos);
                std::string language;
                void parse();
};

#endif
