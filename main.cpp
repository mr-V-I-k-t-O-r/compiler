#include <iostream>
#include <vector>

#include "lexer.hpp"
#include "parser.hpp"

int main(int argc, char* argv[]){
    if(argc < 2){
        std::cout << "укажите файл\n";
        return 0;
    }
    std::vector<std::string> tokensVec;
    Parser pars(&tokensVec);
    pars.parse(argv[1]);
    return 0;
}