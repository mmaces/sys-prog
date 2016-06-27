#include "../includes/Parser.h"
#include <cstdlib>

/** Status sind die alternativen!
 *
 **/

enum varType{
	noType,
	intType,
	intArrayType,
	arrayType,
	opPlus,
	opMinus,
	opMult,
	opDiv,
	opLess,
	opGreater,
	opEqual,
	opUnEqual,
	opAndAnd,
	errorType
} vType;

Parser::Parser(char* file){
	scanner = new Scanner(file);
	prog = new Prog(scanner);
};

int Parser::parse(){
	try{
		cout << "Parsing..." << endl;

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
// Haupt typeCheck: Diese Methode wird aufgerufen um den kompletten Baum auf semantische Korrektheit zu prüfen
void Parser::typeCheckProg(Prog* prog){
	cout << "PROG typecheck begin" << endl;
	typeCheckDecls(prog->decls);
	typeCheckStatements(prog->statements);
	prog->type = noType;
}

void Parser::typeCheckDecl(Decl* decl){
	typeCheckArray(decl->array);
	if(decl->token->symTab->varType!=noType){ // Vielleicht flasch?
		cerr<<"identifier already defined"<< endl;
		decl->status = errorType;
	}else if(decl->array->type == errorType){
		decl->type = errorType;
	}else{
		decl->type = noType;
		if(decl->array->type == arrayType){
			decl->token->symTab->varType = intArrayType;
		}else{
			decl->token->symTab->varType = intType;
		}
	}
	cout << "typecheck: identifier " << decl->token->inhalt<<" array integer: " << strtol(decl->array->token->inhalt,NULL,10) <<endl;
}

void Parser::typeCheckDecls(Decls* decls){
	if(decls->status != 0){
		typeCheckDecl(decls->decl);
		typeCheckDecls(decls->decls);
	}
	decls->type = noType;
}

void Parser::typeCheckArray(Array* array){

	if(array->status != 0){
		if(strtol(array->token->inhalt,NULL,10) >0){
			array->type = arrayType;
		}else{
			cerr<<"no valid dimension"<<endl;
			array->type = errorType;
		}
	}else{
		array->type = noType;
	}
}

void Parser::typeCheckStatements(Statements* statements){
	if(statements->status != 0){
		typeCheckStatement(statements->statement);
		typeCheckStatements(statements->statements);
	}
	statements->type = noType;
}
// status klären !!! Der status sind die verschiedenen Varianten der Mehtode auf den Folien
void Parser::typeCheckStatement(Statement* statement){
	if(statement->status == 0){
		typeCheckExp(statement->exp);
		typeCheckIndex(statement->index);

		int identType = statement->token->symTab->varType;

		if(identType == noType){
			cerr << "identifier not defined" << endl;
			statement->type = errorType;
		}else if((statement->exp->type == intType)
				&& ((identType == intType && statement->index->type == noType)
				|| (identType == intArrayType && statement->index->type == arrayType))){
			statement->type = noType;
		}else{
			cerr << "incompatible types" << endl;
			statement->type = errorType;
		}
	}else if(statement->status == 1){
		typeCheckExp(statement->exp);
		statement->type = noType;
	}else if(statement->status == 2){
		typeCheckIndex(statement->index);

		if(statement->token->symTab->varType == noType){
			cerr << "identifier not defined" << endl;
			statement->type = errorType;
		}else if(((statement->token->symTab->varType == intType) && statement->index->type == noType) || ((statement->token->symTab->varType == intArrayType) && statement->index->type == arrayType)){
			statement->type = noType;
		}else{
			cerr << "incompatible types" <<endl;
			statement->type = errorType;
		}
	}else if(statement->status == 3){
		typeCheckStatements(statement->statements);
		statement->type = noType;
	}else if(statement->status == 4){
		typeCheckExp(statement->exp);
		typeCheckStatement(statement->statement);
		typeCheckStatement(statement->statement2);

		if(statement->exp->type == errorType){
			statement->type = errorType;
		}else{
			statement->type = noType;
		}
	}else if(statement->status == 5){
		typeCheckExp(statement->exp);
		typeCheckStatement(statement->statement);

		if(statement->exp == errorType){
			statement->type = errorType;
		}else{
			statement->type = noType;
		}
	}
}
void Parser::typeCheckIndex(Index* index){
	if(index->status != 0){
		typeCheckExp(index->exp);

		if(index->exp->type == errorType){
			index->type = errorType;
		}else{
			index->type = arrayType;
		}
	}else{
		index->type = noType;
	}
}
void Parser::typeCheckExp(Exp* exp){
	typeCheckExp2(exp->exp2);
	typeCheckOp_Exp(exp->op_exp);

	if(exp->op_exp->type == noType){
		exp->type = exp->exp2->type;
	}else if(exp->exp2->type != exp->op_exp->type){
		exp->type = errorType;
	}else{
		exp->type = exp->exp2->type;
	}
}

void Parser::typeCheckExp2(Exp2* exp2){ // status muss geklärt werden!!!! siehe statement!
	if(exp2->status == 1){
		typeCheckExp(exp2->exp);
		exp2->type = exp2->exp->type;
	}else if(exp2->status == 2){
		typeCheckIndex(exp2->index);
		if(exp2->token->symTab->varType == noType){
			cerr << "identifier not defined" << endl;
			exp2->type = errorType;
		}else if((exp2->token->symTab->varType == intType) && (exp2->index->type == noType)){
			exp2->type = exp2->token->symTab->varType;
		}else if((exp2->token->symTab->varType == intArrayType) && (exp2->index->type == arrayType)){
			exp2->type = intType;
		}else{
			cerr << "no primitive Type" << endl;
			exp2->type = errorType;
		}
	}else if(exp2->status == 3){
		exp2->type = intType;
	}else if(exp2->status == 4){
		typeCheckExp2(exp2->exp2);
		exp2->type = exp2->exp2->type;
	}else if(exp2->status == 5){
		typeCheckExp2(exp2->exp2);
		if(exp2->exp2->type != intType){
			exp2->type = errorType;
		}else{
			exp2->type = intType;
		}
	}
}

void Parser::typeCheckOp_Exp(Op_exp* op_exp){
	if(op_exp->status != 0){
		typeCheckOp(op_exp->op);
		typeCheckExp(op_exp->exp);
		op_exp->type = op_exp->exp->type;
	}else{
		op_exp->type = noType;
	}
}

void Parser::typeCheckOp(Op* op){
	if(strcmp(op->token->inhalt,"+") != 0){
		op->type = opPlus;
	}else if(strcmp(op->token->inhalt,"-") != 0){
		op->type = opMinus;
	}else if(strcmp(op->token->inhalt,"*") != 0){
		op->type = opMult;
	}else if(strcmp(op->token->inhalt,":") != 0){
		op->type = opDiv;
	}else if(strcmp(op->token->inhalt,"<") != 0){
		op->type = opLess;
	}else if(strcmp(op->token->inhalt,">") != 0){
		op->type = opGreater;
	}else if(strcmp(op->token->inhalt,"=") != 0){
		op->type = opEqual;
	}else if(strcmp(op->token->inhalt,"=:=") != 0){
		op->type = opUnEqual;
	}else if(strcmp(op->token->inhalt,"&&") != 0){
		op->type = opAndAnd;
	}
}

Prog::Prog(Scanner* scanner){
//TODO: read write nur klein ?
	try{
		this->decls = new Decls(scanner);
		if(this->decls->status == -1){	//Wenn DECLS fehlerhaft
			throw -1;
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
		}else if(this->decl->status == 1){	//Wenn DECL vorhanden
			this->token = scanner->nextToken();
			if(this->token->type == ';'){
				this->decls = new Decls(scanner);
			}else if(this->decls->status == -1){
				cerr<<"Unexpected token in line: " <<this->token->line <<" column: "<<this->token->column <<" "<< this->token->type <<endl;
				throw -1;
			}else{
				this->status = 1;
				cout << "DECLS" << endl;
			}
		}else{	//Wenn DECL leer bzw. Programm nicht mit int anfängt
			this->status = 0;
			this->decl = NULL;
			this->token = scanner->token;
			scanner->ungetToken(this->token);	//DANGER ->geht vor erstes Token -> Dateianfang
		}
	}catch(int f){
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
		if (this->token->type == 8 && this->token->symTab->ttype == 7){ //Wenn Token/Schlüsselwort int
			this->array = new Array(scanner);
			if (this->array->status == 1 || this->array->status == 0){ //Wenn ARRAY vorhanden oder leer
				this->token = scanner->nextToken();

				if (this->token->type == 8 && this->token->symTab->ttype == 3 /*identifier*/){	//Wenn identifier in Tokentype und symtab
					this->token = scanner->token;
					if(this->array == NULL){
						this->token->symTab->varType = intType;
					}
					else{
						this->token->symTab->varType = intArrayType;
					}
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
				Token* token_tmp = token;
				this->token = scanner->nextToken();
				if (this->token->type == ']'){	//Eckige Klammer zu am Schluss
					this->status = 1;
					token = token_tmp;
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
			this->token = scanner->token;
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
		if(this->statement->status == -1){	//Wenn STATEMENT fehlerhaft
			throw -1;
		}
		else if(this->statement->status == 1){	//Wenn STATEMENT vorhanden
			this->token = scanner->nextToken();
			if(this->token->type == ';'){
				//scanner->ungetToken(this->token)
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
			else{//Wenn kein ;
				cerr << "Unexpected token in line:" << this->token->line << " column: " << this->token->column << " " << this->token->type << endl;
				throw -1;
//				this->token = scanner->token;
//				this->status = 0;
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
		if(this->token->type == 8 && token->symTab->ttype == 3 /*identifier*/){	//Wenn identifier
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
		else if(this->token->type == 8 && this->token->symTab->ttype == 4 /*write*/){	//Wenn write
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
		else if(this->token->type == 8 && token->symTab->ttype == 5 /*read*/){	//Wenn identifier und der ist read vorhanden
			this->token = scanner->nextToken();
			if (this->token->type == '('){	//Wenn ( vorhanden
				this->token = scanner->nextToken();
				if (this->token->type == 8 && this->token->symTab->ttype == 3 /*identifier*/){	//Wenn identifier und identifier in symtab vorhanden
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
		else if(this->token->type == 8 && token->symTab->ttype == 2 /*IF*/){	//Wenn if vorhanden
			this->token = scanner->nextToken();
			if(this->token->type == '('){	//Wenn ( vorhanden
				this->exp = new Exp(scanner);
				if(this->exp->status == 1){	//Wenn EXP vorhanden
					this->token = scanner->nextToken();
					if(this->token->type == ')'){	//Wenn ) vorhanden
						this->statement = new Statement(scanner);
						if(this->statement->status == 1){	//Wenn STATEMENT vorhanden
							this->token = scanner->nextToken();
							if(this->token->type == 8 && this->token->symTab->ttype == 6 /*else*/){ //Wenn Token = identifier und ist else vorhanden
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
		else if(this->token->type == 8 && token->symTab->ttype == 1 /*while*/){	//Wenn Token ist identifier und ist while vorhanden
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
		else{	//Wenn nichts passendes für Statement vorhanden gehe von leer aus
			this->token = scanner->token;
			scanner->ungetToken(this->token);
			this->status = 0;
			//			cerr << "Unexpected token in line:" << this->token->line << " column: " << this->token->column << " " << this->token->type << endl;
			//			throw -1;
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
		else{	//Wenn aktuelles Token nicht [ ist, dann gehe davon aus, dass ARRAY leer
			this->status = 0;
			this->token = scanner->token;
			scanner->ungetToken(this->token);
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
		else if(this->op->status == 0){	//Wenn OP leer, dann OP_EXP leer
			this->status = 0;
			//scanner->ungetToken(this->token);
		}
		else{	//Wenn OP fehlerhaft
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
		else{	//Wenn etwas anderes als Operand, dann gehe davon aus, dass Operand leer bzw. dass daher auch OP_EXP leer
			this->status = 0;
			this->token = scanner->token;
			scanner->ungetToken(this->token);
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
