#include "token.hpp"

Token::Token(){
	this->token_type = end_of_file;
	this->param_value = "";
}

Token::Token(TokenType tok_type){
	this->token_type = tok_type;
	this->param_value = "";
}

Token::Token(TokenType tok_type, std::string par_value){
	this->token_type = tok_type;
	this->param_value = par_value;
}