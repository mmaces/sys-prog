/*
 * Symboltable.cpp
 *
 *  Created on: Sep 26, 2012
 *      Author: knad0001
 */

#include <string.h>

#include "../includes/Symboltable.h"


SymtabEntry::SymtabEntry(char* lex, SymtabEntry* next, int ttype){
	this->lex = malloc(strlen(lex)+1);
	strcpy(this->lex,lex);
	this->next = next;
	this->ttype = ttype;

}

SymtabEntry::~SymtabEntry() {
	delete[] lex;
	delete[] next;
}


Symboltable::Symboltable() {
	bzero(this->tab,SYMTABSIZE*sizeof(SymtabEntry*));

	// TODO Auto-generated constructor stub
}


unsigned int Symboltable::hash(char* lex){
	int size = strlen(lex);
	unsigned int hash = 0;// Damit wir keine negative Werte bekommen
	for (int i = 0; i < size; i++)
		hash = ((unsigned int)(lex[i]))*(i+1);
	hash %= SYMTABSIZE; // damit hashWert nicht größer als das Array ist
	return hash;
}

void Symboltable::initSymbols(){
	insert("while", 1);
	insert("WHILE", 1);
	insert("if", 2);
	insert("IF", 2);

}


Symboltable::~Symboltable() {
	delete[] tab;
}

SymtabEntry* Symboltable::insert(char* lexem, int ttype){
	unsigned int hash = this->hash(lexem);
	SymtabEntry* current = this->tab[hash];
	while (current){
		if (strcmp(current->lex, lexem))
			current = current->next;
		else
			return current;
	}
	this->tab[hash] = current = new SymtabEntry(lexem,this->tab[hash], ttype);
	return current;
}


















