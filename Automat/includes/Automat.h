/*
 * Automat.h
 *
 *  Created on: Jul 5, 2012
 *      Author: knad0001
 */

#ifndef Automat_H_
#define Automat_H_

using namespace std;

#include "../../Scanner/includes/Token.h"

class Automat {
public:
	// Methoden
	Automat();
	virtual ~Automat();
	int identifyToken(char c);
	int matrixAdministrator(int i, char c);
	void trim(char* trimmed);
	Token* getToken();
	char check(char c);

	// Variablen
	Token* token;
	char flower[5000];
	int count;
	int currentState;
	char table[8][300];
	int line;
	int column;
	bool comment = false;
};

#endif /* Automat_H_ */
