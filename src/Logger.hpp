#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <string>
#include <vector>

class Logger {
        private:
        protected:
        public:
                void error(std::vector<std::string> * tokens, unsigned int * pos);
                void warn(std::vector<std::string> * tokens, unsigned int * pos);
                void debug(std::vector<std::string> * tokens, unsigned int * pos);
};

#endif
