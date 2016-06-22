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

class Parser{
public:
	// Konstruktoren
	Parser(char* file);

    int parse();
    void typeCheckProg(Prog* prog);
    void typeCheckDecl(Decl* decl);
    void typeCheckDecls(Decls* decls);
    void typeCheckArray(Array* array);

	Scanner* scanner;
	Prog* prog;
};




class Prog{
public:
	Prog(Scanner* scanner);
	Token* token;
	Decls* decls;
	Statements* statements;
	int status = 0; //-1 Existent mit Fehler | 0 leer((e) Menge) | 1 Existent ohne Fehler
	int type;
};

class Decls{
public:
	Decls(Scanner* scanner);
	Token* token;
	Decls* decls;
	Decl* decl;
	int status = 0;
	int type;
};

class Decl{
public:
	Decl(Scanner* scanner);
	Array* array;
	Token* token;

	int status = 0;
	int type;
};

class Array{
public:
	Array(Scanner* scanner);
	Token* token;
	int status = 0;
	int type;
};

class Statements{
public:
	Statements(Scanner* scanner);
	Token* token;
	Statement* statement;
	Statements* statements;
	int status = 0;
};

class Statement{
public:
	Statement(Scanner* scanner);
	Token* token;
	Index* index;
	Exp* exp;
	Statements* statements;
	Statement* statement;
	Statement* statement2;
	bool beginWithCurrentToken = false;
	int status = 0;
};

class Exp{
public:
	Exp(Scanner* scanner);
	Token* token;
	Exp2* exp2;
	Op_exp* op_exp;
	int status = 0;
};

class Exp2{
public:
	Exp2(Scanner* scanner);
	Token* token;
	Exp* exp;
	Index* index;
	Exp2* exp2;
	int status = 0;
};

class Index{
public:
	Index(Scanner* scanner);
	Token* token;
	Exp* exp;
	int status = 0;
	bool isOperandOrDDE(Token* tk);
};

class Op_exp{
public:
	Op_exp(Scanner* scanner);
	Token* token;
	Op* op;
	Exp* exp;
	int status = 0;
};

class Op{
public:
	Op(Scanner* scanner);
	Token* token;
	int status = 0;
	bool isOperand(Token* tk);
};

#endif /* INCLUDES_PARSER_H_ */
