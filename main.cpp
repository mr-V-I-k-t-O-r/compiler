#include <iostream>
#include <vector>

#include "lexer.hpp"
#include "parser.hpp"

int main(int argc, char* argv[]){
    if(argc < 2){
        std::cout << "укажите файл\n";
        return 0;
    }
    std::vector<std::string> termsVec;
    Parser pars(&termsVec);
    pars.parse(argv[1]);
    for(auto i : termsVec){
        std::cout << i << '\n';
    }
    std::vector<Token> tokensVec;
    Lexer lex(&termsVec, &tokensVec);
    lex.analyze();
    return 0;
}