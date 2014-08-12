#include "Configuration.hpp"
#include "Filereader.hpp"
#include "Parser.hpp"

#include <iostream>

int main(int argc, char* argv[]) {
        Configuration configuration;
        Filereader filereader;

        configuration.parseCommandline(argc,argv);
        std::vector<std::string> tokens = filereader.readFile(configuration.getInputfilename());
        Parser parser = Parser(tokens);
        parser.parse();
}
