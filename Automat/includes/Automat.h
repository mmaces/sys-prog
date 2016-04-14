/*
 * Automat.h
 *
 *  Created on: Jul 5, 2012
 *      Author: knad0001
 */

#ifndef Automat_H_
#define Automat_H_

class Automat {
public:
	Automat();
	virtual ~Automat();
	int identifyToken(char c);
	int matrixAdministrator(int i, char c);
	Token* getToken();
	Token token;
	char* flower;
	int count;
	int currentState;
	int type;
	char table[8][200];
};

#endif /* Automat_H_ */
