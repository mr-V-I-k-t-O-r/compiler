#include "lexer.hpp"

Lexer::Lexer(const std::vector<std::string>* vecForTerms, std::vector<Token>* vecForTokens, std::map<std::string, int> *variables){
	tokensVec = vecForTokens;
	termsVec = vecForTerms;
	vars = variables;
}

Lexer::~Lexer(){
	tokensVec = nullptr;
	termsVec = nullptr;
	vars = nullptr;
}

void Lexer::analyze(){
	Token token;
	bool type = false;
	for(auto i: *termsVec){
		token.value = i;
		if(i == "for"){
			token.type = TokenTypes::FOR;
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
		else if (i == "int"){
			token.type = TokenTypes::TYPE;
			type = true;
			std::cout << token.value << "\tTYPE\n";
		}
		//check is_digit
		else{
			if(type){
				if(vars->find(i) != vars->end()){
					exit(1);
				}
				(*vars)[i] = 0;
			}
			if(vars->find(i) != vars->end()){
				token.type = TokenTypes::VAR;
				type = false;
				std::cout << token.value << "\tVAR\n";
			}
		}
		tokensVec->push_back(token);
	}
	Token end;
	end.type = TokenTypes::END;
	tokensVec->push_back(end);
}

bool Lexer::checkInt(std::string integer){
	std::string::const_iterator it = integer.begin();
    while (it != integer.end() && std::isdigit(*it)){
		++it;
	}
    return !integer.empty() && it == integer.end();
}