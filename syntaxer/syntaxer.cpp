#include "syntaxer.hpp"

std::ostream& operator<< (std::ostream& os, const Node &node){
    switch(node.type){
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

Syntaxer::Syntaxer(const std::vector<Token>* vecForTokens, std::vector<Node*>* syntaxTree, std::map<std::string, int> *variables){
    tokensVec = vecForTokens;
    tree = syntaxTree;
    vars = variables;
    place = 0;
    currentBase = nullptr;
}

Syntaxer::~Syntaxer(){
    tokensVec = nullptr;
    tree = nullptr;
    vars = nullptr;
}


void Syntaxer::analyze(){
    while((*tokensVec)[place].type != TokenTypes::END){
        analyze_operation();
    }
}

void Syntaxer::analyze_operation(){
    Node *operation;
    Node *buffer;
    bool operationUsage = false;
    bool bufferUsage = false;
    while((*tokensVec)[place].type != TokenTypes::SEMICOL){
        operation = new Node;
        buffer = new Node;
        if((*tokensVec)[place].type == TokenTypes::FOR){}
        else if((*tokensVec)[place].type == TokenTypes::PLUS){
            if(!bufferUsage){
                // throwError("");
                exit(1);
            }
            else{
                operationUsage = true;
                operation->type = NodeTypes::ADD;
                operation->addChild(buffer);
                buffer = nullptr;
            }
        }
        else if((*tokensVec)[place].type == TokenTypes::MIN){
            if(!bufferUsage){
                // throwError("");
                exit(1);
            }
            else{
                operationUsage = true;
                operation->type = NodeTypes::SUB;
                operation->addChild(buffer);
                buffer = nullptr;
            }
        }
        else if((*tokensVec)[place].type == TokenTypes::MUL){
            if(!bufferUsage){
                // throwError("");
                exit(1);
            }
            else{
                operationUsage = true;
                operation->type = NodeTypes::MUL;
                operation->addChild(buffer);
                buffer = nullptr;
            }
        }
        else if((*tokensVec)[place].type == TokenTypes::DIV){
            if(!bufferUsage){
                // throwError("");
                exit(1);
            }
            else{
                operationUsage = true;
                operation->type = NodeTypes::DIV;
                operation->addChild(buffer);
                buffer = nullptr;
            }
        }
        else if((*tokensVec)[place].type == TokenTypes::MORE){
            if(!bufferUsage){
                // throwError("");
                exit(1);
            }
            else{
                operationUsage = true;
                operation->type = NodeTypes::MORE;
                operation->addChild(buffer);
                buffer = nullptr;
            }
        }
        else if((*tokensVec)[place].type == TokenTypes::LESS){
            if(!bufferUsage){
                // throwError("");
                exit(1);
            }
            else{
                operationUsage = true;
                operation->type = NodeTypes::LESS;
                operation->addChild(buffer);
                buffer = nullptr;
            }
        }
        else if((*tokensVec)[place].type == TokenTypes::EQ){
            if(!bufferUsage){
                // throwError("");
                exit(1);
            }
            else{
                operationUsage = true;
                operation->type = NodeTypes::EQ;
                operation->addChild(buffer);
                buffer = nullptr;
            }
        }
        else if((*tokensVec)[place].type == TokenTypes::NEQ){
            if(!bufferUsage){
                // throwError("");
                exit(1);
            }
            else{
                operationUsage = true;
                operation->type = NodeTypes::NEQ;
                operation->addChild(buffer);
                buffer = nullptr;
            }
        }
        else if((*tokensVec)[place].type == TokenTypes::ASSIG){
            if(!bufferUsage){
                // throwError("");
                exit(1);
            }
            else{
                operationUsage = true;
                operation->type = NodeTypes::SET;
                operation->addChild(buffer);
                buffer = nullptr;
            }
        }        
        else if((*tokensVec)[place].type == TokenTypes::VAR){
            buffer->type = NodeTypes::VAR;
            if(vars->find((*tokensVec)[place].value) == vars->end()){
                (*vars)[(*tokensVec)[place].value] = 0;
            }
            buffer->value = (*vars)[(*tokensVec)[place].value];
            if(operationUsage){
                operation->addChild(buffer);
                buffer = nullptr;
                bufferUsage = false;
                operationUsage = false;
            }
            else{
                bufferUsage = true;
            }
        }
        else if((*tokensVec)[place].type == TokenTypes::INT){
            if(!operationUsage){
                // throwError("unused constant");
                exit(1);
            }

            buffer->type = NodeTypes::VAR;
            buffer->value = std::stoi((*tokensVec)[place].value);
            operation->addChild(buffer);
            buffer = nullptr;
            bufferUsage = false;
            operationUsage = false;
        }
        ++place;
        delete buffer;
        delete operation;
    }
    ++place;

    for(auto i: *vars){
        std::cout << i.first << ' ' << i.second << '\n';
    }
}
