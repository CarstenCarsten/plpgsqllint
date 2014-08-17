#include "PerformParser.hpp"

#include <iostream>

void PerformParser::parse() {
        if(hasNext() && isPerform()) {
                next();
        } else {
                std::cout << "[ERROR  ] expected PERFORM statement" << std::endl;
        }
        skipWhitespacesAndNewlines();
        
        if(hasNext() && isNull()) {
                next();
        }
}
