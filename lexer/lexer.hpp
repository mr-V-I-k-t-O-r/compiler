#include <iostream>
#include <vector>
#include <map>

enum class TokenTypes{
    VAR, INT, EQ, NEQ, ASSIG, LBRA, RBRA, LPAR, RPAR, FOR, SEMICOL, MORE, LESS, NOT, PLUS, MIN, MUL, DIV
};

class Token{
private:
public:
    std::string value;  
    TokenTypes type;
};

class Lexer{
private:
    std::vector<std::string>* tokensVec;
public:
    Lexer(std::vector<std::string>* vecForTokens);
    ~Lexer();

    void analyze();
};