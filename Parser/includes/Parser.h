/*
 * Parser.h
 *
 *  Created on: Jun 8, 2016
 *      Author: kuar1013
 */

#ifndef INCLUDES_PARSER_H_
#define INCLUDES_PARSER_H_

#include "../../Scanner/includes/Scanner.h"
#include "Tree.h"



class Parser{
public:
	// Konstruktoren
	Parser(char* file);
	Tree* parse();
	Scanner* scanner;
};

class Prog{
public:
	Prog(Scanner scanner);
	Token* token;
};

class Decls{
public:
	Decls(Scanner scanner);
	Token* token;
};

class Decl{
public:
	Decl(Scanner scanner);
	Token* token;
};

class Array{
public:
	Array(Scanner scanner);
	Token* token;
};

class Statements{
public:
	Statements(Scanner scanner);
	Token* token;
};

class Statement{
public:
	Statement(Scanner scanner);
	Token* token;
};

class Exp{
public:
	Exp(Scanner scanner);
	Token* token;
};

class Exp2{
public:
	Exp2(Scanner scanner);
	Token* token;
};

class Index{
public:
	Index(Scanner scanner);
	Token* token;
};

class Op_exp{
public:
	Op_exp(Scanner scanner);
	Token* token;
};

class Op{
public:
	Op(Scanner scanner);
	Token* token;
};



#endif /* INCLUDES_PARSER_H_ */
