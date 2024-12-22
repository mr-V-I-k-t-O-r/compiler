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

    std::ostream& operator << (std::ostream& os){
        switch(type){
            case NodeTypes::CONST:{
                os << "CONST";
                break;
            }
            case NodeTypes::VAR:{
                os << "VAR";
                break;
            }
            case NodeTypes::ADD:{
                os << "ADD";
                break;
            }
            case NodeTypes::SUB:{
                os << "SUB";
                break;
            }
            case NodeTypes::MUL:{
                os << "MUL";
                break;
            }
            case NodeTypes::DIV:{
                os << "DIV";
                break;
            }
            case NodeTypes::MORE:{
                os << "MORE";
                break;
            }
            case NodeTypes::LESS:{
                os << "LESS";
                break;
            }
            case NodeTypes::EQ:{
                os << "EQ";
                break;
            }
            case NodeTypes::NEQ:{
                os << "NEQ";
                break;
            }
            case NodeTypes::NOT:{
                os << "NOT";
                break;
            }
            case NodeTypes::FOR:{
                os << "FOR";
                break;
            }
            case NodeTypes::SET:{
                os << "SET";
                break;
            }
            case NodeTypes::EMPTY:{
                os << "EMPTY";
                break;
            }
        }
        return os;
    }

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