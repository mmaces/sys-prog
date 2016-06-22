#include "../includes/Parser.h"



Parser::Parser(char* file){
	scanner = new Scanner(file);
};

int Parser::parse(){
	try{
		cout << "Parsing..." << endl;
		Prog* prog = new Prog(scanner);
		if(prog->status == -1){
			throw -1;
		}
		else if(prog->status == 0){
			throw 0;
		}
	}
	catch(int f)
	{
		return -1;
	}



}


Prog::Prog(Scanner* scanner){
//TODO: read write nur klein ?
	try{
		this->decls = new Decls(scanner);
		if(this->decls->status == -1){	//Wenn DECLS fehlerhaft
			throw -1;
		}
		else if(this->decls->status == 0){	//Wenn DECLS leer oder erstes Token kein int
			this->decls == NULL;
		}
		if(this->decls->decl->status == 1){	//Wenn DECLS bzw. DECL vorhanden
			cout << "DECLS" << endl;
		}
		cout << "Beginne mit Statements mit Tokeninhalt " << scanner->token->inhalt << endl;
		this->statements = new Statements(scanner);
		if(this->statements->status == -1){
			throw -1;
		}
		else if(this->statements->status == 0){
			this->statements == NULL;
		}
		else{
			this->statements->status = 1;
			cout << "STATEMENTS" << endl;
		}
	}
	catch(int f)
	{
		this->status = -1;
	}
}

Decls::Decls(Scanner* scanner) {
	try{
		this->decl = new Decl(scanner);
		if(this->decl->status == -1){	//Wenn DECL fehlerhaft
			throw -1;
		}
		else if(this->decl->status == 1){	//Wenn DECL vorhanden
			this->token = scanner->nextToken();
			if(this->token->type == ';'){
				this->decls = new Decls(scanner);
				if(this->decls->status == 0){
					this->decls == NULL;
				}
				else if(this->decls->status == -1){
					throw -1;
				}
				else{
					this->status = 1;
					cout << "DECLS" << endl;
				}
			}
			else{
				cerr << "Unexpected token in line:" << this->token->line << " column: " << this->token->column << " " << this->token->type << endl;
				throw -1;
			}
		}
		else{	//Wenn DECL leer bzw. Programm nicht mit int anfängt
			this->status = 0;
			this->decl = NULL;
			scanner->ungetToken(this->token);	//DANGER ->geht vor erstes Token -> Dateianfang
		}
	}
	catch(int f)
	{
		this->status = -1;
	}

}


Decl::Decl(Scanner* scanner) {
	try{
		this->token = scanner->nextToken();	//Erstes Token
//DEBUG
//		cout << "Tokeninhalt: " << this->token->inhalt << endl;
//		this->token = scanner->nextToken();
//		cout << "Tokeninhalt: " << this->token->inhalt << endl;
//		scanner->ungetToken();
//		this->token = scanner->nextToken();
//		cout << "Tokeninhalt: " << this->token->inhalt << endl;
		if (this->token->symTab->ttype == 7){ //Wenn Token/Schlüsselwort int
			this->array = new Array(scanner);
			if (this->array->status == 1 || this->array->status == 0){ //Wenn ARRAY vorhanden oder leer
				this->token = scanner->nextToken();
				if (this->array->status == 0){	//Wenn ARRAY leer
					this->array = NULL;
				}
				if (this->token->symTab->ttype == 3 /*identifier*/){
					this->status = 1;
					cout << "DECL" << endl;
				}
				else{
					cerr << "Unexpected token in line:" << this->token->line << " column: " << this->token->column << " " << this->token->type << endl;
					throw -1;
				}
			}
			else if (this->array->status == -1){ //wenn ARRAY fehlerhaft
				throw -1;
			}
		}
		else{	//Wenn kein int
			this->status = 0;
		}
	}
	catch(int f){
		this->status = -1;
	}
}

