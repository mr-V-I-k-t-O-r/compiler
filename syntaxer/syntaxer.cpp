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

void printNodesInTree(Node *node, int dot){
    std::cout << (*node) << '\t' << dot << '\n';
    switch(node->getNumChildren()){
        case 4:{
            printNodesInTree(node->getFourthChild(), dot + 1);
        }
        case 3:{
            printNodesInTree(node->getThirdChild(), dot + 1);
        }
        case 2:{
            printNodesInTree(node->getSecondChild(), dot + 1);
        }
        case 1:{
            printNodesInTree(node->getFirstChild(), dot + 1);
        }
        case 0:{
            break;
        }
    }
}

Node::Node(NodeTypes nodeType, int tokenValue){
    type = nodeType;
    value = tokenValue;

    numChildren = 0;
    firstChild = nullptr;
    secondChild = nullptr;
    thirdChild = nullptr;
    fourthChild = nullptr;

    next = nullptr;
}

Node::~Node(){
    if(firstChild != nullptr){
        delete firstChild;
        firstChild = nullptr;
    }
    if(secondChild != nullptr){
        delete secondChild;
        secondChild = nullptr;
    }
    if(thirdChild != nullptr){
        delete thirdChild;
        thirdChild = nullptr;
    }
    if(fourthChild != nullptr){
        delete fourthChild;
        fourthChild = nullptr;
    }

    if(next != nullptr){
        delete next;
        next = nullptr;
    }
}

