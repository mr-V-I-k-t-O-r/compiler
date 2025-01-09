#ifndef LEXER
#define LEXER 

#include <iostream>
#include <vector>
#include <cctype>
#include <climits>
#include <vector>
#include <map>

enum class TokenTypes{
    TYPE, VAR, INT, EQ, NEQ, ASSIG,LPAR, RPAR, FOR, SEMICOL, MORE, LESS, NOT, PLUS, MIN, MUL, DIV, END, DO, DONE
};

class Token{
private:
public:
    std::string value;  
    TokenTypes type;
};

class Lexer{
private:
    std::vector<Token>* tokensVec;
    const std::vector<std::string>* termsVec;
    std::map<std::string, int> *vars;
    
    bool checkInt(std::string integer);
public:
    Lexer(const std::vector<std::string>* vecForTerms, std::vector<Token>* vecForTokens, std::map< std::string, int> *variables);
    ~Lexer();

    void analyze();
};
#endif