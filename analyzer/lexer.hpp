#ifndef LEXER
#define LEXER

#include <ifstream>

#include "token.hpp"

class Lexer{
private:
	std::ifstream file;
	std::string path;
	int row_number;
	int col_number
	char current_char;

	Token get_next_token();
	void next_char();
	void add_to_identificators_table(Token token);
	void throw_error(std::string error);

public:
	Lexer();
	void analyze(std::string path);
};

#endif
