#include "../includes/Token.h"

Token::Token(char* i,int l, int c, int t, int z) {
	inhalt = i;
	line = l;
	column = c;
	type = t;
	zuruck = z;
}

Token::~Token() {
	delete[] type;
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
int Token::getZuruck(){
	return zuruck;
}
char* Token::getInhalt(){
	return inhalt;
}

