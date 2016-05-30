#include "../includes/Token.h"

Token::Token(char* i,int l, int c, int t) {
	inhalt = i;
	line = l;
	column = c;
	type = t;
}

Token::~Token() {

}

