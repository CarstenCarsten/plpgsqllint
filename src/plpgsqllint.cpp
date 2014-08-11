#include "Configuration.hpp"

#include <iostream>

using namespace std;

int main(int argc, char* argv[]) {
        Configuration configuration;
        configuration.parseCommandline(argc,argv);
        cout << configuration.getInputFile("");
}
