#include <fstream>
#include <iostream>
#include <vector>

class Parser{
private:
    int row;
    int col;
    char currentChar;
    std::string fileName;
    std::ifstream file;
    std::vector<std::string>* tokensVec;

    void getNextChar();

public:
    Parser(std::vector<std::string>* );
    ~Parser();

    bool parse(std::string path);
    void throwError(std::string error);
};