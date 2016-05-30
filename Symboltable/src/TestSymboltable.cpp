#include "../includes/Symboltable.h"
#include <iostream>
#include <stdio.h>



int main(int argc, char **argv) {

	Symboltable* symboltable;

	symboltable = new Symboltable();

	symboltable->initSymbols();
	cout << (symboltable->insert("while",1)->lex) << endl;
	cout << (symboltable->insert("UI",1)->lex) << endl;
}
