#include "../includes/Scanner.h"
#include <fstream>
#include <iomanip>
int main(int argc, char **argv) {

	enum state {
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
	} state;

	char* array[255];
	array[1] = "Keyword While";
	array[2] = "Keyword If";
	array[3] = "Identifier";
	array[8] = "Identifier";
	array[9] = "Digit";
	array[11] = "DoubleDot";
	array[12] = "DoubleDotStar";
	array[13] = "DoubleDotEqual";
	array[14] = "StarDoubleDot";
	array[15] = "Star";
	array[16] = "EqualDoubleDotEqual";
	array[17] = "Equal";
	array[19] = "AndAnd";
	array['+'] = "Plus";
	array['-'] = "Minus";
	array['<'] = "LessThan";
	array['>'] = "GreaterThan";
	array['!'] = "ExclamationMark";
	array[';'] = "Semicolon";
	array['('] = "ParanthesesOpen";
	array[')'] = "ParanthesesClose";
	array['{'] = "BraceOpen";
	array['}'] = "BraceClose";
	array['['] = "BracketOpen";
	array[']'] = "BracketClose";


	Scanner* scanner;

	scanner = new Scanner(argv[1]);

	fstream fs("out.txt", ios::out);
	Token* t = scanner->nextToken();
	while(t != NULL){
		while(!(t->type == 8 || t->type == 9|| t->type == 11|| t->type == 12|| t->type == 13|| t->type == 14|| t->type == 15
			|| t->type == 16|| t->type == 17|| t->type == 19|| t->type == '+'|| t->type == '-'|| t->type == '<'|| t->type == '>'
			|| t->type == '!'|| t->type == ';'|| t->type == '('|| t->type == ')'|| t->type == '['|| t->type == ']'|| t->type == '{'
			|| t->type == '}')){
			t = scanner->nextToken();
		}
		if(t->type==8){
			fs << "Token " << setw(20)<< left<< array[t->symTab->ttype] << " Line: " << setw(7)<<t->line<< " Column: " << setw(7)<< t->column;
		}else{
			fs << "Token " << setw(20)<< left<< array[t->type] << " Line: " << setw(7)<<t->line<< " Column: " << setw(7)<< t->column;
		}

		if(t->type == 8){ // Bei identifiernoch lexem anfügen
			fs << "Lexem: " << t->inhalt <<endl;
		}else if(t->type == 9){
			fs << "Value: " << t->inhalt <<endl;
		}else{
			fs<<endl;
		}
		t = scanner->nextToken();
	}

	if(t->type==8){
		fs << "Token " << setw(20)<< left<< array[t->symTab->ttype] << " Line: " << setw(7)<<t->line<< " Column: " << setw(7)<< t->column;
	}else{
		fs << "Token " << setw(20)<< left<< array[t->type] << " Line: " << setw(7)<<t->line<< " Column: " << setw(7)<< t->column;
	}

	if(t->type == 8){
		fs << "Lexem: " << t->inhalt <<endl;
	}else if(t->type == 9){
		fs << "Value: " << t->inhalt <<endl;
	}else{
		fs<<endl;
	}
	fs.close();
	delete scanner;
	}


