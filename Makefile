all:
	g++ -Wall src/plpgsqllint.cpp src/Configuration.cpp src/Filereader.cpp src/StatementParser.cpp src/DoParser.cpp src/CodeDoParser.cpp -o plpgsqllint.app -lboost_program_options
