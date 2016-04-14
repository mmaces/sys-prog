/*
 * Scanner.h
 *
 *  Created on: Sep 26, 2012
 *      Author: knad0001
 */

#ifndef SCANNER_H_
#define SCANNER_H_

#include "Token.h"
#include "../../Buffer/includes/Buffer.h"
#include "../../Automat/includes/Automat.h"

class Scanner {
public:
	Scanner(char* file);
	virtual ~Scanner();
	Automat* automat;
	Buffer* buffer;
	Token* nextToken();
};

#endif /* SCANNER_H_ */
