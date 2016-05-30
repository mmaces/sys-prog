/*
 * Buffer.h
 *
 *  Created on: Sep 26, 2012
 *      Author: knad0001
 */

#ifndef BUFFER_H_
#define BUFFER_H_
#include "String.h"
using namespace std;


class Buffer {
public:
	Buffer(const char * file);
	virtual ~Buffer();
	int filedescriptor;
	int index;
	bool rank;
	bool grenzeuebertreten;
	//bool end = false;
	int puffer_content1,puffer_content2;
	char* buffer1;
	char* buffer2;

	bool getRank();
	char getChar();
	void ungetChar();
};

#endif /* BUFFER_H_ */
