all:
	g++ -Wall src/plpgsqllint.cpp src/Configuration.cpp src/Logger.cpp src/Filereader.cpp src/StatementParser.cpp src/DoParser.cpp src/CodeDoParser.cpp src/PerformParser.cpp src/FromParser.cpp src/WhereParser.cpp src/InsertParser.cpp -o plpgsqllint.app -lboost_program_options
