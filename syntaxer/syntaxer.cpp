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
    if(firstChild != nullptr){
        delete firstChild;
        firstChild = nullptr;
    }
    if(firstChild != nullptr){
        delete secondChild;
        secondChild = nullptr;
    }
    if(firstChild != nullptr){
        delete thirdChild;
        thirdChild = nullptr;
    }
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
    currentEnd = nullptr;
}

Syntaxer::~Syntaxer(){
    tokensVec = nullptr;
    tree = nullptr;
    vars = nullptr;
}


void Syntaxer::analyze(){
    while((*tokensVec)[place].type != TokenTypes::END){
        if(place >= tokensVec->size()){
            break;
        }
        analyzeOperation();
    }


    for(auto i: *vars){
        std::cout << i.first << ' ' << i.second << '\n';
    }
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
        } 
        operation = new Node;
        buffer = new Node;
        if((*tokensVec)[place].type == TokenTypes::FOR){
            analyzeFor();
        }
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
            if(!bufferUsage){
                buffer = new Node;
                buffer->type = NodeTypes::VAR;
                bufferUsage = true;
                if(operationUsage){
                    operation->addChild(buffer);
                    buffer = nullptr;
                    bufferUsage = false;
                }
            }
        }
        else if((*tokensVec)[place].type == TokenTypes::INT){
            if(!bufferUsage){
                buffer = new Node;
                buffer->type = NodeTypes::CONST;
                buffer->value = std::stoi((*tokensVec)[place].value);
                if(operationUsage){
                    std::cout << operation << '\n';
                    operation->addChild(buffer);
                    buffer = nullptr;
                    bufferUsage = false;
                    operationUsage = false;
                }
            }
        }
        else if((*tokensVec)[place].type == TokenTypes::TYPE){
        }
        else if((*tokensVec)[place].type == TokenTypes::RBRA){
        }
        else if((*tokensVec)[place].type == TokenTypes::RPAR){
        }
        else if((*tokensVec)[place].type == TokenTypes::NOT){
        }
        ++place;
        delete buffer;
        delete operation;
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
    std::cout << "start for\n";

    Node* forNode = new Node;
    forNode->type = NodeTypes::FOR;

    Node* initial = nullptr;
    Node* condition = nullptr;
    Node* change = nullptr;

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
        std::cout << "while iteration\n";
        if((*tokensVec)[place].type == TokenTypes::SEMICOL){
            std::cout << ";\n";
            if(!init){
                initial = operation;
                operation = nullptr;
                operationUsage = false;
            }
            else if(!cond){
                condition = operation;
                operation = nullptr;
                operationUsage = false;
            }
            if(bufferUsage){
                currentEnd->addChild(buffer);
            }
        }
        else if((*tokensVec)[place].type == TokenTypes::VAR){
            if(!bufferUsage){
                buffer = new Node;
                buffer->type = NodeTypes::VAR;
                bufferUsage = true;
                if(operationUsage){
                    operation->addChild(buffer);
                    buffer = nullptr;
                    bufferUsage = false;
                }
            }
        }
        else if((*tokensVec)[place].type == TokenTypes::INT){
            if(!operationUsage){
                // throwError("unused constant");
                if(init && !cond){
                    if(std::stoi((*tokensVec)[place].value) == 0){
                        // 0 iterations
                    }
                    else{
                        // infinity iterations
                    }
                }
            }
            else{
                if(!bufferUsage){
                    buffer = new Node;
                    buffer->type = NodeTypes::CONST;
                    buffer->value = std::stoi((*tokensVec)[place].value);
                    if(operationUsage){
                        std::cout << operation << '\n';
                        operation->addChild(buffer);
                        buffer = nullptr;
                        bufferUsage = false;
                        operationUsage = false;
                    }
                }
            }
        }
        else if((*tokensVec)[place].type == TokenTypes::ASSIG){
            if(buffer->type != NodeTypes::VAR){
                exit(1);
            }
            operation = new Node;
            operation->type = NodeTypes::SET;
            operationUsage = true;
            operation->addChild(buffer);
            if(currentEnd == nullptr){
                currentEnd = operation;
            }
            else{
                currentEnd->addChild(operation);
            }
            bufferUsage = false;
            buffer = nullptr;
        }
        else if((*tokensVec)[place].type == TokenTypes::PLUS){
            if(!bufferUsage){
                // throwError("");
                exit(1);
            }
            operation = new Node;
            operation->type = NodeTypes::ADD;
            operationUsage = true;
            operation->addChild(buffer);
            if(currentEnd == nullptr){
                currentEnd = operation;
            }
            else{
                currentEnd->addChild(operation);
            }
            
            bufferUsage = false;
            buffer = nullptr;
        }
        else if((*tokensVec)[place].type == TokenTypes::MIN){
            if(!bufferUsage){
                // throwError("");
                exit(1);
            }
            operation = new Node;
            operation->type = NodeTypes::SUB;
            operationUsage = true;
            operation->addChild(buffer);
            if(currentEnd == nullptr){
                currentEnd = operation;
            }
            else{
                currentEnd->addChild(operation);
            }
            
            bufferUsage = false;
            buffer = nullptr;
        }
        else if((*tokensVec)[place].type == TokenTypes::MUL){
            if(!bufferUsage){
                // throwError("");
                exit(1);
            }
            operation = new Node;
            operation->type = NodeTypes::MUL;
            operationUsage = true;
            operation->addChild(buffer);
            if(currentEnd == nullptr){
                currentEnd = operation;
            }
            else{
                currentEnd->addChild(operation);
            }
            
            bufferUsage = false;
            buffer = nullptr;
        }
        else if((*tokensVec)[place].type == TokenTypes::DIV){
            if(!bufferUsage){
                // throwError("");
                exit(1);
            }
            operation = new Node;
            operation->type = NodeTypes::DIV;
            operationUsage = true;
            operation->addChild(buffer);
            if(currentEnd == nullptr){
                currentEnd = operation;
            }
            else{
                currentEnd->addChild(operation);
            }
            
            bufferUsage = false;
            buffer = nullptr;
        }
        else if((*tokensVec)[place].type == TokenTypes::MORE){
            if(!bufferUsage){
                // throwError("");
                exit(1);
            }
            operation = new Node;
            operation->type = NodeTypes::MORE;
            operationUsage = true;
            operation->addChild(buffer);
            if(currentEnd == nullptr){
                currentEnd = operation;
            }
            else{
                currentEnd->addChild(operation);
            }
            
            bufferUsage = false;
            buffer = nullptr;
        }
        else if((*tokensVec)[place].type == TokenTypes::LESS){
            if(!bufferUsage){
                // throwError("");
                exit(1);
            }
            operation = new Node;
            operation->type = NodeTypes::LESS;
            operationUsage = true;
            operation->addChild(buffer);
            if(currentEnd == nullptr){
                currentEnd = operation;
            }
            else{
                currentEnd->addChild(operation);
            }
            
            bufferUsage = false;
            buffer = nullptr;
        }
        else if((*tokensVec)[place].type == TokenTypes::EQ){
            if(!bufferUsage){
                // throwError("");
                exit(1);
            }
            operation = new Node;
            operation->type = NodeTypes::EQ;
            operationUsage = true;
            operation->addChild(buffer);
            if(currentEnd == nullptr){
                currentEnd = operation;
            }
            else{
                currentEnd->addChild(operation);
            }
            
            bufferUsage = false;
            buffer = nullptr;
        }
        else if((*tokensVec)[place].type == TokenTypes::NEQ){
            if(!bufferUsage){
                // throwError("");
                exit(1);
            }
            operation = new Node;
            operation->type = NodeTypes::NEQ;
            operationUsage = true;
            operation->addChild(buffer);
            if(currentEnd == nullptr){
                currentEnd = operation;
            }
            else{
                currentEnd->addChild(operation);
            }
            
            bufferUsage = false;
            buffer = nullptr;
        }
        else if((*tokensVec)[place].type == TokenTypes::ASSIG){
            if(!bufferUsage){
                // throwError("");
                exit(1);
            }
            operation = new Node;
            operation->type = NodeTypes::SET;
            operationUsage = true;
            operation->addChild(buffer);
            if(currentEnd == nullptr){
                currentEnd = operation;
            }
            else{
                currentEnd->addChild(operation);
            }
            
            bufferUsage = false;
            buffer = nullptr;
        }        
        ++place;
    }

    change = operation;
    operation = nullptr;
    operationUsage = false;
    std::cout << "1 child for for\n";
    forNode->addChild(initial);
    std::cout << "2 child for for\n";
    forNode->addChild(condition);
    std::cout << "3 child for for\n";
    forNode->addChild(change);
    std::cout << "all childs for for\n";

    initial = nullptr;
    condition = nullptr;
    change = nullptr;

    // currentBase->addChild(forNode);
    forNode = nullptr;

    std::cout << "end of for\n";
}