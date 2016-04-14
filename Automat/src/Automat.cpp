/*
 * Automat.cpp
 *
 */

#include "../includes/Automat.h"

enum state {
	state_start,
	state_way2Id,
	state_way2Dig,
	state_way2And,
	state_startDoubleDot,
	state_startStar,
	state_startEqual,
	state_startEqualDoubleDot,
	state_identifier,	// EZ
	state_digit,		// EZ
	state_errorAnd,		// EZ
	state_doubleDot,	// EZ
	state_doubleDotStar,// EZ
	state_doubleDotEqual, // EZ
	state_starDoubleDot,  // EZ
	state_star,			  // EZ
	state_equalDoubleDotEqual, 	// EZ
	state_equal,				// EZ
	state_errorEqual,			// EZ
	state_andAnd				// EZ
} state;

Automat::Automat() {
	table[state_start]['a'] = state_way2Id;
	table[state_start]['0'] = state_way2Dig;
	table[state_start]['+'] = '+';
	table[state_start]['-'] = '-';
	table[state_start]['<'] = '<';
	table[state_start]['>'] = '>';
	table[state_start]['!'] = '!';
	table[state_start][';'] = ';';
	table[state_start]['('] = '(';
	table[state_start][')'] = ')';
	table[state_start]['{'] = '{';
	table[state_start]['}'] = '}';
	table[state_start]['['] = '[';
	table[state_start][']'] = ']';
	table[state_start]['&'] = state_way2And;
	table[state_start][':'] = state_startDoubleDot;
	table[state_start]['*'] = state_startStar;
	table[state_start]['='] = state_startEqual;
	table[state_start][' '] = state_start;

	table[state_way2Id]['a'] = state_way2Id;
	table[state_way2Id]['0'] = state_way2Id;
	table[state_way2Id]['+'] = state_identifier;
	table[state_way2Id]['-'] = state_identifier;
	table[state_way2Id]['<'] = state_identifier;
	table[state_way2Id]['>'] = state_identifier;
	table[state_way2Id]['!'] = state_identifier;
	table[state_way2Id][';'] = state_identifier;
	table[state_way2Id]['('] = state_identifier;
	table[state_way2Id][')'] = state_identifier;
	table[state_way2Id]['{'] = state_identifier;
	table[state_way2Id]['}'] = state_identifier;
	table[state_way2Id]['['] = state_identifier;
	table[state_way2Id][']'] = state_identifier;
	table[state_way2Id]['&'] = state_identifier;
	table[state_way2Id][':'] = state_identifier;
	table[state_way2Id]['*'] = state_identifier;
	table[state_way2Id]['='] = state_identifier;
	table[state_way2Id][' '] = state_identifier;

	table[state_way2Dig]['a'] = state_digit;
	table[state_way2Dig]['0'] = state_way2Dig;
	table[state_way2Dig]['+'] = state_digit;
	table[state_way2Dig]['-'] = state_digit;
	table[state_way2Dig]['<'] = state_digit;
	table[state_way2Dig]['>'] = state_digit;
	table[state_way2Dig]['!'] = state_digit;
	table[state_way2Dig][';'] = state_digit;
	table[state_way2Dig]['('] = state_digit;
	table[state_way2Dig][')'] = state_digit;
	table[state_way2Dig]['{'] = state_digit;
	table[state_way2Dig]['}'] = state_digit;
	table[state_way2Dig]['['] = state_digit;
	table[state_way2Dig][']'] = state_digit;
	table[state_way2Dig]['&'] = state_digit;
	table[state_way2Dig][':'] = state_digit;
	table[state_way2Dig]['*'] = state_digit;
	table[state_way2Dig]['='] = state_digit;
	table[state_way2Dig][' '] = state_digit;

	table[state_way2And]['a'] = state_errorAnd;
	table[state_way2And]['0'] = state_errorAnd;
	table[state_way2And]['+'] = state_errorAnd;
	table[state_way2And]['-'] = state_errorAnd;
	table[state_way2And]['<'] = state_errorAnd;
	table[state_way2And]['>'] = state_errorAnd;
	table[state_way2And]['!'] = state_errorAnd;
	table[state_way2And][';'] = state_errorAnd;
	table[state_way2And]['('] = state_errorAnd;
	table[state_way2And][')'] = state_errorAnd;
	table[state_way2And]['{'] = state_errorAnd;
	table[state_way2And]['}'] = state_errorAnd;
	table[state_way2And]['['] = state_errorAnd;
	table[state_way2And][']'] = state_errorAnd;
	table[state_way2And]['&'] = state_digit;
	table[state_way2And][':'] = state_errorAnd;
	table[state_way2And]['*'] = state_errorAnd;
	table[state_way2And]['='] = state_errorAnd;
	table[state_way2And][' '] = state_errorAnd;

	table[state_startDoubleDot]['a'] = ':';
	table[state_startDoubleDot]['0'] = ':';
	table[state_startDoubleDot]['+'] = ':';
	table[state_startDoubleDot]['-'] = ':';
	table[state_startDoubleDot]['<'] = ':';
	table[state_startDoubleDot]['>'] = ':';
	table[state_startDoubleDot]['!'] = ':';
	table[state_startDoubleDot][';'] = ':';
	table[state_startDoubleDot]['('] = ':';
	table[state_startDoubleDot][')'] = ':';
	table[state_startDoubleDot]['{'] = ':';
	table[state_startDoubleDot]['}'] = ':';
	table[state_startDoubleDot]['['] = ':';
	table[state_startDoubleDot][']'] = ':';
	table[state_startDoubleDot]['&'] = ':';
	table[state_startDoubleDot][':'] = ':';
	table[state_startDoubleDot]['*'] = state_doubleDotStar;
	table[state_startDoubleDot]['='] = state_doubleDotEqual;
	table[state_startDoubleDot][' '] = ':';

	table[state_startDoubleDot]['a'] = '*';
	table[state_startDoubleDot]['0'] = '*';
	table[state_startDoubleDot]['+'] = '*';
	table[state_startDoubleDot]['-'] = '*';
	table[state_startDoubleDot]['<'] = '*';
	table[state_startDoubleDot]['>'] = '*';
	table[state_startDoubleDot]['!'] = '*';
	table[state_startDoubleDot][';'] = '*';
	table[state_startDoubleDot]['('] = '*';
	table[state_startDoubleDot][')'] = '*';
	table[state_startDoubleDot]['{'] = '*';
	table[state_startDoubleDot]['}'] = '*';
	table[state_startDoubleDot]['['] = '*';
	table[state_startDoubleDot][']'] = '*';
	table[state_startDoubleDot]['&'] = '*';
	table[state_startDoubleDot][':'] = state_starDoubleDot;
	table[state_startDoubleDot]['*'] = '*';
	table[state_startDoubleDot]['='] = '*';
	table[state_startDoubleDot][' '] = '*';

	table[state_startDoubleDot]['a'] = '=';
	table[state_startDoubleDot]['0'] = '=';
	table[state_startDoubleDot]['+'] = '=';
	table[state_startDoubleDot]['-'] = '=';
	table[state_startDoubleDot]['<'] = '=';
	table[state_startDoubleDot]['>'] = '=';
	table[state_startDoubleDot]['!'] = '=';
	table[state_startDoubleDot][';'] = '=';
	table[state_startDoubleDot]['('] = '=';
	table[state_startDoubleDot][')'] = '=';
	table[state_startDoubleDot]['{'] = '=';
	table[state_startDoubleDot]['}'] = '=';
	table[state_startDoubleDot]['['] = '=';
	table[state_startDoubleDot][']'] = '=';
	table[state_startDoubleDot]['&'] = '=';
	table[state_startDoubleDot][':'] = state_startEqualDoubleDot;
	table[state_startDoubleDot]['*'] = '=';
	table[state_startDoubleDot]['='] = '=';
	table[state_startDoubleDot][' '] = '=';

	table[state_startDoubleDot]['a'] = state_errorEqual;
	table[state_startDoubleDot]['0'] = state_errorEqual;
	table[state_startDoubleDot]['+'] = state_errorEqual;
	table[state_startDoubleDot]['-'] = state_errorEqual;
	table[state_startDoubleDot]['<'] = state_errorEqual;
	table[state_startDoubleDot]['>'] = state_errorEqual;
	table[state_startDoubleDot]['!'] = state_errorEqual;
	table[state_startDoubleDot][';'] = state_errorEqual;
	table[state_startDoubleDot]['('] = state_errorEqual;
	table[state_startDoubleDot][')'] = state_errorEqual;
	table[state_startDoubleDot]['{'] = state_errorEqual;
	table[state_startDoubleDot]['}'] = state_errorEqual;
	table[state_startDoubleDot]['['] = state_errorEqual;
	table[state_startDoubleDot][']'] = state_errorEqual;
	table[state_startDoubleDot]['&'] = state_errorEqual;
	table[state_startDoubleDot][':'] = state_errorEqual;
	table[state_startDoubleDot]['*'] = state_errorEqual;
	table[state_startDoubleDot]['='] = state_equalDoubleDotEqual;
	table[state_startDoubleDot][' '] = state_errorEqual;

	flower = '';//Alle Übergebenen Chars
	count = 0;
	type = 0;// t = 1 identifier, t = 2 digits
	currentState = 0;
}

Automat::~Automat() {
	delete[] flower;
}

int Automat::identifyToken(char c){
	int number;
	flower[count] = c;
	count++;

	currentState = matrixAdministrator(currentState,c);
	if(currentState < 8){
		number = 0;
	}else if(){//im fall von entzuständen
		// Token erstellen
		//gewünschte anzahl an zeichen zurück gehen
		//flower usw. alles auf 0
	}

	return number; //ident = 0 -> kein Token
}

Token* Automat::getToken(){
	Token t = token;
	~token();
	return t;
}

int Automat::matrixAdministrator(int i, char c){
	if(('a'<= c && c <= 'z') || ('A'<= c && c <= 'Z')){
		c = 'a';
	}else if(c == '\n' || c == ' ' || c == '\f' || c == '\t' || c == '\v'){
		c = ' ';
	}
	return table[i][c];
}