Array::Array(Scanner* scanner) {
	try{
		this->token = scanner->nextToken();
		if (this->token->type == '['){	//Eckige Klammer auf muss zuerst da sein
			this->token = scanner->nextToken();
			if (this->token->type == 9){  //Integer (Zahl) muss danach kommen -> type entspricht state_digit = 9
				this->token = scanner->nextToken();
				if (this->token->type == ']'){	//Eckige Klammer zu am Schluss
					this->status = 1;
					cout << "ARRAY" << endl;
				}else{
					cerr << "Unexpected token in line:" << this->token->line << " column: " << this->token->column << " " << this->token->type << endl;
					throw -1;
				}
			}else{
				cerr << "Unexpected token in line:" << this->token->line << " column: " << this->token->column << " " << this->token->type << endl;
				throw -1;
			}
		}else{
			scanner->ungetToken(this->token);
			this->status = 0;//Ansonten ist Array leer
		}
	}
	catch (int f){
		this->status = -1;
	}
}

Statements::Statements(Scanner* scanner) {
	try{
		this->statement = new Statement(scanner);
		if(this->statement->status == -1){	//Wenn STATEMENT nicht vorhanden
			throw -1;
		}
		else if(this->statement->status == 1){	//Wenn STATEMENT vorhanden
			this->token = scanner->nextToken();
			if(this->token->type == ';'){
				this->statements = new Statements(scanner);
				if(this->statements->status == 0){	//Wenn STATEMENTS leer
					this->statements = NULL;
					this->status = 1;
					cout << "STATEMENTS" << endl;
				}
				else if(this->statements->status == -1){
					throw -1;
				}
				else{	//Wenn STATEMENTS vorhanden
					this->status = 1;
					cout << "STATEMENTS" << endl;
				}
			}
			else{
				cerr << "Unexpected token in line:" << this->token->line << " column: " << this->token->column << " " << this->token->type << endl;
				throw -1;
			}
		}
	}
	catch(int f){
		this->status = -1;
	}
}

