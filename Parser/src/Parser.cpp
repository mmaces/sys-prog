#include "../includes/Parser.h"



Parser::Parser(char* file){
	scanner = new Scanner(file);
};

void Parser::parse(){
	Prog* prog = new Prog(scanner);
}


Prog::Prog(Scanner* scanner){
//TODO: read write nur klein ?

	this->decls = new Decls(scanner);

	if(token->symTab->ttype == 1 /*while*/|| token->symTab->ttype == 2 /*IF*/
		|| token->symTab->ttype == 4 /*write*/ || token->symTab->ttype == 5 /*read*/
		|| token->symTab->ttype == 3 /*identifier*/){
		this->statements = new Statements(scanner);
	}

}

Decls::Decls(Scanner* scanner) {
	int semicolon = 1;
	this->decl = new Decl(scanner);
	if(!(this->decl->exists)){
		this->decl = NULL;
	}

	cout << "Komme an!" << endl;

	token = scanner->nextToken();

	cout << "Komme immernoch an!   -->" << token->type<< endl;
	if(!(token->type == ';')){
		cerr << "Semikolon fehlt in Zeile: " << token->line << " Spalte: " << token->column;
		semicolon = 0;
	}else{
		cout << "Semikolon vorhanden" << endl;
	}

	if(semicolon){  	// Wenn ein Semicolon vorhanden ist, dann wird dieser Teil ausgeführt.
		this->decls = new Decls(scanner);
	}
}

Decl::Decl(Scanner* scanner) {
	token = scanner->nextToken();
	if (token->symTab->ttype == 7){	//Wenn nächstes Token ist 'int'(7), dann schau nach Array
		this->array = new Array(scanner);
	}
	if (!(this->array->exists)){
		this->array = NULL;

	}else{
		token = scanner->nextToken();
	}
	cout << "DEBUG:"<<token->type << endl;
	if (token->type == 8){	//Identifier (8) muss danach kommen -> ttype entspricht
		this->exists = true;
		cout<<"DECL existiert"<< endl;
	}else{
		cerr << "";
	}
}

Array::Array(Scanner* scanner) {
	token = scanner->nextToken();
	cout << "DEBUG:"<<token->type << endl;
	if (token->type == '['){	//Eckige Klammer auf muss zuerst da sein
		token = scanner->nextToken();
		if (token->type == 9){  //Integer (Zahl) muss danach kommen -> ttype entspricht state_digit = 9
			token = scanner->nextToken();
			if (token->type == ']'){	//Eckige Klammer zu am Schluss
				this->exists = true;
				cout << "Array existiert" << endl;
			}else{
				cerr <<"Expect ']' in line " << token->line << " column " << token->column;
			}
		}else{
			cerr << "Fehlender Arrayindex! in line " << token->line << " column " << token->column;
		}

	}else if (token->type == 8){	//Wenn Token nach int(Array könnte auch leer sein) ein identifier(8) ist, dann existiert kein array.
		this->exists = false;
		cout << "Array existiert nicht" << endl;
	}else{
		cerr << "Identifier fehlt in Zeile: " << token->line << " Spalte: " << token->column;
	}
}




Statements::Statements(Scanner* scanner) {
}

Statement::Statement(Scanner* scanner) {
}

Exp::Exp(Scanner* scanner) {
}

Exp2::Exp2(Scanner* scanner) {
}

Index::Index(Scanner* scanner) {
}

Op_exp::Op_exp(Scanner* scanner) {
}

Op::Op(Scanner* scanner) {
}
