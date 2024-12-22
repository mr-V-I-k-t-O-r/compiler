#include <iostream>
#include <vector>
#include <vector>

#include "parser.hpp"
#include "lexer.hpp"
#include "syntaxer.hpp"

int main(int argc, char* argv[]){
    if(argc < 2){
        std::cout << "укажите файл\n";
        return 0;
    }

    std::cout << "-----PARSER-----\n";
    std::vector<std::string> termsVec;
    Parser pars(&termsVec);
    pars.parse(argv[1]);
    for(auto i : termsVec){
        std::cout << i << '\n';
    }
    std::cout << "-----PARSER-----\n";

    std::cout << "-----LEXER-----\n";
    std::vector<Token> tokensVec;
    Lexer lex(&termsVec, &tokensVec);
    lex.analyze();
    std::cout << "-----LEXER-----\n";

    std::cout << "-----SYNTAXER-----\n";
    std::vector<Node*> syntaxTree;
    Syntaxer syntax(&tokensVec, &syntaxTree);
    std::cout << "-----SYNTAXER-----\n";


    return 0;
}