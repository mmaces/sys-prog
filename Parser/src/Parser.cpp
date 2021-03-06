


/*
 * FRAGEN
 * - Soll man im Typcheck beim ersten Fehler aufhören?
 * - Muss Zeile und Spalte beim ersten Typecheck Fehler angegeben werden wie bei Tree auch?
 * - Brauch man ein Stop beim Typecheck?
 * - Gilt der Zeilenfehler vom Scanner auch nochmal hier!????? O.O
 * column - (d - ((number == 1)? 0 : number) - ((currentState == 12 || currentState == 14)? 2 : 0))
 *
 */





#include "../includes/Parser.h"
#include <cstdlib>
#include <cstring>

enum varType{
	noType = 0,
	intType = 1,
	intArrayType = 2,
	arrayType = 3,
	opPlus = 4,
	opMinus = 5,
	opMult = 6,
	opDiv = 7,
	opLess = 8,
	opGreater = 9,
	opEqual = 10,
	opUnEqual = 11,
	opAndAnd = 12,
	errorType = 13
} varType;

enum state2 {
		Identifier = 8,
		Digit = 9,
		DoubleDot = 11,
		DoubleDotStar = 12,
		DoubleDotEqual = 13,
		StarDoubleDot = 14,
		Star = 15,
		EqualDoubleDotEqual = 16,
		Equal = 17,
		AndAnd = 19,
		Plus = '+',
		Minus = '-',
		SmallerThan = '<',
		BiggerThan = '>',
		ExclamationMark = '!',
		Semicolon = ';',
		ParanthesesOpen = '(',
		ParanthesesClose = ')',
		BraceOpen = '{',
		BraceClose = '}',
		BracketOpen = '[',
		BracketClose = ']'
} state2;

Parser::Parser(char* file){
	scanner = new Scanner(file);
	fs.open("out.txt",ios::out);
	label1 = 1;
	label2 = 2;
	label3 = 3;
	label4 = 4;
};


Parser::~Parser(){
	fs.close();
	delete prog;
}

Prog::~Prog(){
	if (this->status){
	delete decls;
	delete statements;
	}
}

Decls::~Decls(){
	if (this->status){
		delete decl;
		delete decls;
	}
}

Decl::~Decl(){
	if (this->status)
		delete array;
}

Array::~Array(){
	if (this->status)
		delete token;
}
Statements::~Statements(){
	if (this->status){
		delete statement;
	delete statements;
	}
}

Statement::~Statement(){
	if (this->status)
		delete index;
	if (this->status)
		delete exp;
	if (this->status)
		delete statements;
	if (this->status)
		delete statement;:
}

Exp::~Exp(){
	if (this->status){
		delete exp2;
		delete op_exp;
	}
}

Exp2::~Exp2(){
	if (this->status)
		delete exp;
	if (this->status)
		delete index;
	if (this->status)
		delete exp2;
}

Index::~Index(){
	if (this->status)
delete exp;
}

Op_exp::~Op_exp(){
	if (this->status){
		delete op;
	delete exp;
	}
}

Op::~Op(){
delete this->token;
}

int Parser::parse(){
	try{
			cout << "Parsing..." << endl;
			this->prog = new Prog(scanner);
			if(prog->status == -1){
				throw -1;
			}
			else if(prog->status == 0){
				throw 0;
			}
		}
		catch(int f)
		{
			return f;
		}
}

/**
 * make Code
 */
void Parser::makeCodeProg(){
	makeCodeDecls(this->prog->decls);
	makeCodeStatements(this->prog->statements);
	fs<<"STP"<<endl;
}
void Parser::makeCodeDecls(Decls* decls){
	if(decls->status != 0){
		makeCodeDecl(decls->decl);
	}
	if(decls->decls->status != 0){
		makeCodeDecls(decls->decls);
	}
}
void Parser::makeCodeDecl(Decl* decl){
	fs<<"DS "<<"$"<<decl->inhalt;
	if(decl->array->status != 0){
		fs<<" "<<atoi(decl->array->inhalt)<<endl;;
	}else{
		fs<<" "<<1<<endl;
	}
}

void Parser::makeCodeStatements(Statements* statements){
	if(statements->status != 0){
		makeCodeStatement(statements->statement);
		makeCodeStatements(statements->statements);
	}else{
		fs<<"NOP"<<endl;
	}
}

