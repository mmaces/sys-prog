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
#include<iostream>
#include<fstream>

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
	~Parser();
	fstream fs;

	int parse();
	int label1;
	int label2;
	int label3;
	int label4;


    void makeCodeProg();
	void makeCodeDecls(Decls* decls);
	void makeCodeDecl(Decl* decl);
	void makeCodeStatements(Statements* statements);
	void makeCodeStatement(Statement* statement);
	void makeCodeIndex(Index* index);
	void makeCodeExp(Exp* exp);
	void makeCodeExp2(Exp2* exp2);
	void makeCodeOp_Exp(Op_exp* op_exp);
	void makeCodeOp(Op* op);


    void typeCheckProg();
    void typeCheckDecl(Decl* decl);
    void typeCheckDecls(Decls* decls);
    void typeCheckArray(Array* array);
    void typeCheckStatements(Statements* statements);
    void typeCheckStatement(Statement* statement);
    void typeCheckIndex(Index* index);
    void typeCheckExp(Exp* exp);
    void typeCheckExp2(Exp2* exp2);
    void typeCheckOp_Exp(Op_exp* op_exp);
    void typeCheckOp(Op* op);
	Scanner* scanner;
	Prog* prog;
};

class Prog{
public:
	Prog(Scanner* scanner);
	~Prog();
	Token* token;
	Decls* decls;
	Statements* statements;
	int status = 0; //-1 Existent mit Fehler | 0 leer((e) Menge) | 1 Existent ohne Fehler
	int type;
};

class Decls{
public:
	Decls(Scanner* scanner);
	~Decls();
	Token* token;
	Decls* decls;
	Decl* decl;
	int status = 0;
	int type;
};

class Decl{
public:
	Decl(Scanner* scanner);
	~Decl();
	Array* array;
	Token* token;
	char inhalt[5000];
	int varType;
	int status = 0;
	int type;
};

class Array{
public:
	Array(Scanner* scanner);
	~Array();
	Token* token;
	char inhalt[5000];
	int varType;
	int status = 0;
	int type;
};

class Statements{
public:
	Statements(Scanner* scanner);
	~Statements();
	Token* token;
	Statement* statement;
	Statements* statements;
	int status = 0;
	int type;
};

class Statement{
public:
	Statement(Scanner* scanner);
	~Statement();
	Token* token;
	char inhalt[5000];
	int varType;
	Index* index;
	Exp* exp;
	Statements* statements;
	Statement* statement;
	Statement* statement2;
	bool beginWithCurrentToken = false;
	int status = 0;
	int type;
};

class Exp{
public:
	Exp(Scanner* scanner);
	~Exp();
	Token* token;
	Exp2* exp2;
	Op_exp* op_exp;
	int status = 0;
	int type;
};

class Exp2{
public:
	Exp2(Scanner* scanner);
	~Exp2();
	Token* token;
	char inhalt[5000];
	int varType;
	Exp* exp;
	Index* index;
	Exp2* exp2;
	int status = 0;
	int type;
};

class Index{
public:
	Index(Scanner* scanner);
	~Index();
	Token* token;
	Exp* exp;
	int status = 0;
	bool isOperandOrDDE(Token* tk);
	int type;
};

class Op_exp{
public:
	Op_exp(Scanner* scanner);
	~Op_exp();
	Token* token;
	Op* op;
	Exp* exp;
	int status = 0;
	int type;
};

class Op{
public:
	Op(Scanner* scanner);
	~Op();
	Token* token;
	char inhalt[5000];
	int status = 0;
	bool isOperand(Token* tk);
	int type;
};

#endif /* INCLUDES_PARSER_H_ */