void Node::addChild(Node* childNode){
    if(childNode == nullptr){
        return;
    }
    if(numChildren == 0){
        firstChild = childNode;
    }
    else if(numChildren == 1){
        secondChild = childNode;
    }
    else if(numChildren == 2){
        thirdChild = childNode;
    }
    else if(numChildren == 3){
        fourthChild = childNode;
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
    return firstChild;
}

Node* Node::getSecondChild(){
    return secondChild;
}

Node* Node::getThirdChild(){
    return thirdChild;
}

Node* Node::getFourthChild(){
    return fourthChild;
}

Node* Node::getNext(){
    return next;
}

Syntaxer::Syntaxer(const std::vector<Token>* vecForTokens, std::vector<Node*>* syntaxTree, std::map<std::string, int> *variables){
    tokensVec = vecForTokens;
    tree = syntaxTree;
    vars = variables;
    place = 0;
    currentBase = nullptr;
    currentEnd = nullptr;
}

Syntaxer::~Syntaxer(){
    tokensVec = nullptr;
    tree = nullptr;
    vars = nullptr;
}

void Syntaxer::analyze(){
    currentBase = new Node(NodeTypes::START);
    currentEnd = currentBase;
    while((*tokensVec)[place].type != TokenTypes::END){
        if(place >= tokensVec->size()){
            break;
        }
        analyzeOperation();
    }
    delete currentBase;
}

void Syntaxer::analyzeOperation(){
    Node *operation;
    Node *buffer;
    bool operationUsage = false;
    bool bufferUsage = false;
    while((*tokensVec)[place].type != TokenTypes::SEMICOL && (*tokensVec)[place].type != TokenTypes::END){
        if((*tokensVec)[place].type == TokenTypes::LPAR){
            ++place;
            analyzePars();
        }
        else if((*tokensVec)[place].type == TokenTypes::LBRA){
            ++place;
            analyzeBras();
            break;
        } 
        else if((*tokensVec)[place].type == TokenTypes::FOR){
            analyzeFor();
            break;
        }
        else if((*tokensVec)[place].type == TokenTypes::VAR){
            if(!bufferUsage){
                buffer = new Node(NodeTypes::VAR);
                bufferUsage = true;
            }
            else{
                std::cout << "error in using buffers for var\n";
            }
        }
        else if((*tokensVec)[place].type == TokenTypes::INT){
            if(!bufferUsage){
                buffer = new Node(NodeTypes::CONST);
                buffer->value = std::stoi((*tokensVec)[place].value);
                bufferUsage = true;
            }
            else{
                std::cout << "error in using buffers for int\n";
            }
        }
        else if((*tokensVec)[place].type == TokenTypes::ASSIG){
            if(buffer->type != NodeTypes::VAR){
                exit(1);
            }
            operation = new Node(NodeTypes::SET);
            operation->addChild(buffer);
            currentEnd->addChild(operation);
            currentEnd = operation;
            bufferUsage = false;
            operation = nullptr;
            buffer = nullptr;
        }
        else if((*tokensVec)[place].type == TokenTypes::PLUS){
            if(!bufferUsage){
                // throwError("");
                exit(1);
            }
            operation = new Node(NodeTypes::ADD);
            operation->addChild(buffer);
            currentEnd->addChild(operation);
            currentEnd = operation;
            
            bufferUsage = false;
            buffer = nullptr;
            operation = nullptr;
        }
        else if((*tokensVec)[place].type == TokenTypes::MIN){
            if(!bufferUsage){
                // throwError("");
                exit(1);
            }
            operation = new Node(NodeTypes::SUB);
            operation->addChild(buffer);
            currentEnd->addChild(operation);
            currentEnd = operation;
            
            bufferUsage = false;
            buffer = nullptr;
            operation = nullptr;
        }
        else if((*tokensVec)[place].type == TokenTypes::MUL){
            if(!bufferUsage){
                // throwError("");
                exit(1);
            }
            operation = new Node(NodeTypes::MUL);
            operation->addChild(buffer);
            currentEnd->addChild(operation);
            currentEnd = operation;
            
            bufferUsage = false;
            buffer = nullptr;
            operation = nullptr;
        }
        else if((*tokensVec)[place].type == TokenTypes::DIV){
            if(!bufferUsage){
                // throwError("");
                exit(1);
            }
            operation = new Node(NodeTypes::DIV);
            operation->addChild(buffer);
            currentEnd->addChild(operation);
            currentEnd = operation;
            
            bufferUsage = false;
            buffer = nullptr;
            operation = nullptr;
        }
        else if((*tokensVec)[place].type == TokenTypes::MORE){
            if(!bufferUsage){
                // throwError("");
                exit(1);
            }
            operation = new Node(NodeTypes::MORE);
            operation->addChild(buffer);
            currentEnd->addChild(operation);
            currentEnd = operation;
            
            bufferUsage = false;
            buffer = nullptr;
            operation = nullptr;
        }
        else if((*tokensVec)[place].type == TokenTypes::LESS){
            if(!bufferUsage){
                // throwError("");
                exit(1);
            }
            operation = new Node(NodeTypes::LESS);
            operation->addChild(buffer);
            currentEnd->addChild(operation);
            currentEnd = operation;
            
            bufferUsage = false;
            buffer = nullptr;
            operation = nullptr;
        }
        else if((*tokensVec)[place].type == TokenTypes::EQ){
            if(!bufferUsage){
                // throwError("");
                exit(1);
            }
            operation = new Node(NodeTypes::EQ);
            operation->addChild(buffer);
            currentEnd->addChild(operation);
            currentEnd = operation;
            
            bufferUsage = false;
            buffer = nullptr;
            operation = nullptr;
        }
        else if((*tokensVec)[place].type == TokenTypes::NEQ){
            if(!bufferUsage){
                // throwError("");
                exit(1);
            }
            operation = new Node(NodeTypes::NEQ);
            operation->addChild(buffer);
            currentEnd->addChild(operation);
            currentEnd = operation;
            
            bufferUsage = false;
            buffer = nullptr;
            operation = nullptr;
        }     
        
        ++place;
    }
    ++place;

}

void Syntaxer::analyzePars(){
    while((*tokensVec)[place].type != TokenTypes::RPAR){
        ++place;
    }
}

void Syntaxer::analyzeBras(){
    while((*tokensVec)[place].type != TokenTypes::RBRA){
        analyzeOperation();
    }
}

void Syntaxer::analyzeFor(){
    Node* forNode = new Node(NodeTypes::FOR);

    currentEnd->addChild(forNode);
    currentEnd = forNode;

    ++place;
    if((*tokensVec)[place].type != TokenTypes::LPAR){
        exit(1);
    }
    bool init = false;
    bool cond = false;
    Node *buffer = nullptr;
    Node *operation = nullptr;
    bool bufferUsage = false;
    bool operationUsage = false;
    while((*tokensVec)[place].type != TokenTypes::RPAR){
        if((*tokensVec)[place].type == TokenTypes::SEMICOL){
            if(bufferUsage){
                currentEnd->addChild(buffer);
                buffer = nullptr;
                bufferUsage = false;
            }
            currentEnd = forNode;
        }
        else if((*tokensVec)[place].type == TokenTypes::VAR){
            if(!bufferUsage){
                buffer = new Node(NodeTypes::VAR);
                bufferUsage = true;
            }
            else{
                std::cout << "error in using buffers for var\n";
            }
        }
        else if((*tokensVec)[place].type == TokenTypes::INT){
            if(!bufferUsage){
                buffer = new Node(NodeTypes::CONST);
                buffer->value = std::stoi((*tokensVec)[place].value);
                bufferUsage = true;
            }
            else{
                std::cout << "error in using buffers for int\n";
            }
        }
        else if((*tokensVec)[place].type == TokenTypes::ASSIG){
            if(buffer->type != NodeTypes::VAR){
                exit(1);
            }
            operation = new Node(NodeTypes::SET);
            operation->addChild(buffer);
            currentEnd->addChild(operation);
            currentEnd = operation;
            bufferUsage = false;
            operation = nullptr;
            buffer = nullptr;
        }
        else if((*tokensVec)[place].type == TokenTypes::PLUS){
            if(!bufferUsage){
                // throwError("");
                exit(1);
            }
            operation = new Node(NodeTypes::ADD);
            operation->addChild(buffer);
            currentEnd->addChild(operation);
            currentEnd = operation;
            
            bufferUsage = false;
            buffer = nullptr;
            operation = nullptr;
        }
        else if((*tokensVec)[place].type == TokenTypes::MIN){
            if(!bufferUsage){
                // throwError("");
                exit(1);
            }
            operation = new Node(NodeTypes::SUB);
            operation->addChild(buffer);
            currentEnd->addChild(operation);
            currentEnd = operation;
            
            bufferUsage = false;
            buffer = nullptr;
            operation = nullptr;
        }
        else if((*tokensVec)[place].type == TokenTypes::MUL){
            if(!bufferUsage){
                // throwError("");
                exit(1);
            }
            operation = new Node(NodeTypes::MUL);
            operation->addChild(buffer);
            currentEnd->addChild(operation);
            currentEnd = operation;
            
            bufferUsage = false;
            buffer = nullptr;
            operation = nullptr;
        }
        else if((*tokensVec)[place].type == TokenTypes::DIV){
            if(!bufferUsage){
                // throwError("");
                exit(1);
            }
            operation = new Node(NodeTypes::DIV);
            operation->addChild(buffer);
            currentEnd->addChild(operation);
            currentEnd = operation;
            
            bufferUsage = false;
            buffer = nullptr;
            operation = nullptr;
        }
        else if((*tokensVec)[place].type == TokenTypes::MORE){
            if(!bufferUsage){
                // throwError("");
                exit(1);
            }
            operation = new Node(NodeTypes::MORE);
            operation->addChild(buffer);
            currentEnd->addChild(operation);
            currentEnd = operation;
            
            bufferUsage = false;
            buffer = nullptr;
            operation = nullptr;
        }
        else if((*tokensVec)[place].type == TokenTypes::LESS){
            if(!bufferUsage){
                // throwError("");
                exit(1);
            }
            operation = new Node(NodeTypes::LESS);
            operation->addChild(buffer);
            currentEnd->addChild(operation);
            currentEnd = operation;
            
            bufferUsage = false;
            buffer = nullptr;
            operation = nullptr;
        }
        else if((*tokensVec)[place].type == TokenTypes::EQ){
            if(!bufferUsage){
                // throwError("");
                exit(1);
            }
            operation = new Node(NodeTypes::EQ);
            operation->addChild(buffer);
            currentEnd->addChild(operation);
            currentEnd = operation;
            
            bufferUsage = false;
            buffer = nullptr;
            operation = nullptr;
        }
        else if((*tokensVec)[place].type == TokenTypes::NEQ){
            if(!bufferUsage){
                // throwError("");
                exit(1);
            }
            operation = new Node(NodeTypes::NEQ);
            operation->addChild(buffer);
            currentEnd->addChild(operation);
            currentEnd = operation;
            
            bufferUsage = false;
            buffer = nullptr;
            operation = nullptr;
        }     
        ++place;
    }

    analyzeOperation();

    forNode = nullptr;
    if(bufferUsage){
        currentEnd->addChild(buffer);
        buffer = nullptr;
        bufferUsage = false;
    }

}