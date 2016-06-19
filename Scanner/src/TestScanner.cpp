#include "../includes/Scanner.h"
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include <cerrno>
#include <cstdio>

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
	array[1] = "Keyword while";
	array[2] = "Keyword if";
	array[3] = "Identifier";
	array[4] = "Keyword write";
	array[5] = "Keyword read";
	array[6] = "Keyword else";
	array[7] = "Keyword int";
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
		long int converted_long = strtol(t->inhalt,NULL,10);

		if(errno != ERANGE && t->column <5000){
			if(t->type==8){
				fs << "Token " << setw(20)<< left<< array[t->symTab->ttype] << " Line: " << setw(7)<<t->line<< " Column: " << setw(7)<< t->column;
			}else{
				fs << "Token " << setw(20)<< left<< array[t->type] << " Line: " << setw(7)<<t->line<< " Column: " << setw(7)<< t->column;
			}

			if(t->type == 8){ // Bei identifiernoch lexem anfügen
				fs << "Lexem: " << t->inhalt <<endl;
			}else if(t->type == 9){
				fs << "Value: " << converted_long <<endl;
			}else{
				fs<<endl;
			}
		}else if(errno == ERANGE){
			fprintf(stderr,"Bereichsüberschreitung: %s in Zeile: %d und Spalte: %d\n",t->inhalt,t->line,t->column);
			errno = 0;
		}else if(t->column >=5000){
			fprintf(stderr,"Zeile: %d ist zu lang um verarbeitet zu werden!!\n",t->line);
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


