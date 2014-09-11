#include "Logger.hpp"

#include <iostream>

void Logger::error(std::vector<std::string> * tokens, unsigned int * pos) {
        std::cout << "[ERROR  ]" << std::endl;
}

void Logger::warn(std::vector<std::string> * tokens, unsigned int * pos) {
        std::cout << "[ERROR  ]" << std::endl;
}

void Logger::debug(std::vector<std::string> * tokens, unsigned int * pos) {
        std::cout << "[ERROR  ]" << std::endl;
}
