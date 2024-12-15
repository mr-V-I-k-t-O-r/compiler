#include <iostream>
#include <vector>

#include "lexer.hpp"

enum class NodesTypes{
    CONST, VAR, ADD, SUB, MUL, DIV, MORE, LESS, EQ, NEQ, NOT, FOR, SET
};


class Node{
private:
    Node* oper1;
    Node* oper2;
    Node* oper3;

    int numChildren;

    int value;

public:
    NodesTypes nodeType;

    Node();
    Node(NodesTypes type, int tokenValue, Node* firstChild = nullptr, Node* secondChild = nullptr, Node* thirdChild = nullptr);
    ~Node();

    void addChild(Node* childNode);

    int getNumChildren();

    Node* getFirstChild();
    Node* getSecondChild();
    Node* getThirdChild();
};

class Tree{
private:
public:
    Tree();
    ~Tree();
};

class Syntaxer{
private:
    const std::vector<Token>* tokensVec;
    Tree* tree;
public:
    Syntaxer(const std::vector<Token>* vecForTokens, Tree* syntaxTree);
    ~Syntaxer();

    void analyze();
};