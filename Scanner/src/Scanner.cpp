/*
 * Scanner.cpp
 *
 *  Created on: Sep 26, 2012
 *      Author: knad0001
 */

#include "../includes/Scanner.h"
//#include "../../Automat/includes/Automat.h"
//#include "../../Buffer/includes/Buffer.h"
//#include "../includes/Token.h"

Scanner::Scanner(char* file) {
	automat = new Automat();
	buffer = new Buffer(file);
}

Scanner::~Scanner() {
	delete[] automat;
	delete[] buffer;
}

Token* Scanner::nextToken(){
	int ident = 0; // 0 damit er zu erst einmal in die schleife geet
	while(ident == 0){ // ident<0 --> Token gefunden gehe ident zeichen zurück, iden = 0 noch ein Zeichen, ident=1 Token gefunden gehe keikn Zeichen zurück
		ident = automat->identifyToken(buffer->getChar());
		for(int i = ident;i<0;i++){ // geed nur herein wenn ident <0 und der puffer auch somit zurück gehen muss
			buffer->ungetChar();
		}
	}

	// TODO: Type des Tokens überprüfen und je nach type in die Symboltabelle eintragen


	// Token in Symboltabelle geben falls es ein Ident ist und noch nicht vorhanden ist siehe Tafelbild von letztem mal auf mikes handy
	Token* token = automat->getToken();
	return token;
}
