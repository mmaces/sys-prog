#include "../includes/Scanner.h"
#include <fstream>
int main(int argc, char **argv) {
	cout <<"blabla"<< endl;

	Scanner* scanner;

	scanner = new Scanner(argv[1]);

	fstream fs("quark.txt", ios::out);
	Token* t = scanner->nextToken();
	while(t != NULL){
		std::cout << t->getLine() << " " << t->getColumn() << " ";
		std::cout << t->getInhalt()<< std::endl;
		fs  << t->getInhalt()<<'\n';
		t = scanner->nextToken();
	}
	std::cout << t->getLine() << " " << t->getColumn() << " ";
	std::cout << t->getInhalt()<< std::endl;
	fs  << t->getInhalt()<<'\n';
	fs.close();
	delete scanner;
}

