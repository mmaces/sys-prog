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
    void parse();
	Scanner* scanner;
};

class Statements;
class Decls;
class Decl;
class Prog;
class Array;
class Statement;
class Statements;
class Exp;
class Exp2;
class Index;
class Op_exp;
class Op;


class Prog{
public:
	Prog(Scanner* scanner);
	Token* token;
	Decls* decls;
	Statements* statements;
	bool exists = false;
};

class Decls{
public:
	Decls(Scanner* scanner);
	Token* token;
	Decls* decls;
	Decl* decl;
	bool exists = false;
};

class Decl{
public:
	Decl(Scanner* scanner);
	Token* token;
	Array* array;
	bool exists = false;
};

class Array{
public:
	Array(Scanner* scanner);
	Token* token;
	bool exists = false;
};

class Statements{
public:
	Statements(Scanner* scanner);
	Token* token;
	Statement* statement;
	Statements* statements;
	bool exists = false;
};

class Statement{
public:
	Statement(Scanner* scanner);
	Token* token;
	Index* index;
	Exp* exp;
	Statements* statements;
	Statement* statement;
	bool exists = false;
};

class Exp{
public:
	Exp(Scanner* scanner);
	Token* token;
	Exp2* exp2;
	Op_exp* op_exp;
	bool exists = false;
};

class Exp2{
public:
	Exp2(Scanner* scanner);
	Token* token;
	Exp* exp;
	Index* index;
	Exp2* exp2;
	bool exists = false;
};

class Index{
public:
	Index(Scanner* scanner);
	Token* token;
	Exp* exp;
	bool exists = false;
};

class Op_exp{
public:
	Op_exp(Scanner* scanner);
	Token* token;
	Op* op;
	Exp* exp;
	bool exists = false;
};

class Op{
public:
	Op(Scanner* scanner);
	Token* token;
	bool exists = false;
};

#endif /* INCLUDES_PARSER_H_ */
