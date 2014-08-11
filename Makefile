all:
	g++ src/plpgsqllint.cpp src/Configuration.cpp -o plpgsqllint.app -lboost_program_options
