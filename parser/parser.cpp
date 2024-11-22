#include "parser.hpp"

Parser::Parser(){
    row = 1;
    col = 0;
    currentChar = '\0';
    currentString = "";
    fileName = "";
}

Parser::~Parser(){
    currentChar = '\0';
    currentString = "";
}

bool Parser::parse(std::string path){
    fileName = path;
    // check if file exist

    file.open(path);
    if(!file.is_open()){
        std::cout << "cannot open file " << path << '\n';
        return false;
    }
    while(1){
        file >> currentChar;
        if(file.eof()){
            break;
        }
        // ifstream don`t give me \n symbols
        if(currentChar == '\n'){
            ++row;
            col = 0;
        }
        else{
            ++col;
        }
        std::cout << "now currentChar is " << currentChar << '\n';

    }
    file.close();
    return true;
}

void Parser::throwError(std::string error){
    std::cout << fileName << ':' << row << ':' << col << " - " << error << '\n';
    exit(1);
}