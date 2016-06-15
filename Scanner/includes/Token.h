/*
 * Token.h
 *
 *  Created on: Apr 6, 2016
 *      Author: mami1041
 */

#ifndef BUFFER_INCLUDES_TOKEN_H_
#define BUFFER_INCLUDES_TOKEN_H_
#include "../../Symboltable/includes/Symboltable.h"


class Token {
public:
	Token(char* i,int l, int c, int t);
	virtual ~Token();
	char* inhalt;//=> i im konstruktor
	int line;
	int column;
	int type;
	SymtabEntry* symTab = 0;

	void setSymTab(SymtabEntry* symTab);
};



#endif /* BUFFER_INCLUDES_TOKEN_H_ */
