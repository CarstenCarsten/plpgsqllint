#include "Configuration.hpp"
#include "Filereader.hpp"

#include <iostream>

int main(int argc, char* argv[]) {
        Configuration configuration;
        configuration.parseCommandline(argc,argv);
        std::cout << configuration.getInputfilename();
        Filereader filereader;
        filereader.readFile(configuration.getInputfilename());
}
