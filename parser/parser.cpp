#include "parser.hpp"

Parser::Parser(std::vector<std::string>* vecForTokens){
    row = 1;
    col = 0;
    currentChar = '\0';
    fileName = "";
    tokensVec = vecForTokens;
}

Parser::~Parser(){
    currentChar = '\0';
    tokensVec = nullptr;
}

bool Parser::parse(std::string path){
    fileName = path;
    // check if file exist
    std::string token = "";

    file.open(path);
    if(!file.is_open()){
        std::cout << "cannot open file " << path << '\n';
        return false;
    }
    while(1){
        getNextChar();
        if(file.eof()){
            tokensVec->push_back(token);
            token = "";
            break;
        }
        if(currentChar == '\n'){
            ++row;
            col = 0;
        }
        else{
            ++col;
        }
        if(token == "(" || token == "{" || token == ")" || token == "}" || token == ";"){
            tokensVec->push_back(token);
            token = "";
        }
        if(currentChar == ' ' || currentChar == '\n' || currentChar == '\t' || currentChar == ';' || currentChar == '(' || currentChar == ')' || currentChar == '{' || currentChar == '}'){
            if(token != ""){
                tokensVec->push_back(token);
                token = "";
            }
            while(currentChar == ' ' || currentChar == '\n' || currentChar == '\t'){
                getNextChar();
            }
        }
        token += currentChar;
    }
    file.close();
    return true;
}

void Parser::throwError(std::string error){
    std::cout << fileName << ':' << row << ':' << col << " - " << error << '\n';
    exit(1);
}

void Parser::getNextChar(){
    currentChar = file.get();
}