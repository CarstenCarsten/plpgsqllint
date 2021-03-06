#include "Logger.hpp"

#include <iostream>

void Logger::error(std::vector<std::string> * tokens, unsigned int * pos) {
        std::cout << "[ERROR  ] at [" << *pos << "]" << std::endl;
}

void Logger::warn(std::vector<std::string> * tokens, unsigned int * pos) {
        std::cout << "[WARN   ] at [" << *pos << "]" << std::endl;
}

void Logger::debug(std::vector<std::string> * tokens, unsigned int * pos) {
        std::cout << "[DEBUG  ] at [" << *pos << "]" << std::endl;
}
