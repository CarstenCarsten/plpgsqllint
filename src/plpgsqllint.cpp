#include "Configuration.hpp"
#include "Filereader.hpp"
#include "Parser.hpp"

#include <iostream>

int main(int argc, char* argv[]) {
        Configuration configuration;
        Filereader filereader;

        configuration.parseCommandline(argc,argv);
        std::vector<std::string> tokens = filereader.readFile(configuration.getInputfilename());
        unsigned int position = 0;
        Parser parser = Parser(&tokens,&position);
        parser.parse();
}
