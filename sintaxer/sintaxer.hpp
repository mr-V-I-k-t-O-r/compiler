#include <iostream>

enum class NodesTypes{
    CONST, VAR, ADD, SUB, MUL, DIV, MORE, LESS, EQ, NEQ, NOT, FOR
};


class Node{
private:

    Node* oper1;
    Node* oper2;
    Node* oper3;
public:
    Node();
    ~Node();
};

class Sintaxer{
private:
public:
    Sintaxer();
    ~Sintaxer();
};