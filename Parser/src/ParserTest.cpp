/*
 * ParserTest.cpp
 *
 *  Created on: Jun 15, 2016
 *      Author: kuar1013
 */
#include "../includes/Parser.h"
int main(int argc, char **argv) {
	Parser* parser = new Parser(argv[1]);
	parser->parse();
}