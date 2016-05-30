/*
 * Automat.cpp
 *
 */

#include "../includes/Automat.h"
#include <iostream>

enum state {
	state_start,
	state_way2Id,
	state_way2Dig,
	state_way2And,
	state_startDoubleDot,
	state_startStar,
	state_startEqual,
	state_startEqualDoubleDot,
	state_identifier,	// EZ gehe zuruck:-1 gebe -1 zurück
	state_digit,		// EZ gehe zuruck:-1 gebe -1 zurück
	state_errorAnd,		// EZ gehe zuruck:-1 gebe -1 zurück
	state_doubleDot,	// EZ gehe zuruck:-1 gebe -1 zurück
	state_doubleDotStar,// EZ gehe zuruck:0 gebe 1 zurück
	state_doubleDotEqual, // EZ gehe zuruck:0 gebe 1 zurück
	state_starDoubleDot,  // EZ gehe zuruck:0 gebe 1 zurück
	state_star,			  // EZ gehe zuruck:-1
	state_equalDoubleDotEqual, 	// EZ gehe zuruck:0gebe 1 zurück
	state_equal,				// EZ gehe zuruck:-1 gebe -1 zurück
	state_errorEqual,			// EZ gehe zuruck:-2 gebe -2 zurück
	state_andAnd,			// EZ gehe zuruck:0 gebe 1 zurück
	state_error,					// (EZ)
	state_firstError		// (EZ)
} state;

Automat::Automat() {
	for(int i=0; i<8; i++){
		for(int j=0; j<300; j++){
			table[i][j] = state_error;
		}
	}

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
	table[state_start]['$'] = state_firstError;

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
	table[state_way2Id]['$'] = state_identifier;

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
	table[state_way2Dig]['$'] = state_digit;

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
	table[state_way2And]['&'] = state_andAnd;
	table[state_way2And][':'] = state_errorAnd;
	table[state_way2And]['*'] = state_errorAnd;
	table[state_way2And]['='] = state_errorAnd;
	table[state_way2And][' '] = state_errorAnd;
	table[state_way2And]['$'] = state_errorAnd;

	table[state_startDoubleDot]['a'] = state_doubleDot;
	table[state_startDoubleDot]['0'] = state_doubleDot;
	table[state_startDoubleDot]['+'] = state_doubleDot;
	table[state_startDoubleDot]['-'] = state_doubleDot;
	table[state_startDoubleDot]['<'] = state_doubleDot;
	table[state_startDoubleDot]['>'] = state_doubleDot;
	table[state_startDoubleDot]['!'] = state_doubleDot;
	table[state_startDoubleDot][';'] = state_doubleDot;
	table[state_startDoubleDot]['('] = state_doubleDot;
	table[state_startDoubleDot][')'] = state_doubleDot;
	table[state_startDoubleDot]['{'] = state_doubleDot;
	table[state_startDoubleDot]['}'] = state_doubleDot;
	table[state_startDoubleDot]['['] = state_doubleDot;
	table[state_startDoubleDot][']'] = state_doubleDot;
	table[state_startDoubleDot]['&'] = state_doubleDot;
	table[state_startDoubleDot][':'] = state_doubleDot;
	table[state_startDoubleDot]['*'] = state_doubleDotStar;
	table[state_startDoubleDot]['='] = state_doubleDotEqual;
	table[state_startDoubleDot][' '] = state_doubleDot;
	table[state_startDoubleDot]['$'] = state_doubleDot;

	table[state_startStar]['a'] = state_star;
	table[state_startStar]['0'] = state_star;
	table[state_startStar]['+'] = state_star;
	table[state_startStar]['-'] = state_star;
	table[state_startStar]['<'] = state_star;
	table[state_startStar]['>'] = state_star;
	table[state_startStar]['!'] = state_star;
	table[state_startStar][';'] = state_star;
	table[state_startStar]['('] = state_star;
	table[state_startStar][')'] = state_star;
	table[state_startStar]['{'] = state_star;
	table[state_startStar]['}'] = state_star;
	table[state_startStar]['['] = state_star;
	table[state_startStar][']'] = state_star;
	table[state_startStar]['&'] = state_star;
	table[state_startStar][':'] = state_starDoubleDot;
	table[state_startStar]['*'] = state_star;
	table[state_startStar]['='] = state_star;
	table[state_startStar][' '] = state_star;
	table[state_startStar]['$'] = state_star;

	table[state_startEqual]['a'] = state_equal;
	table[state_startEqual]['0'] = state_equal;
	table[state_startEqual]['+'] = state_equal;
	table[state_startEqual]['-'] = state_equal;
	table[state_startEqual]['<'] = state_equal;
	table[state_startEqual]['>'] = state_equal;
	table[state_startEqual]['!'] = state_equal;
	table[state_startEqual][';'] = state_equal;
	table[state_startEqual]['('] = state_equal;
	table[state_startEqual][')'] = state_equal;
	table[state_startEqual]['{'] = state_equal;
	table[state_startEqual]['}'] = state_equal;
	table[state_startEqual]['['] = state_equal;
	table[state_startEqual][']'] = state_equal;
	table[state_startEqual]['&'] = state_equal;
	table[state_startEqual][':'] = state_startEqualDoubleDot;
	table[state_startEqual]['*'] = state_equal;
	table[state_startEqual]['='] = state_equal;
	table[state_startEqual][' '] = state_equal;
	table[state_startEqual]['$'] = state_equal;

	table[state_startEqualDoubleDot]['a'] = state_errorEqual;
	table[state_startEqualDoubleDot]['0'] = state_errorEqual;
	table[state_startEqualDoubleDot]['+'] = state_errorEqual;
	table[state_startEqualDoubleDot]['-'] = state_errorEqual;
	table[state_startEqualDoubleDot]['<'] = state_errorEqual;
	table[state_startEqualDoubleDot]['>'] = state_errorEqual;
	table[state_startEqualDoubleDot]['!'] = state_errorEqual;
	table[state_startEqualDoubleDot][';'] = state_errorEqual;
	table[state_startEqualDoubleDot]['('] = state_errorEqual;
	table[state_startEqualDoubleDot][')'] = state_errorEqual;
	table[state_startEqualDoubleDot]['{'] = state_errorEqual;
	table[state_startEqualDoubleDot]['}'] = state_errorEqual;
	table[state_startEqualDoubleDot]['['] = state_errorEqual;
	table[state_startEqualDoubleDot][']'] = state_errorEqual;
	table[state_startEqualDoubleDot]['&'] = state_errorEqual;
	table[state_startEqualDoubleDot][':'] = state_errorEqual;
	table[state_startEqualDoubleDot]['*'] = state_errorEqual;
	table[state_startEqualDoubleDot]['='] = state_equalDoubleDotEqual;
	table[state_startEqualDoubleDot][' '] = state_errorEqual;
	table[state_startEqualDoubleDot]['$'] = state_errorEqual;

	//in flower sind alle Übergebenen Chars
	count = 0;
	currentState = 0;
	line = 1;
	column = 0;

	for(int i=0; i<600;i++){
		flower[i] = '\0';
	}
}