void Parser::makeCodeStatement(Statement* statement){
	int localLabel1 = label1;
	int localLabel2 = label2;
	int localLabel3 = label3;
	int localLabel4 = label4;
	label1+=4;
	label2+=4;
	label3+=4;
	label4+=4;

	if(statement->status == 2){ // write
		makeCodeExp(statement->exp);
		fs << "PRI"<<endl;
	}
	else if(statement->status == 3){//read
		fs << "REA"<<endl;
		fs << "LA " << "$" << statement->inhalt<<endl;
		makeCodeIndex(statement->index);
		fs << "STR"<<endl;
	}
	else if(statement->status == 5){//if
		makeCodeExp(statement->exp);
		fs << "JIN "<< "#" << "akr"<<localLabel1<<endl; // Label 1 ???????
		makeCodeStatement(statement->statement);
		fs << "JMP "<< "#" << "akr"<<localLabel2<<endl; // Label 2 ???????
		fs<<"#"<<"akr"<<localLabel1<<" NOP"<<endl;
		makeCodeStatement(statement->statement2);
		fs<<"#"<<"akr"<<localLabel2 <<" NOP"<<endl;
	}
	else if(statement->status == 6){//while
		fs << "#" << "akr"<<localLabel3 << " NOP"<<endl; // Label 1 ???????
		makeCodeExp(statement->exp);
		fs << "JIN "<< "#" << "akr"<<localLabel4<<endl; // Label 1 ???????
		makeCodeStatement(statement->statement);
		fs<<"JMP " << "#"<<"akr"<<localLabel3<<endl;
		fs<<"#"<<"akr"<<localLabel4 <<" NOP"<<endl;
	}
	else if(statement->status == 1){ // identifier
		makeCodeExp(statement->exp);
		fs<<"LA "<<"$" << statement->inhalt<<endl;
		makeCodeIndex(statement->index);
		fs << "STR"<<endl;
	}
	else if(statement->status == 4){
		makeCodeStatements(statement->statements);
	}

}

void Parser::makeCodeExp(Exp* exp){
	if(exp->op_exp->type == noType){
		makeCodeExp2(exp->exp2);
	}else if(exp->op_exp->op->type == opGreater){
		makeCodeOp_Exp(exp->op_exp);
		makeCodeExp2(exp->exp2);
		fs<<"LES"<<endl;
	}else if(exp->op_exp->op->type == opUnEqual){
		makeCodeExp2(exp->exp2);
		makeCodeOp_Exp(exp->op_exp);
		fs << "NOT"<<endl;
	}else{
		makeCodeExp2(exp->exp2);
		makeCodeOp_Exp(exp->op_exp);
	}
}

void Parser::makeCodeIndex(Index* index){
	if(index->status != 0){
		makeCodeExp(index->exp);
		fs << "ADD"<<endl;
	}else{
		//nichts machen
	}
}

void Parser::makeCodeExp2(Exp2* exp2){
	if(exp2->status == 1){
		makeCodeExp(exp2->exp);
	}else if(exp2->status == 2){// 8 = identifier
		fs<<"LA " << "$" << exp2->inhalt<<endl;
		makeCodeIndex(exp2->index);:
		fs<<"LV"<<endl;
	}else if(exp2->status == 3){// 9 = integer
		fs<<"LC " <<atoi(exp2->inhalt)<<endl;
	}else if(exp2->status == 4){
		fs<<"LC "<< 0<<endl;
		makeCodeExp2(exp2-:>exp2);
		fs<<"SUB"<<endl;
	}else if(exp2->status == 5){
		makeCodeExp2(exp2->exp2);
		fs<<"NOT" <<endl;
	}

}

void Parser::makeCodeOp_Exp(Op_exp* op_exp){
	if(op_exp->status != 0){
		makeCodeExp(op_exp->exp);
		makeCodeOp(op_exp->op);
	}else{
		//nichts
	}
}

void Parser::makeCodeOp(Op* op){
	if(op->token->type == '+'){
		fs<<"ADD"<<endl;
	}
	else if(op->token->type == '-'){
		fs<<"SUB"<<endl;
	}
	else if(op->token->type == Star){
		fs<<"MUL"<<endl;
	}
	else if(op->token->type == DoubleDot){
		fs<<"DIV"<<endl;
	}
	else if(op->token->type == '<'){
		fs<<"LES"<<endl;
	}
	else if(op->token->type == '>'){

	}
	else if(op->token->type == Equal){
		fs<<"EQU"<<endl;
	}
	else if(op->token->type == EqualDoubleDotEqual){// =:=
		fs<<"EQU"<<endl;
	}
	else if(op->token->type == AndAnd){ // &&
		fs<<"AND"<<endl;
	}
}



