all:
	g++ -Wall src/plpgsqllint.cpp src/Configuration.cpp src/Filereader.cpp src/Parser.cpp src/DoParser.cpp -o plpgsqllint.app -lboost_program_options
