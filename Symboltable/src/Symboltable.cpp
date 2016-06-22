/*
 * Symboltable.cpp
 *
 *  Created on: Sep 26, 2012
 *      Author: knad0001
 */

#include <string.h>
#include <stdlib.h>
#include <iostream>

#include "../includes/Symboltable.h"



SymtabEntry::SymtabEntry(char* lex, SymtabEntry* next,int ttype){
	this->lex = (char*)malloc(strlen(lex)+1);
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
	initSymbols();

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
	insert("while");
	insert("WHILE");
	insert("if");
	insert("IF");
	insert("write");  // ttype 4
	insert("read");	  // ttype 5
	insert("else");	  // ttype 6
	insert("ELSE");	  // ttype 6
	insert("int");	  // ttype 7
}


Symboltable::~Symboltable() {
	delete[] tab;
}

SymtabEntry* Symboltable::insert(char* lexem){
	unsigned int hash = this->hash(lexem);
	SymtabEntry* current = this->tab[hash];
	while (current){
		if (strcmp(current->lex, lexem))
			current = current->next;
		else
			return current;
	}

	int ttype = 3;
	if(!(strcmp(lexem, "if")&&strcmp(lexem,"IF"))){
		ttype = 2;
	}else if(!(strcmp(lexem, "while")&&strcmp(lexem,"WHILE"))){
		ttype = 1;
	}else if(!(strcmp(lexem, "write"))){
		ttype = 4;
	}else if(!(strcmp(lexem, "read"))){
		ttype = 5;
	}else if(!(strcmp(lexem, "else")&&strcmp(lexem,"ELSE"))){
		ttype = 6;
	}else if(!(strcmp(lexem, "int"))){
		ttype = 7;
	}

	this->tab[hash] = current = new SymtabEntry(lexem,this->tab[hash], ttype);
	return current;
}


















