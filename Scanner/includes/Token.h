/*
 * Token.h
 *
 *  Created on: Apr 6, 2016
 *      Author: mami1041
 */

#ifndef BUFFER_INCLUDES_TOKEN_H_
#define BUFFER_INCLUDES_TOKEN_H_

class Token {
public:
	Token(char* i,int l, int c, int t, int z);
	virtual ~Token();
	char* inhalt;
	int line;
	int column;
	int type;
	int zuruck;

	int Token::getLine();
	int Token::getColumn();
	int Token::getType();
	int Token::getZuruck();
	char* Token::getInhalt();
};



#endif /* BUFFER_INCLUDES_TOKEN_H_ */
