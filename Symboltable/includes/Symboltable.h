/*
 * Symboltable.h
 *
 *  Created on: Sep 26, 2012
 *      Author: knad0001
 */

#ifndef SYMBOLTABLE_H_
#define SYMBOLTABLE_H_
using namespace std;

#define SYMTABSIZE 1025

class SymtabEntry{
public:
	SymtabEntry(char* lex, SymtabEntry* next, int ttype);
	virtual ~SymtabEntry();
	char* lex;
	SymtabEntry* next;
	int ttype;
};

class Symboltable {
private:

	SymtabEntry* tab[SYMTABSIZE];
	unsigned int hash(char* lex);

public:
	Symboltable();
	virtual ~Symboltable();
	SymtabEntry* insert(char* lexem, int ttype);
	void initSymbols();
};

#endif /* SYMBOLTABLE_H_ */
