#include "syntaxer.hpp"

Node::Node(NodeTypes nodeType, int tokenValue, Node* firstChildNode, Node* secondChildNode, Node* thirdChildNode){
    type = nodeType;
    value = tokenValue;

    if(firstChild == nullptr){
        numChildren = 0;
    }
    else if(secondChild == nullptr){
        firstChild = firstChildNode;
        numChildren = 1;
    }
    else if(thirdChild == nullptr){
        firstChild = firstChildNode;
        secondChild = secondChildNode;
        numChildren = 2;
    }
    else{
        firstChild = firstChildNode;
        secondChild = secondChildNode;
        thirdChild = thirdChildNode;
        numChildren = 3;
    }
}

Node::~Node(){
    delete firstChild;
    firstChild = nullptr;
    delete secondChild;
    secondChild = nullptr;
    delete thirdChild;
    thirdChild = nullptr;
}

void Node::addChild(Node* childNode){
    if(numChildren == 0){
        firstChild = childNode;
    }
    else if(numChildren == 1){
        secondChild = childNode;
    }
    else if(numChildren == 2){
        thirdChild = childNode;
    }
    else{
        return;
    }

    ++numChildren;
}

int Node::getNumChildren(){
    return numChildren;
}

Node* Node::getFirstChild(){
    if(firstChild != nullptr){
        return firstChild;
    }
    else{
        return nullptr;
    }
}

Node* Node::getSecondChild(){
    if(secondChild != nullptr){
        return secondChild;
    }
    else{
        return nullptr;
    }
}

Node* Node::getThirdChild(){
    if(thirdChild != nullptr){
        return thirdChild;
    }
    else{
        return nullptr;
    }
}

Syntaxer::Syntaxer(const std::vector<Token>* vecForTokens, std::vector<Node*>* syntaxTree){
    tokensVec = vecForTokens;
    tree = syntaxTree;
    currentBase = nullptr;
}

Syntaxer::~Syntaxer(){
    tokensVec = nullptr;
    tree = nullptr;
}


void Syntaxer::analyze(){
    
}

void Syntaxer::analyze_operation(){
    Node operation;
    Node buffer;
    bool operationUsage = false;
    bool bufferUsage = false;
    while((*tokensVec)[place].type != TokenTypes::SEMICOL){
        if((*tokensVec)[place].type == TokenTypes::FOR){}
        else if((*tokensVec)[place].type == TokenTypes::PLUS){
            if(!bufferUsage){
                throwError("");
                exit(1);
            }
            else{
                operationUsage = true;
                operation.type = NodeTypes::;
                operation.addChild(&buffer);
            }
        }
        else if((*tokensVec)[place].type == TokenTypes::MIN){
            if(!bufferUsage){
                throwError("");
                exit(1);
            }
            else{
                operationUsage = true;
                operation.type = NodeTypes::;
                operation.addChild(&buffer);
            }
        }
        else if((*tokensVec)[place].type == TokenTypes::MUL){
            if(!bufferUsage){
                throwError("");
                exit(1);
            }
            else{
                operationUsage = true;
                operation.type = NodeTypes::;
                operation.addChild(&buffer);
            }
        }
        else if((*tokensVec)[place].type == TokenTypes::DIV){
            if(!bufferUsage){
                throwError("");
                exit(1);
            }
            else{
                operationUsage = true;
                operation.type = NodeTypes::;
                operation.addChild(&buffer);
            }
        }
        else if((*tokensVec)[place].type == TokenTypes::MORE){
            if(!bufferUsage){
                throwError("");
                exit(1);
            }
            else{
                operationUsage = true;
                operation.type = NodeTypes::;
                operation.addChild(&buffer);
            }
        }
        else if((*tokensVec)[place].type == TokenTypes::LESS){
            if(!bufferUsage){
                throwError("");
                exit(1);
            }
            else{
                operationUsage = true;
                operation.type = NodeTypes::;
                operation.addChild(&buffer);
            }
        }
        else if((*tokensVec)[place].type == TokenTypes::EQ){
            if(!bufferUsage){
                throwError("");
                exit(1);
            }
            else{
                operationUsage = true;
                operation.type = NodeTypes::;
                operation.addChild(&buffer);
            }
        }
        else if((*tokensVec)[place].type == TokenTypes::NEQ){
            if(!bufferUsage){
                throwError("");
                exit(1);
            }
            else{
                operationUsage = true;
                operation.type = NodeTypes::;
                operation.addChild(&buffer);
            }
        }
        else if((*tokensVec)[place].type == TokenTypes::VAR){
            bufferUsage = true;
            buffer.type = NodeTypes::VAR;
            buffer.value = std::stoi((*tokensVec)[place].value);
        }
        else if((*tokensVec)[place].type == TokenTypes::INT){
            if(!operationUsage && !bufferUsage){
                throwError("unused constant");
            }
        }
        ++place;
    }
}
