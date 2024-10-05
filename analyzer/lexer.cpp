#include "lexer.hpp"

Lexer::Lexer(){
	// TODO check is ifstream can be initialize by 0
	this->file = 0;
	this->path = "";
	this->row_number = 0;
	this->col_number = 0;
	this->current_char = '\0';
}

void Lexer::analize(std::string path){
	this->file.open(path);
	this->path = path;
	if(file.is_open()){
		// TODO check how to recv data from file by characters
		this->current_char = file.begin();
		this->row_number = 1;
		this->col_number = 1;
	}
	else{
		throw_error("can`t open source file");
		// TODO check if exit() close all programm, if yes, then return is not need
		return 0
	}
}

void Lexer::throw_error(std::string error){
	std::cout << this->path + ":" + std::to_string(this->row_number) + ":" + std::to_string(this->col_number) + " " + error + '\n';
	exit(1);
}

void Lexer::next_char(){
	// TODO increment current_char
	if(this->current_char == '\n'){
		++this->row_number;
		this->col_number = 1;
	}

}

Token Lexer::get_next_token(){
	next_char;
	std::string lexem = "";
	// TODO now it can work only with form n = 3, but can`t with n=3 
	while(this->current_char != ' ' or this->current_char != '\n' or this->current_char != '\t'){
		lexem += next_char;
		next_char();
	}

}

void Lexer::add_to_identificators_table(Token token){

}