/** Status sind die alternativen!
 *
 **/
// Haupt typeCheck: Diese Methode wird aufgerufen um den kompletten Baum auf semantische Korrektheit zu prüfen
void Parser::typeCheckProg(){
	typeCheckDecls(this->prog->decls);
	typeCheckStatements(this->prog->statements);
	this->prog->type = noType;
}
// typeCheck: DECL
void Parser::typeCheckDecl(Decl* decl){
	typeCheckArray(decl->array);
	if(scanner->symTab->insert(decl->inhalt)->varType!=noType){
		cerr<<"identifier already defined"<< endl;
		decl->type = errorType;
	}else if(decl->array->type == errorType){
		decl->type = errorType;
	}else{
		decl->type = noType;
		if(decl->array->type == arrayType){
			scanner->symTab->insert(decl->inhalt)->varType = intArrayType;
			//decl->varType = intArrayType;
		}else{
			scanner->symTab->insert(decl->inhalt)->varType = intType;
			//decl->varType = intType;
		}
	}
}
// typeCheck: DECLS
void Parser::typeCheckDecls(Decls* decls){
	if(decls->status != 0){
		typeCheckDecl(decls->decl);
		typeCheckDecls(decls->decls);
	}
	decls->type = noType;
}
// typeCheck: ARRAY
void Parser::typeCheckArray(Array* array){

	if(array->status != 0){
		if(strtol(array->inhalt,NULL,10) >0){
			array->type = arrayType;
		}else{
			cerr<<"no valid dimension"<<endl;
			array->type = errorType;
		}
	}else{
		array->type = noType;
	}
}
// typeCheck: STATEMENTS
void Parser::typeCheckStatements(Statements* statements){
	if(statements->status != 0){
		typeCheckStatement(statements->statement);
		typeCheckStatements(statements->statements);
	}
	statements->type = noType;
}
// typeCheck: STATEMENT
void Parser::typeCheckStatement(Statement* statement){
	if(statement->status == 1){
		typeCheckExp(statement->exp);
		typeCheckIndex(statement->index);

		int identType = statement->exp->type;

		if(scanner->symTab->insert(statement->inhalt)->varType == noType){
			cerr << "identifier not defined" << endl;
			statement->type = errorType;
		}else if((statement->exp->type == intType)
				&& ((scanner->symTab->insert(statement->inhalt)->varType == intType && statement->index->type == noType)
				|| (scanner->symTab->insert(statement->inhalt)->varType == intArrayType && statement->index->type == arrayType))){
			statement->type = noType;
		}else{
			cerr << "incompatible types" << endl;
			statement->type = errorType;
		}
	}else if(statement->status == 2){
		typeCheckExp(statement->exp);
		statement->type = noType;
	}else if(statement->status == 3){
		typeCheckIndex(statement->index);

		if(scanner->symTab->insert(statement->inhalt)->varType == noType){
			cerr << "identifier not defined" << endl;
			statement->type = errorType;
		}else if(((scanner->symTab->insert(statement->inhalt)->varType == intType) && statement->index->type == noType)
			|| ((scanner->symTab->insert(statement->inhalt)->varType == intArrayType) && statement->index->type == arrayType)){
		    	
		    	statement->type = noType;
		}else{
			cerr << "incompatible types" <<endl;
			statement->type = errorType;
		}
	}else if(statement->status == 4){
		typeCheckStatements(statement->statements);
		statement->type = noType;
	}else if(statement->status == 5){
		typeCheckExp(statement->exp);
		typeCheckStatement(statement->statement);
		typeCheckStatement(statement->statement2);

		if(statement->exp->type == errorType){
			statement->type = errorType;
		}else{
			statement->type = noType;
		}
	}else if(statement->status == 6){
		typeCheckExp(statement->exp);
		typeCheckStatement(statement->statement);

		if(statement->exp->type == errorType){
			statement->type = errorType;
		}else{
			statement->type = noType;
		}
	}
}
// typeCheck: INDEX
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
// typeCheck: EXP
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
// typeCheck: EXP2
void Parser::typeCheckExp2(Exp2* exp2){ // status muss geklärt werden!!!! siehe statement!
	if(exp2->status == 1){
		typeCheckExp(exp2->exp);
		exp2->type = exp2->exp->type;
	}else if(exp2->status == 2){
		typeCheckIndex(exp2->index);
		if(scanner->symTab->insert(exp2->inhalt)->varType == noType){
			cerr << "identifier not defined" << endl;
			exp2->type = errorType;
		}else if((scanner->symTab->insert(exp2->inhalt)->varType == intType) && (exp2->index->type == noType)){
			exp2->type = scanner->symTab->insert(exp2->inhalt)->varType;
		}else if((scanner->symTab->insert(exp2->inhalt)->varType == intArrayType) && (exp2->index->type == arrayType)){
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
// typeCheck: OP_EXP
void Parser::typeCheckOp_Exp(Op_exp* op_exp){
	if(op_exp->status != 0){
		typeCheckOp(op_exp->op);
		typeCheckExp(op_exp->exp);
		op_exp->type = op_exp->exp->type;
	}else{
		op_exp->type = noType;
	}
}
// typeCheck: OP
void Parser::typeCheckOp(Op* op){
	if(strcmp(op->inhalt,"+") == 0){
		op->type = opPlus;
	}else if(strcmp(op->inhalt,"-") == 0){
		op->type = opMinus;
	}else if(strcmp(op->inhalt,"*") == 0){
		op->type = opMult;
	}else if(strcmp(op->inhalt,":") == 0){
		op->type = opDiv;
	}else if(strcmp(op->inhalt,"<") == 0){
		op->type = opLess;
	}else if(strcmp(op->inhalt,">") == 0){
		op->type = opGreater;
	}else if(strcmp(op->inhalt,"=") == 0){
		op->type = opEqual;
	}else if(strcmp(op->inhalt,"=:=") == 0){
		op->type = opUnEqual;
	}else if(strcmp(op->inhalt,"&&") == 0){
		op->type = opAndAnd;
	}
}


Prog::Prog(Scanner* scanner){
//TODO: read write nur klein ?
	try{
		this->decls = new Decls(scanner);	//Baue DECLS
		if(this->decls->status == -1){	//Wenn DECLS fehlerhaft
			throw -1;
		}
		if(this->decls->decl->token == NULL){
			this->status = 0;
			cerr << "File empty!" << endl << "Stop"; exit(-1);
			throw 0;
		}
		this->statements = new Statements(scanner);
		if(this->statements->status == -1){
			throw -1;
		}
		else{
			this->status = 1;
		}

	}
	catch(int f)
	{
		this->status = f;
	}
}

Decls::Decls(Scanner* scanner) {
	try{

		this->decl = new Decl(scanner);	//Baue DECLS
		if(this->decl->status == -1){	//Wenn DECL fehlerhaft
			throw -1;
		}
		else if(this->decl->status >= 1){	//Wenn DECL vorhanden
			this->token = scanner->nextToken();
			if(this->token == NULL){
				cerr << "Unexpected End of File (EOF)" << endl << "Stop"; exit(-1);
				throw -1;
			}
			else if(this->token->type == ';'){	//Wenn ;
				this->status = 1;
				this->decls = new Decls(scanner);
			}
			else{	//Wenn kein ;
				cerr << "Unexpected token in line:" << this->token->line << " column: " << this->token->column << " " << this->token->type << endl << "Stop"; exit(-1);
				throw -1;
			}
		}
		else{	//Wenn DECL leer bzw. Programm nicht mit int anfängt
			this->status = 0;
		}
	}catch(int f){
		this->status = -1;
	}

}


Decl::Decl(Scanner* scanner) {
	try{
		this->token = scanner->nextToken();	//ggf. erstes Token, wenn NULL dann legitimes Dateiende
		if(this->token == NULL){
			throw 0;
		}
		else if (this->token->type == 8 && this->token->symTab->ttype == 7){ //Wenn Token/Schlüsselwort int
			this->array = new Array(scanner);
			if (this->array->status >= 1 || this->array->status == 0){ //Wenn ARRAY vorhanden oder leer
				//delete token;
				this->token = scanner->nextToken();
				if(this->token == NULL){
					cerr << "Unexpected End of File (EOF)" << endl << "Stop"; exit(-1);
					throw -1;
				}
				else if (this->token->type == 8 && this->token->symTab->ttype == 3 /*identifier*/){	//Wenn identifier in Tokentype und symtab
					this->status = 1;

					int count = 0;
					while(this->token->inhalt[count] != '\0'){
						this->inhalt[count] = this->token->inhalt[count];
						count++;
					}
					this->inhalt[count] = '\0';

					//this->inhalt = this->token->inhalt;
					this->varType = this->token->symTab->varType;
				}
				else{
					cerr << "Unexpected token in line:" << this->token->line << " column: " << this->token->column << " " << this->token->type << endl << "Stop"; exit(-1);
					throw -1;
				}
			}
			else if (this->array->status == -1){ //wenn ARRAY fehlerhaft
				throw -1;
			}
		}
		else{	//Wenn kein int gehe zurück und lasse später Statement prüfen
			this->status = 0;
			scanner->ungetToken(token);
		}
	}
	catch(int f){
		this->status = f;
	}
}

Array::Array(Scanner* scanner) {
	try{
		this->token = scanner->nextToken();
		if(this->token == NULL){
			cerr << "Unexpected End of File (EOF)" << endl << "Stop"; exit(-1);
			throw -1;
		}
		else if (this->token->type == '['){	//Eckige Klammer auf muss zuerst da sein
			this->token = scanner->nextToken();
			if(this->token == NULL){
				cerr << "Unexpected End of File (EOF)" << endl << "Stop"; exit(-1);
				throw -1;
			}
			else if (this->token->type == 9){  //Integer (Zahl) muss danach kommen -> type entspricht state_digit = 9
				int count = 0;
				while(this->token->inhalt[count] != '\0'){
					this->inhalt[count] = this->token->inhalt[count];
					count++;
				}
				this->inhalt[count] = '\0';
				this->varType = this->token->symTab->varType;
				this->token = scanner->nextToken();
				if(this->token == NULL){
					cerr << "Unexpected End of File (EOF)" << endl << "Stop"; exit(-1);
					throw -1;
				}
				else if (this->token->type == ']'){	//Eckige Klammer zu am Schluss
					this->status = 1;
				}
				else{
					cerr << "Unexpected token in line:" << this->token->line << " column: " << this->token->column << " " << this->token->type << endl << "Stop"; exit(-1);
					throw -1;
				}
			}
			else{
				cerr << "Unexpected token in line:" << this->token->line << " column: " << this->token->column << " " << this->token->type << endl << "Stop"; exit(-1);
				throw -1;
			}
		}
		else{
			//this->token = scanner->token;
			scanner->ungetToken(this->token);
			this->status = 0;//Ansonsten ist Array leer
		}
	}
	catch (int f){
		this->status = -1;
	}
}

Statements::Statements(Scanner* scanner) {
	try{
		this->statement = new Statement(scanner);	//Baue STATEMENT
		if(this->statement->status == -1){	//Wenn STATEMENT fehlerhaft
			throw -1;
		}
		else if(this->statement->status >= 1){	//Wenn STATEMENT vorhanden
			this->token = scanner->nextToken();
			if(this->token == NULL){
				cerr << "Unexpected End of File (EOF)" << endl << "Stop"; exit(-1);
				throw -1;
			}
			else if(this->token->type == ';'){	//Wenn ;
				this->status = 1;
				this->statements = new Statements(scanner);
			}
			else{	//Wenn kein ;
				cerr << "Unexpected token in line:" << this->token->line << " column: " << this->token->column << " " << this->token->type << endl << "Stop"; exit(-1);
				throw -1;
			}
		}
		else{	//Wenn STATEMENT leer bzw. Programm nicht mit token für STATEMENT anfängt
			this->status = 0;
		}
	}catch(int f){
		this->status = -1;
	}
}

Statement::Statement(Scanner* scanner) {
	try{
		this->token = scanner->nextToken();	//Wenn Token Null, dann legitimes Dateiende
		if(this->token == NULL){
			throw 0;
		}
		else if(this->token->type == 8 && token->symTab->ttype == 3 /*identifier*/){	//Wenn identifier
			int count = 0;//ident-Token zwischenspeichern
			while(this->token->inhalt[count] != '\0'){
				this->inhalt[count] = this->token->inhalt[count];
				count++;
			}
			this->inhalt[count] = '\0';
			this->varType = this->token->symTab->varType;
			this->index = new Index(scanner);
			if(this->index->status >= 0){	//Wenn INDEX da oder leer	//1, 2, 3, ... = Token vorhanden, 0 = Token nicht vorhanden, -1 = Token falsch
				this->token = scanner->nextToken();
				if(this->token == NULL){
					cerr << "Unexpected End of File (EOF)" << endl << "Stop"; exit(-1);
					throw -1;
				}
				else if(this->token->type == 13){ //Wenn :=
					this->exp = new Exp(scanner);
					if(this->exp->status >= 1){	//Wenn EXP vorhanden
						this->status = 1;
					}
					else{	//Wenn EXP nicht vorhanden (oder leer)
						throw -1;
					}
				}
				else{	//wenn Token nicht := ist
					cerr << "Unexpected token in line:" << this->token->line << " column: " << this->token->column << " " << this->token->type << endl << "Stop"; exit(-1);
					throw -1;
				}
			}
			else{	//Wenn INDEX fehlerhaft
				throw -1;
			}

		}
		else if(this->token->type == 8 && this->token->symTab->ttype == 4 /*write*/){	//Wenn write
			this->token = scanner->nextToken();
			if(this->token == NULL){
				cerr << "Unexpected End of File (EOF)" << endl << "Stop"; exit(-1);
				throw -1;
			}
			else if(this->token->type == '('){ //Wenn (
				this->exp = new Exp(scanner);
				if(this->exp->status >= 1){	//Wenn EXP vorhanden
					this->token = scanner->nextToken();
					if(this->token == NULL){
						cerr << "Unexpected End of File (EOF)" << endl << "Stop"; exit(-1);
						throw -1;
					}
					else if(this->token->type == ')'){	//Wenn )
						this->status = 2;
					}
					else{	//Wenn ) nicht vorhanden
						cerr << "Unexpected token in line:" << this->token->line << " column: " << this->token->column << " " << this->token->type << endl << "Stop"; exit(-1);
						throw -1;
					}
				}
				else{	//Wenn EXP nicht vorhanden oder fehlerhaft
					throw -1;
				}
			}
			else{	//Wenn ( nicht vorhanden
				cerr << "Unexpected token in line:" << this->token->line << " column: " << this->token->column << " " << this->token->type << endl << "Stop"; exit(-1);
				throw -1;
			}
		}
		else if(this->token->type == 8 && token->symTab->ttype == 5 /*read*/){	//Wenn identifier und der ist read vorhanden
			this->token = scanner->nextToken();
			if(this->token == NULL){
				cerr << "Unexpected End of File (EOF)" << endl << "Stop"; exit(-1);
				throw -1;
			}
			else if (this->token->type == '('){	//Wenn ( vorhanden
				this->token = scanner->nextToken();
				if (this->token->type == 8 && this->token->symTab->ttype == 3 /*identifier*/){	//Wenn identifier und identifier in symtab vorhanden
					int count = 0;
					while(this->token->inhalt[count] != '\0'){
						this->inhalt[count] = this->token->inhalt[count];
						count++;
					}
					this->inhalt[count] = '\0';
					this->varType = this->token->symTab->varType;
					this->index = new Index(scanner);
					if(this->index->status >= 0){	//Wenn INDEX vorhanden oder leer hole neues Token
						this->token = scanner->nextToken();
						if(this->token == NULL){
							cerr << "Unexpected End of File (EOF)" << endl << "Stop"; exit(-1);
							throw -1;
						}
						else if(this->token->type == ')'){	//Wenn ) vorhanden
							this->status = 3;
						}
						else{	//Wenn ) nicht vorhanden
							cerr << "Unexpected token in line:" << this->token->line << " column: " << this->token->column << " " << this->token->type << endl << "Stop"; exit(-1);
							throw -1;
						}
					}
					else{	//Wenn INDEX fehlerhaft
						throw -1;
					}

				}
				else{	//Wenn identifier nicht vorhanden
					cerr << "Unexpected token in line:" << this->token->line << " column: " << this->token->column << " " << this->token->type << endl << "Stop"; exit(-1);
					throw -1;
				}
			}
			else{	//Wenn ( nicht vorhanden
				cerr << "Unexpected token in line:" << this->token->line << " column: " << this->token->column << " " << this->token->type << endl << "Stop"; exit(-1);
				throw -1;
			}
		}
		else if(token->type == '{'){	//Wenn { vorhanden
			this->statements = new Statements(scanner);
			if(this->statements->status >= 0){	//Wenn STATEMENTS vorhanden oder leer
				this->token = scanner->nextToken();
				if(this->token == NULL){
					cerr << "Unexpected End of File (EOF)" << endl << "Stop"; exit(-1);
					throw -1;
				}
				else if(this->token->type == '}'){	//Wenn } vorhanden
					this->status = 4;
				}
				else{	//Wenn } nicht vorhanden
					cerr << "Unexpected token in line:" << this->token->line << " column: " << this->token->column << " " << this->token->type << endl << "Stop"; exit(-1);
					throw -1;
				}
			}
			else{	//Wenn STATEMENTS fehlerhaft
				throw -1;
			}
		}
		else if(this->token->type == 8 && token->symTab->ttype == 2 /*IF*/){	//Wenn if vorhanden
			this->token = scanner->nextToken();
			if(this->token == NULL){
				cerr << "Unexpected End of File (EOF)" << endl << "Stop"; exit(-1);
				throw -1;
			}
			else if(this->token->type == '('){	//Wenn ( vorhanden
				this->exp = new Exp(scanner);
				if(this->exp->status >= 1){	//Wenn EXP vorhanden
					this->token = scanner->nextToken();
					if(this->token == NULL){
						cerr << "Unexpected End of File (EOF)" << endl << "Stop"; exit(-1);
						throw -1;
					}
					else if(this->token->type == ')'){	//Wenn ) vorhanden
						this->statement = new Statement(scanner);
						if(this->statement->status >= 1){	//Wenn STATEMENT vorhanden
							this->token = scanner->nextToken();
							if(this->token == NULL){
								cerr << "Unexpected End of File (EOF)" << endl << "Stop"; exit(-1);
								throw -1;
							}
							else if(this->token->type == 8 && this->token->symTab->ttype == 6 /*else*/){ //Wenn Token = identifier und ist else vorhanden
								this->statement2 = new Statement(scanner);
								if(this->statement2->status >= 1){	//Wenn zweites STATEMENT
									this->status = 5;
								}
								else{	//Wenn zweites STATEMENT fehlerhaft oder leer
									throw -1;
								}
							}
							else{	//Wenn else nicht vorhanden
								cerr << "Unexpected token in line:" << this->token->line << " column: " << this->token->column << " " << this->token->type << endl << "Stop"; exit(-1);
								throw -1;
							}
						}
						else{	//Wenn STATEMENT fehlerhaft oder leer
							throw -1;
						}
					}
					else{	//Wenn ) nicht vorhanden
						cerr << "Unexpected token in line:" << this->token->line << " column: " << this->token->column << " " << this->token->type << endl << "Stop"; exit(-1);
						throw -1;
					}
				}
				else{	//Wenn EXP fehlerhaft oder leer
					throw -1;
				}
			}
			else{	//Wenn ( nicht vorhanden
				cerr << "Unexpected token in line:" << this->token->line << " column: " << this->token->column << " " << this->token->type << endl << "Stop"; exit(-1);
				throw -1;
			}
		}
		else if(this->token->type == 8 && token->symTab->ttype == 1 /*while*/){	//Wenn Token ist identifier und ist while vorhanden
			this->token = scanner->nextToken();
			if(this->token == NULL){
				cerr << "Unexpected End of File (EOF)" << endl << "Stop"; exit(-1);
				throw -1;
			}
			else if(this->token->type == '('){	//Wenn ( vorhanden
				this->exp = new Exp(scanner);
				if(this->exp->status >= 1){	//Wenn EXP vorhanden
					this->token = scanner->nextToken();
					if(this->token == NULL){
						cerr << "Unexpected End of File (EOF)" << endl << "Stop"; exit(-1);
						throw -1;
					}
					else if(this->token->type == ')'){	//Wenn ) vorhanden
						this->statement = new Statement(scanner);
						if(this->statement->status >= 1){	//Wenn STATEMENT vorhanden
							this->status = 6;
						}
						else{	//Wenn STATEMENT nicht vorhanden oder leer
							throw -1;
						}
					}
					else{	//Wenn ) nicht vorhanden
						cerr << "Unexpected token in line:" << this->token->line << " column: " << this->token->column << " " << this->token->type << endl << "Stop"; exit(-1);
						throw -1;
					}
				}
				else{	//Wenn EXP nicht vorhanden oder leer
					throw -1;
				}
			}
			else{	//Wenn ( nicht vorhanden
				cerr << "Unexpected token in line:" << this->token->line << " column: " << this->token->column << " " << this->token->type << endl << "Stop"; exit(-1);
				throw -1;
			}
		}
		else{	//Wenn nichts passendes für Statement vorhanden, prüfe auf braces close, ansonsten fehler!
			if (this->token->type == '}'){
				this->status = 0;
				scanner->ungetToken(this->token);
			}
			else{
				cerr << "Unexpected token in line:" << this->token->line << " column: " << this->token->column << " " << this->token->type << endl << "Stop"; exit(-1);
				throw -1;
			}
		}
	}
	catch(int f){
		this->status = f;
	}
}

Exp::Exp(Scanner* scanner) {
	try{
		this->exp2 = new Exp2(scanner);
		if(this->exp2->status >= 1){	//Wenn EXP2 vorhanden
			this->op_exp = new Op_exp(scanner);
			if(this->op_exp->status >= 0){	//Wenn OP_EXP vorhanden oder leer
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
		if(this->token == NULL){
			cerr << "Unexpected End of File (EOF)" << endl << "Stop"; exit(-1);
			throw -1;
		}
		else if(this->token->type == '('){	//Wenn ( vorhanden
			this->exp = new Exp(scanner);
			if(this->exp->status >= 1){	//Wenn EXP vorhanden
				this->token = scanner->nextToken();
				if(this->token == NULL){
					cerr << "Unexpected End of File (EOF)" << endl << "Stop"; exit(-1);
					throw -1;
				}
				else if(this->token->type == ')'){	//Wenn ) vorhanden
					this->status = 1;
				}
				else{	//Wenn ) nicht vorhanden
					cerr << "Unexpected token in line:" << this->token->line << " column: " << this->token->column << " " << this->token->type << endl << "Stop"; exit(-1);
					throw -1;
				}
			}
			else{	//Wenn EXP fehlerhaft oder leer
				throw -1;
			}
		}
		else if(this->token->type == 8 /*identifier*/){	//Wenn identifier

			int count = 0;
			while(this->token->inhalt[count] != '\0'){
				this->inhalt[count] = this->token->inhalt[count];
				count++;
			}
			this->inhalt[count] = '\0';
			this->varType = this->token->symTab->varType;
			this->index = new Index(scanner);
			if(this->index->status >= 0){	//Wenn INDEX leer oder vorhanden
				this->status = 2;
			}
			if(this->index->status == -1){	//Wenn INDEX fehlerhaft
				throw -1;
			}

		}
		else if(this->token->type == 9){  //Wenn Integer (Zahl) -> type entspricht state_digit = 9
			this->status = 3;
			int count = 0;
			while(this->token->inhalt[count] != '\0'){
				this->inhalt[count] = this->token->inhalt[count];
				count++;
			}
			this->inhalt[count] = '\0';
			this->varType = this->token->symTab->varType;
		}
		else if(this->token->type == '-' || this->token->type == '!'){	//Wenn - oder !
			this->exp2 = new Exp2(scanner);
			if(this->exp2->status >= 1){	//Wenn EXP2 vorhanden
				if(this->token->type == '-'){
					this->status = 4;
				}
				else{
					this->status = 5;
				}
			}
			else{	//Wenn EXP2 leer oder nicht vorhanden
				throw -1;
			}
		}
		else{	//Wenn kein passendes Beginnertoken für EXP2
			cerr << "Unexpected token in line:" << this->token->line << " column: " << this->token->column << " " << this->token->type << endl << "Stop"; exit(-1);
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
		if(this->token == NULL){
			cerr << "Unexpected End of File (EOF)" << endl << "Stop"; exit(-1);
			throw -1;
		}
		else if(this->token->type == '['){	//Wenn [ vorhanden
			this->exp = new Exp(scanner);
			if(this->exp->status == 1){	//Wenn EXP vorhanden
				this->token = scanner->nextToken();
				if(this->token == NULL){
					cerr << "Unexpected End of File (EOF)" << endl << "Stop"; exit(-1);
					throw -1;
				}
				else if(this->token->type == ']'){	//Wenn ] vorhanden
					this->status = 1;
				}
				else{	//Wenn ] nicht vorhanden
					cerr << "Unexpected token in line:" << this->token->line << " column: " << this->token->column << " " << this->token->type << endl << "Stop"; exit(-1);
					throw -1;
				}
			}
			else{	//Wenn EXP fehlerhaft (oder leer)
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
		if(this->op->status >= 1){	//Wenn OP vorhanden
			this->exp = new Exp(scanner);
			if(this->exp->status == 1){	//Wenn EXP vorhanden
				this->status = 1;
			}
			else{	//Wenn EXP fehlerhaft oder nicht vorhanden
				throw -1;
			}
		}
		else if(this->op->status == 0){	//Wenn OP leer, dann OP_EXP leer
			this->status = 0;
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
		if(this->token == NULL){
			cerr << "Unexpected End of File (EOF)" << endl << "Stop"; exit(-1);
			throw -1;
		}
		else if(Op::isOperand(this->token)){	//Wenn Operand vorhanden
			this->status = 1;
			int count = 0;
			while(this->token->inhalt[count] != '\0'){
				this->inhalt[count] = this->token->inhalt[count];
				count++;
			}
			this->inhalt[count] = '\0';
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
	if (t == '+' || t == '-' || t == Star ||  t == DoubleDot || t == '<' || t == '>' || t == Equal || t == DoubleDotEqual || t == EqualDoubleDotEqual || t == AndAnd){
		return true;
	}
	else{
		return false;
	}
}
