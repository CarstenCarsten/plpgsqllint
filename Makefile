all:
	g++ src/plpgsqllint.cpp src/Configuration.cpp src/Filereader.cpp -o plpgsqllint.app -lboost_program_options
