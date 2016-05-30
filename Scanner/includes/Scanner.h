/*
 * Scanner.h
 *
 *  Created on: Sep 26, 2012
 *      Author: knad0001
 */

#ifndef SCANNER_H_
#define SCANNER_H_

using namespace std;
#include "Token.h"
#include "../../Buffer/includes/Buffer.h"
#include "../../Automat/includes/Automat.h"
#include "../../Symboltable/includes/Symboltable.h"

class Scanner {
public:
	Scanner(char* file);
	virtual ~Scanner();
	Automat* automat;
	Buffer* buffer;
	Symboltable* symTab;
	Token* nextToken();
	bool comment = false;
};

#endif /* SCANNER_H_ */
