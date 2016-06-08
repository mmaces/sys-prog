#include "../includes/Parser.h"


Parser::Parser(char* file){
	scanner = new Scanner(file);
};

Tree* Parser::parse(){


	Tree* t = new Prog(scanner);
	return t;
}

Prog* Prog::Prog(Scanner* scanner){
	token = scanner->nextToken();
//TODO: read write nur klein ?
	if(token->inhalt == 'int' || token->symTab->ttype == 1 /*while*/|| token->symTab->ttype == 2 /*IF*/
			|| token->inhalt == 'write' || token->inhalt == 'read' || token->symTab->ttype == 3 /*identifier*/){
		Decls decls = new Decls(scanner);
		if(!decls)return 0;
		Statements statements = new Statements(scanner);
		if(!statements){
			delete (decls);
			return 0;
		}
		return new Prog(scanner,decls,statements);
	}
	cout<<"Fehlerzeichen: " <<token->inhalt << " in Linie: "<< token->line<<" und Spalte: "<< token->column<<endl;
	return 0;
}

Decls* Decls::Decls(Scanner* scanner){
	token = scanner->nextToken();

	//TODO weitermachen alles (Ende letzter Termin)
	if(token->inhalt == 'int' || token->symTab->ttype == 1 /*while*/|| token->symTab->ttype == 2 /*IF*/
				|| token->inhalt == 'write' || token->inhalt == 'read' || token->symTab->ttype == 3 /*identifier*/){
			Decls decls = new Decls(scanner);
			if(!decls)return 0;
			Statements statements = new Statements(scanner);
			if(!statements){
				delete (decls);
				return 0;
			}
			return new Prog(scanner,decls,statements);
		}
		cout<<"Fehlerzeichen: " <<token->inhalt << " in Linie: "<< token->line<<" und Spalte: "<< token->column<<endl;
		return 0;
}