Automat::~Automat() {
}

int Automat::identifyToken(char c){
	int number = 0;

	// Aktuelles Zeichen zwischenspeichern
	flower[count] = c;
 	count++;

 	column++;


	// Transition in den nächsten Zustand
 	c = check(c);
	currentState = matrixAdministrator(currentState,(c == '\0')? ' ':c);

	// Testen ob Endzustzand oder nicht
	if(currentState < 8 ){
		number = 0;
	}else{
		//endzustand erreicht flower abschließen
		flower[count] = '\0';
		// Im Fall =:.. 2 zurück
		if(currentState == state_errorEqual){
			number = -2;
		// In den 5 Fällen bei denen es nur eine mögliche Lösung gibt: Token erkannt, keins zurück
		}else if(currentState == state_doubleDotStar || currentState == state_doubleDotEqual || currentState == state_starDoubleDot
				 || currentState == state_equalDoubleDotEqual || currentState == state_andAnd || currentState == '+' || currentState == '-'
				 || currentState == '>' || currentState == '<' || currentState == '!' || currentState == ';' || currentState == '('
				 || currentState == ')' || currentState == '{' || currentState == '}' || currentState == '[' || currentState == ']' || currentState == state_firstError){
			number = 1;
		// Anderen Fälle in denen es 2 Möglichkeiten gibt ein Token zu erkennen, immer 1 zurück, wenn das zweite Zeichen falsch ist
		}else{
			number = -1;
		}

		if(number == -2){ // Das state_errorEqual dient oben nur zur erkennung und soll dann trotzdem nur ein = ausgeben
			currentState = state_equal;
		}

		//falls man zeichen zurück gehen muss , muss man das auch in flower machen
		flower[count+number] = '\0';

		trim(flower);

		int d = -1;
		int i = 0;
		while(flower[i] != '\0'){
			i++;
			d++;
		}
		if(d == -1){
			d = 0;
		}
		token = new Token(flower,line,column - (d - ((number == 1)? 0 : number) - ((currentState == 12 || currentState == 14)? 2 : 0)),currentState); //d und number sind korrekturfaktoren -> number addieren wenn schritt(e) zurück

		count = 0;
		currentState = 0;
	}

	if(flower[count-1] == '\n'){
		line++;
		column = 0;
	}

    if(number<0){
    	column += number;
    }
	return number; //number = 0 -> kein Token, noch ein zeichen, number = 1 Token gefunden kein Zeichen zuruck geben, Number < 0 gehe number zeichen zuruck und token gefunden
}

Token* Automat::getToken(){
	Token* tmp = token;
	token = NULL;
	delete token;
	return tmp;
}

int Automat::matrixAdministrator(int currentState, char ch){
	if(('a'<= ch && ch <= 'z') || ('A'<= ch && ch <= 'Z')){
		 ch = 'a';
	}else if('0'<= ch && ch <= '9'){
		 ch = '0';
	}else if(ch == '\n' || ch == ' ' || ch == '\f' || ch == '\t' || ch == '\v'){
		ch = ' ';
	}
	return table[currentState][ch];
}

void Automat::trim(char* trimmed){
	int i = 1;

	while(trimmed[0] == '\n' || trimmed[0] ==  ' ' || trimmed[0] == '\f' || trimmed[0] == '\t' || trimmed[0] == '\v'){
		i = 1;
		if(trimmed[0] == '\n' || trimmed[0] ==  ' ' || trimmed[0] == '\f' || trimmed[0] == '\t' || trimmed[0] == '\v'){
			while(trimmed[i] != '\0'){
				trimmed[i-1] = trimmed[i];
				trimmed[i] = '\0';
				i++;
			}
		}
	}
}

char Automat::check(char c){
		if(('a'<= c && c <= 'z') || ('A'<= c && c <= 'Z')){
			 c = 'a';
		}else if('0'<= c && c <= '9'){
			 c = '0';
		}else if(c == '\n'  || c == ' ' || c == '\f' || c == '\t' || c == '\v'){
			c = ' ';
		}else if(!(c == '+' || c == '-' || c == '<' || c == '>' || c == '!' || c == ';' || c == '(' || c == ')' || c == '{' || c == '}' || c == '[' || c == ']' || c == '&' || c == ':'  || c == '*' || c == '=' || c == '\0')){
			c = '$';
		}
		return c;
}