Statement::Statement(Scanner* scanner) {
	try{
		this->token = scanner->nextToken();
		if(token->symTab->ttype == 3 /*identifier*/){	//Wenn identifier
			this->index = new Index(scanner);
			if(this->index->status == 1 || this->index->status == 0){	//Wenn INDEX da oder leer	//1 = Token vorhanden, 0 = Token nicht vorhanden, -1 = Token falsch
				this->token = scanner->nextToken();
				if(this->index->status == 0){ //Wenn INDEX leer
					this->index = NULL;
				}
				if(this->token->type == 13){ //Wenn :=
					this->exp = new Exp(scanner);
					if(this->exp->status == 1){	//Wenn EXP vorhanden
						this->status = 1;
						cout << "STATEMENT" << endl;
					}
					else{	//Wenn EXP nicht vorhanden oder leer
						throw -1;
					}
				}
				else{	//wenn Token nicht := ist
					cerr << "Unexpected token in line:" << this->token->line << " column: " << this->token->column << " " << this->token->type << endl;
					throw -1;
				}
			}
			else{	//Wenn INDEX fehlerhaft
				throw -1;
			}

		}
		else if(this->token->symTab->ttype == 4 /*write*/){	//Wenn write
			this->token = scanner->nextToken();
			if(this->token->type == '('){ //Wenn (
				this->exp = new Exp(scanner);
				if(this->exp->status == 1){	//Wenn EXP vorhanden
					this->token = scanner->nextToken();
					if(this->token->type == ')'){	//Wenn )
						this->status = 1;
						cout << "STATEMENT" << endl;
					}
					else{	//Wenn ) nicht vorhanden
						cerr << "Unexpected token in line:" << this->token->line << " column: " << this->token->column << " " << this->token->type << endl;
						throw -1;
					}
				}
				else{	//Wenn EXP nicht vorhanden oder fehlerhaft
					throw -1;
				}
			}
			else{	//Wenn ( nicht vorhanden
				cerr << "Unexpected token in line:" << this->token->line << " column: " << this->token->column << " " << this->token->type << endl;
				throw -1;
			}
		}
		else if(token->symTab->ttype == 5 /*read*/){	//Wenn read vorhanden
			this->token = scanner->nextToken();
			if (this->token->type == '('){	//Wenn ( vorhanden
				this->token = scanner->nextToken();
				if (this->token->symTab->ttype == 3 /*identifier*/){	//Wenn identifier vorhanden
					this->index = new Index(scanner);
					if(this->index->status == 1 || this->index->status == 0){	//Wenn INDEX vorhanden oder leer hole neues Token
						if(this->index->status == 0){	//Wenn INDEX leer
							this->index = NULL;
						}
						this->token = scanner->nextToken();
						if(this->token->type == ')'){	//Wenn ) vorhanden
							this->status = 1;
							cout << "STATEMENT" << endl;
						}
						else{	//Wenn ) nicht vorhanden
							cerr << "Unexpected token in line:" << this->token->line << " column: " << this->token->column << " " << this->token->type << endl;
							throw -1;
						}
					}
					else{	//Wenn INDEX fehlerhaft
						throw -1;
					}

				}
				else{	//Wenn identifier nicht vorhanden
					cerr << "Unexpected token in line:" << this->token->line << " column: " << this->token->column << " " << this->token->type << endl;
					throw -1;
				}
			}
			else{	//Wenn ( nicht vorhanden
				cerr << "Unexpected token in line:" << this->token->line << " column: " << this->token->column << " " << this->token->type << endl;
				throw -1;
			}
		}
		else if(token->type == '{'){	//Wenn { vorhanden
			this->statements = new Statements(scanner);
			if(this->statements->status == 1 || this->statements->status == 0){	//Wenn STATEMENTS vorhanden oder leer
				this->token = scanner->nextToken();
				if(this->token->type == '}'){	//Wenn } vorhanden
					this->status = 1;
					cout << "STATEMENTS" << endl;
				}
				else{	//Wenn } nicht vorhanden
					cerr << "Unexpected token in line:" << this->token->line << " column: " << this->token->column << " " << this->token->type << endl;
					throw -1;
				}
			}
			else{	//Wenn STATEMENTS fehlerhaft
				throw -1;
			}
		}
		else if(token->symTab->ttype == 2 /*IF*/){	//Wenn if vorhanden
			this->token = scanner->nextToken();
			if(this->token->type == '('){	//Wenn ( vorhanden
				this->exp = new Exp(scanner);
				if(this->exp->status == 1){	//Wenn EXP vorhanden
					this->token = scanner->nextToken();
					if(this->token->type == ')'){	//Wenn ) vorhanden
						this->statement = new Statement(scanner);
						if(this->statement->status == 1){	//Wenn STATEMENT vorhanden
							this->token = scanner->nextToken();
							if(this->token->symTab->ttype == 6 /*else*/){ //Wenn else vorhanden
								this->statement2 = new Statement(scanner);
								if(this->statement2->status == 1){	//Wenn zweites STATEMENT
									this->status = 1;
									cout << "STATEMENT" << endl;
								}
								else{	//Wenn zweites STATEMENT fehlerhaft oder leer
									throw -1;
								}
							}
							else{	//Wenn else nicht vorhanden
								cerr << "Unexpected token in line:" << this->token->line << " column: " << this->token->column << " " << this->token->type << endl;
								throw -1;
							}
						}
						else{	//Wenn STATEMENT fehlerhaft oder leer
							throw -1;
						}
					}
					else{	//Wenn ) nicht vorhanden
						cerr << "Unexpected token in line:" << this->token->line << " column: " << this->token->column << " " << this->token->type << endl;
						throw -1;
					}
				}
				else{	//Wenn EXP fehlerhaft oder leer
					throw -1;
				}
			}
			else{	//Wenn ( nicht vorhanden
				cerr << "Unexpected token in line:" << this->token->line << " column: " << this->token->column << " " << this->token->type << endl;
				throw -1;
			}
		}
		else if(token->symTab->ttype == 1 /*while*/){	//Wenn while vorhanden
			this->token = scanner->nextToken();
			if(this->token->type == '('){	//Wenn ( vorhanden
				this->exp = new Exp(scanner);
				if(this->exp->status == 1){	//Wenn EXP vorhanden
					this->token = scanner->nextToken();
					if(this->token->type == ')'){	//Wenn ) vorhanden
						this->statement = new Statement(scanner);
						if(this->statement->status == 1){	//Wenn STATEMENT vorhanden
							this->status = 1;
							cout << "STATEMENT" << endl;
						}
						else{	//Wenn STATEMENT nicht vorhanden oder leer
							throw -1;
						}
					}
					else{	//Wenn ) nicht vorhanden
						cerr << "Unexpected token in line:" << this->token->line << " column: " << this->token->column << " " << this->token->type << endl;
						throw -1;
					}
				}
				else{	//Wenn EXP nicht vorhanden oder leer
					throw -1;
				}
			}
			else{	//Wenn ( nicht vorhanden
				cerr << "Unexpected token in line:" << this->token->line << " column: " << this->token->column << " " << this->token->type << endl;
				throw -1;
			}
		}
		{	//Wenn nichts passendes für Statement vorhanden
			cerr << "Unexpected token in line:" << this->token->line << " column: " << this->token->column << " " << this->token->type << endl;
			throw -1;
		}
	}
	catch(int f){
		this->status = -1;
	}
}

