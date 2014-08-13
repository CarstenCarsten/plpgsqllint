#ifndef PARSER_HPP
#define PARSER_HPP

#include <string>
#include <vector>

class Parser {
        private:
                std::vector<Parser> children;
        protected:
                bool isDo(std::string input);
                bool isLanguage(std::string input);
                bool isNewline(std::string input);
                bool isPlpgsql(std::string input);
                bool isStringLiteral(std::string input);
                bool isWhitespace(std::string input);

                std::string consumeStringLiteral();
                static std::vector<std::string> tokens;
                static unsigned int position;
        public:
                Parser();  // made public because of easier child-creation
                Parser(std::vector<std::string> tokensvector);
                void parse();
};

#endif
