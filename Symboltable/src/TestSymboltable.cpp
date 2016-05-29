#include "../includes/Symboltable.h"

int main(int argc, char **argv) {

	Symboltable* symboltable;

	symboltable = new Symboltable();

	symboltable->initSymbols();
	std::cout << symboltable->insert("while",1)<< std::endl;



}
