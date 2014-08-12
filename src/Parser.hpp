#ifndef PARSER_HPP
#define PARSER_HPP

#include <string>
#include <vector>

class Parser {
        private:
                std::vector<Parser> children;
        protected:
                bool isWhitespace(std::string input);
                bool isDo(std::string input);
                static std::vector<std::string> tokens;
                static unsigned int position;
        public:
                Parser();  // made public because of easier child-creation
                Parser(std::vector<std::string> tokensvector);
                void parse();
};

#endif
