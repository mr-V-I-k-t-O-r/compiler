#include <iostream>
#include <vector>
#include <map>

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
    std::map<std::string, int> variables;
    Lexer lex(&termsVec, &tokensVec, &variables);
    lex.analyze();
    std::cout << "-----LEXER-----\n";

    std::cout << "-----SYNTAXER-----\n";
    std::vector<Node*> syntaxTree;
    Syntaxer syntax(&tokensVec, &syntaxTree, &variables);
    syntax.analyze();
    std::cout << "-----SYNTAXER-----\n";


    return 0;
}