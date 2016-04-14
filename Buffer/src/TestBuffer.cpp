#include "../includes/Buffer.h"
#include <fstream>

int main(int argc, char **argv) {
	Buffer*  buffer;
	char c;
	buffer = new Buffer(argv[1]);

	fstream fs("quark.txt", ios::out);

	for(int i = 0; i < 512; i++){
		buffer->getChar();
	}
	//fs << buffer->getChar();
	fs << buffer->getChar();
	cout << buffer->getRank() << endl;
	buffer->ungetChar();
	buffer->ungetChar();
	cout << buffer->getRank() << endl;
	fs << (((c = buffer->getChar()) != '\0')? c : '\n');
	cout << buffer->getRank() << endl;
	while((c = buffer->getChar()) != '\0'){
			fs << c ;
		}


	fs.close();

	return 0;
}
