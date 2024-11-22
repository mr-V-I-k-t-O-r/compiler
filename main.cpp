#include <iostream>

#include "lexer.hpp"
#include "parser.hpp"

int main(int argc, char* argv[]){
    if(argc < 2){
        std::cout << "укажите файл\n";
        return 0;
    }
    Parser pars;
    pars.parse(argv[1]);
    std::cout << "end of main\n";
    return 0;
}