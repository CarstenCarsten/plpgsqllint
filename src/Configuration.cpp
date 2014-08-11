#include "Configuration.hpp"

#include <boost/program_options.hpp>

#include <cstdlib>
namespace po = boost::program_options;

Configuration::Configuration() {
}

void Configuration::parseCommandline(int argc, char* argv[]) {
        try {
                po::options_description desc("Allowed options");
                desc.add_options()
                ("help", "get help message")
                ("filename", po::value<std::string>(), "Filename of the input graph")
                ;

                po::variables_map vm;
                po::store(po::parse_command_line(argc, argv, desc), vm);
                po::notify(vm);

                if (vm.count("help")) {
                        std::cout << desc << "\n";
                        exit(0);
                }

                if (vm.count("filename")) {
                        std::cout << "Input filename is "
                        << vm["filename"].as<std::string>() << ".\n";
                } else {
                        std::cout << "input filename was not set.\n";
                }
        } catch(std::exception& e) {
                std::cerr << "error: " << e.what() << "\n";
                exit(1);
        } catch(...) {
                std::cerr << "Exception of unknown type!\n";
        }
}

std::string Configuration::getInputFile(std::string filename) {
   return "asdf";
}

