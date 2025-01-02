#ifndef SYNTAXER
#define SYNTAXER

#include <iostream>
#include <vector>

#include "lexer.hpp"

enum class NodeTypes{
    CONST, VAR, ADD, SUB, MUL, DIV, MORE, LESS, EQ, NEQ, NOT, FOR, SET, EMPTY
};


class Node{
private:
    Node* firstChild;
    Node* secondChild;
    Node* thirdChild;

    int numChildren;


public:
    int value;
    NodeTypes type;

    // friend std::ostream& operator << (std::ostream& os, const Node &node);
    Node(NodeTypes type = NodeTypes::EMPTY, int tokenValue = 0, Node* firstChild = nullptr, Node* secondChild = nullptr, Node* thirdChild = nullptr);
    ~Node();

    void addChild(Node* childNode);

    int getNumChildren();

    Node* getFirstChild();
    Node* getSecondChild();
    Node* getThirdChild();
};

class Syntaxer{
private:

    const std::vector<Token>* tokensVec;
    std::vector<Node*>* tree;

    int place;

    Node* currentBase;
public:
    Syntaxer(const std::vector<Token>* vecForTokens, std::vector<Node*>* syntaxTree);
    ~Syntaxer();

    void analyze();
    void analyze_operation();
};

#endif