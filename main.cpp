#include <iostream>

std::string version = "0.0.1";

int main(int argc, char* argv[]){
	if(argc < 1){
		return 0;
	}
	if(argv[1] == "-v" or argv[1] == "--version"){
		std::cout << version << '\n';
		return 0;
	}
	if(argv[1] == "-h" or argv[1] == "--help"){
		std::cout << "" << '\n';
		return 0;
	}

	Analizer analyzer;
	Creator creator;

	for(int i = 1; i < argc; ++i){
		/* output */
		if(argv[i] == "-o"){
			if(i == argc +1){
				// TODO err output file name
				return 1;
			}
			std::string output = argv[++i];
		}
		/* input */
		else{
			analyzer.analyze(argv[i]);

		}

	}
	return 0;
}