Exp::Exp(Scanner* scanner) {
	try{
		this->exp2 = new Exp2(scanner);
		if(this->exp2->status == 1){	//Wenn EXP2 vorhanden
			this->op_exp = new Op_exp(scanner);
			if(this->op_exp->status == 0 || this->op_exp->status == 1){	//Wenn OP_EXP vorhanden oder leer
				if(this->op_exp->status == 0){
					this->op_exp = NULL;
				}
				cout << "EXP" << endl;
				this->status = 1;
			}
			else{	//Wenn OP_EXP fehlerhaft
				throw -1;
			}
		}
		else{	//Wenn EXP2 fehlerhaft oder leer
			throw -1;
		}
	}
	catch(int f){
		this->status = -1;
	}
}

Exp2::Exp2(Scanner* scanner) {
	try{
		this->token = scanner->nextToken();
		if(this->token->type == '('){	//Wenn ( vorhanden
			this->exp = new Exp(scanner);
			if(this->exp->status == 1){	//Wenn EXP vorhanden
				this->token = scanner->nextToken();
				if(this->token->type == ')'){	//Wenn ) vorhanden
					this->status = 1;
					cout << "EXP2" << endl;
				}
				else{	//Wenn ) nicht vorhanden
					cerr << "Unexpected token in line:" << this->token->line << " column: " << this->token->column << " " << this->token->type << endl;
					throw -1;
				}
			}
			else{	//Wenn EXP fehlerhaft oder leer
				throw -1;
			}
		}
		else if(this->token->type == 8 /*identifier*/){
			this->index = new Index(scanner);
			if(this->index->status == 0 || this->index->status == 1){	//Wenn INDEX leer oder vorhanden
				this->status = 1;
				cout << "EXP2" << endl;
			}
			if(this->index->status == -1){	//Wenn INDEX fehlerhaft
				throw -1;
			}

		}
		else if(this->token->type == 9){  //Integer (Zahl) muss danach kommen -> type entspricht state_digit = 9
			this->status = 1;
			cout << "EXP2" << endl;
		}
		else if(this->token->type == '-' || this->token->type == '!'){	//Wenn - oder !
			this->exp2 = new Exp2(scanner);
			if(this->exp2->status == 1){	//Wenn EXP2 vorhanden
				this->status = 1;
				cout << "EXP2" << endl;
			}
			else{	//Wenn EXP2 leer oder nicht vorhanden
				throw -1;
			}
		}
		else{	//Wenn kein passendes Beginnertoken für EXP2
			cerr << "Unexpected token in line:" << this->token->line << " column: " << this->token->column << " " << this->token->type << endl;
			throw -1;
		}
	}
	catch(int f){
		this->status = -1;
	}
}

