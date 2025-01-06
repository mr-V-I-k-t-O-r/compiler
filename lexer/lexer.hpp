#ifndef LEXER
#define LEXER 

#include <iostream>
#include <vector>
#include <cctype>
#include <climits>
#include <vector>

enum class TokenTypes{
    TYPE, VAR, INT, EQ, NEQ, ASSIG, LBRA, RBRA, LPAR, RPAR, FOR, SEMICOL, MORE, LESS, NOT, PLUS, MIN, MUL, DIV, END
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
    
    bool checkInt(std::string integer);
public:
    Lexer(const std::vector<std::string>* vecForTerms, std::vector<Token>* vecForTokens);
    ~Lexer();

    void analyze();
};
#endif