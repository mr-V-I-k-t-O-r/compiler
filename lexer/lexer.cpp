#include "lexer.hpp"

Lexer::Lexer(const std::vector<std::string>* vecForTerms, std::vector<Token>* vecForTokens){
	tokensVec = vecForTokens;
	termsVec = vecForTerms;
}

Lexer::~Lexer(){
	tokensVec = nullptr;
	termsVec = nullptr;
}

void Lexer::analyze(){
	Token token;
	for(auto i: *termsVec){
		token.value = i;
		if(i == "for"){
			token.type = TokenTypes::FOR;
			tokensVec->push_back(token);
			std::cout << token.value << "\tFOR\n";
		}
		else if (i == "("){
			token.type = TokenTypes::LPAR;
			std::cout << token.value << "\tLPAR\n";
		}
		else if (i == ")"){
			token.type = TokenTypes::RPAR;
			std::cout << token.value << "\tRPAR\n";
		}
		else if (i == "{"){
			token.type = TokenTypes::LBRA;
			std::cout << token.value << "\tLBRA\n";
		}
		else if (i == "}"){
			token.type = TokenTypes::RBRA;
			std::cout << token.value << "\tRBRA\n";
		}
		else if (i == ";"){
			token.type = TokenTypes::SEMICOL;
			std::cout << token.value << "\tSEMICOL\n";
		}
		else if (i == "<"){
			token.type = TokenTypes::LESS;
			std::cout << token.value << "\tLESS\n";
		}
		else if (i == ">"){
			token.type = TokenTypes::MORE;
			std::cout << token.value << "\tMORE\n";
		}
		else if (i == "!"){
			token.type = TokenTypes::NOT;
			std::cout << token.value << "\tNOT\n";
		}
		else if (i == "=="){
			token.type = TokenTypes::EQ;
			std::cout << token.value << "\tEQ\n";
		}
		else if (i == "!="){
			token.type = TokenTypes::NEQ;
			std::cout << token.value << "\tNEQ\n";
		}
		else if (i == "="){
			token.type = TokenTypes::ASSIG;
			std::cout << token.value << "\tASSIG\n";
		}
		else if (i == "+"){
			token.type = TokenTypes::PLUS;
			std::cout << token.value << "\tPLUS\n";
		}
		else if (i == "-"){
			token.type = TokenTypes::MIN;
			std::cout << token.value << "\tMIN\n";
		}
		else if (i == "*"){
			token.type = TokenTypes::MUL;
			std::cout << token.value << "\tMUL\n";
		}
		else if (i == "/"){
			token.type = TokenTypes::DIV;
			std::cout << token.value << "\tDIV\n";
		}
		else if(checkInt(i)){
			token.type = TokenTypes::INT;
			std::cout << token.value << "\tINT\n";
		}
		//check is_digit
		else{
			token.type = TokenTypes::VAR;
			std::cout << token.value << "\tVAR\n";
		}
	}
}

bool Lexer::checkInt(std::string integer){
	std::string::const_iterator it = integer.begin();
    while (it != integer.end() && std::isdigit(*it)){
		++it;
	}
    return !integer.empty() && it == integer.end();
}