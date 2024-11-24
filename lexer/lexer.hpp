#include <iostream>
#include <vector>
#include <map>
#include <cctype>
#include <climits>

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
    bool checkInt(std::string integer);
public:
    Lexer(std::vector<std::string>* vecForTokens);
    ~Lexer();

    void analyze();
};