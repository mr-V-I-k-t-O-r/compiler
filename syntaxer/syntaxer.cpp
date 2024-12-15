#include "syntaxer.hpp"

Node::Node(){
    
}

Node::Node(NodesTypes type, int tokenValue, Node* firstChild, Node* secondChild, Node* thirdChild){

}
Node::~Node(){

}


void Node::addChild(Node* childNode){

}


int Node::getNumChildren(){

}


Node* Node::getFirstChild(){

}

Node* Node::getSecondChild(){

}

Node* Node::getThirdChild(){

}


Tree::Tree(){

}

Tree::~Tree(){

}

Syntaxer::Syntaxer(const std::vector<Token>* vecForTokens, Tree* syntaxTree){
    tokensVec = vecForTokens;
    tree = syntaxTree;
}

Syntaxer::~Syntaxer(){
    tokensVec = nullptr;
    tree = nullptr;
}


void Syntaxer::analyze(){
    for(auto i : *tokensVec){
        if(i.type == TokenTypes::SEMICOL){
            continue;
        }
        Node node;
    }
}

