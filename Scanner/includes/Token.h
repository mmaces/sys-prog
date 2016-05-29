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
	Token(char* i,int l, int c, int t);
	virtual ~Token();
	char* inhalt;//=> i im konstruktor
	int line;
	int column;
	int type;

	int getLine();
	int getColumn();
	int getType();
	char* getInhalt();
};



#endif /* BUFFER_INCLUDES_TOKEN_H_ */
