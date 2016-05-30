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
	symTab = new Symboltable();
}

Scanner::~Scanner() {
	delete automat;
	delete buffer;
	delete symTab;
}

Token* Scanner::nextToken(){
	int ident = 0; // 0 damit er zu erst einmal in die schleife geet
	while(ident == 0){ // ident<0 --> Token gefunden gehe ident zeichen zurück, iden = 0 noch ein Zeichen, ident=1 Token gefunden gehe kein Zeichen zurück
		char tmp = buffer->getChar();
		ident = automat->identifyToken(tmp);
		if(tmp == '\0'){
			if(ident == 1){//Token gwfunden und gleich danach Terminator Symbol -> Alles Ok gleich aufhören
				return automat->getToken();
			}
			if(ident == 0){//Noch ein Zeichen
					return NULL;
			}

			if(ident<0){
				for(int i = ident;i<-1;i++){ // geht nur hinein wenn ident <0 und der puffer auch somit zurück gehen muss
					buffer->ungetChar();
				}
				return automat->getToken();
			}
		}

		for(int i = ident;i<0;i++){ // geed nur herein wenn ident <0 und der puffer auch somit zurück gehen muss
			buffer->ungetChar();
		}
	}
	// TODO: Type des Tokens überprüfen und je nach type in die Symboltabelle eintragen


	// Token in Symboltabelle geben falls es ein Ident ist und noch nicht vorhanden ist siehe Tafelbild von letztem mal auf mikes handy
	Token* token = automat->getToken();
	if(token->type == 8){ // 8 Entspricht dem Zustand identifier im Automat
		if(token->inhalt != "while" || token->inhalt != "WHILE" || token->inhalt != "if" || token->inhalt != "IF"){
			symTab->insert(token->inhalt,token->type);
		}

	}

	//std::cout<<token->getColumn() << " " << token->getInhalt()<<std::endl;
	if(token->type == 12){
		comment = true;
	}else if(token->type == 14){
		comment = false;
		token = nextToken();
	}

	if(comment){
		nextToken();
	}else{
		return token;
	}

}
