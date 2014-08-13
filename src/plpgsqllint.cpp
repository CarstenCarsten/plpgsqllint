#include "Configuration.hpp"
#include "Filereader.hpp"
#include "StatementParser.hpp"

#include <iostream>

int main(int argc, char* argv[]) {
        Configuration configuration;
        Filereader filereader;

        configuration.parseCommandline(argc,argv);
        std::vector<std::string> tokens = filereader.readFile(configuration.getInputfilename());
        unsigned int position = 0;
        StatementParser statementParser = StatementParser(&tokens,&position);
        statementParser.parse();
}
