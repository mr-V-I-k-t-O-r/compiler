#ifndef TOKEN
#define TOKEN

enum class TokenType = {id, number, string, if, else, for, while, do, equal, plus, minus, multiply, divide, exponent, 
	lpar, rpar, lbrace, rbrace, lbracket, rbracket, comparator, and, or, not, comma, semicolumn, skreen, end_of_file};

class Token{
private:
	TokenType token_type;
	std::string param_value;
public:
	Token();
	Token(TokenType tok_type);
	Token(TokenType tok_type, std::string par_value);

	TokenType type();
	std::string value();
};

#endif