Index::Index(Scanner* scanner){
	try{
		this->token = scanner->nextToken();
		if(this->token->type == '['){	//Wenn [ vorhanden
			this->exp = new Exp(scanner);
			if(this->exp->status == 1){	//Wenn EXP vorhanden
				this->token = scanner->nextToken();
				if(this->token->type == ']'){	//Wenn ] vorhanden
					this->status = 1;
					cout << "INDEX" << endl;
				}
				else{	//Wenn ] nicht vorhanden
					cerr << "Unexpected token in line:" << this->token->line << " column: " << this->token->column << " " << this->token->type << endl;
					throw -1;
				}
			}
			else{	//Wenn EXP fehlerhaft oder leer
				throw -1;
			}
		}
		else if(Index::isOperandOrDDE(this->token)){	//Wenn aktuelles Token nicht [, sondern OP oder := ist
			this->status = 0;
			scanner->ungetToken(this->token);
		}
		else{	//Wenn kein OP oder := oder [
			cerr << "Unexpected token in line:" << this->token->line << " column: " << this->token->column << " " << this->token->type << endl;
			throw -1;
		}
	}
	catch(int f){
		this->status = -1;
	}
}

Op_exp::Op_exp(Scanner* scanner) {
	try{
		this->op = new Op(scanner);
		if(this->op->status == 1){	//Wenn OP vorhanden
			this->exp = new Exp(scanner);
			if(this->exp->status == 1){	//Wenn EXP vorhanden
				this->status = 1;
				cout << "OP_EXP" << endl;
			}
			else{	//Wenn EXP fehlerhaft oder nicht vorhanden
				throw -1;
			}
		}
		else{	//Wenn OP fehlerhaft oder leer
			throw -1;
		}
	}
	catch(int f){
		this->status = -1;
	}
}

Op::Op(Scanner* scanner) {
	try{
		this->token = scanner->nextToken();
		if(Op::isOperand(this->token)){	//Wenn Operand vorhanden
			this->status = 1;
			cout << "OP" << endl;
		}
		//Ausnahmefälle behandeln!!! Wenn OP leer usw.
		else{
			cerr << "Unexpected token in line:" << this->token->line << " column: " << this->token->column << " " << this->token->type << endl;
			throw -1;
		}
	}
	catch(int f){
		this->status = -1;
	}
}
bool Op::isOperand(Token* tk){
	int t = tk->type;
	if (t == '+' || t == '-' || t == '*' ||  t == ':' || t == '<' || t == '>' || t == '=' || t == 16 /*EqualDoubleDotEqual*/ || t == 19 /*AndAnd*/){
		return true;
	}
	else{
		return false;
	}
}
bool Index::isOperandOrDDE(Token* tk){
	int t = tk->type;
	if (t == '+' || t == '-' || t == '*' ||  t == ':' || t == '<' || t == '>' || t == '=' || t == 13 /*DoubleDotEqual*/ || t == 16 /*EqualDoubleDotEqual*/ || t == 19 /*AndAnd*/){
		return true;
	}
	else{
		return false;
	}
}
//TODO: Code wie ( oder Operanden speichern
//TODO: Auf cerr für Dateiende nach jedem nextToken prüfen
//TODO: In Symboltabelle Standardwert für ttype
//TODO: objekte mit NULL initialisieren
