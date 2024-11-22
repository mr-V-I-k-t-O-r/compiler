#include <fstream>
#include <iostream>

class Parser{
private:
    int row;
    int col;
    char currentChar;
    std::string currentString;
    std::string fileName;
    std::ifstream file;

public:
    Parser();
    ~Parser();

    bool parse(std::string path);
    void throwError(std::string error);
};