#include "../includes/Token.h"

Token::Token(char* i,int l, int c, int t) {
	inhalt = i;
	line = l;
	column = c;
	type = t;
}

Token::~Token() {

}

int Token::getLine(){
	return line;
}

int Token::getColumn(){
	return column;
}
int Token::getType(){
	return type;
}
char* Token::getInhalt(){
	return inhalt;
}

