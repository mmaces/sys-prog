#include "../includes/Automat.h"
#include <iostream>


int main (int argc, char* argv[]){

	Automat* automat;

	automat = new Automat();
	std::cout  <<automat->identifyToken('1') << std::endl;
	std::cout  <<automat->identifyToken('2') << std::endl;
	std::cout  <<automat->identifyToken('0') << std::endl;
	std::cout  <<automat->identifyToken('0') << std::endl;
	std::cout  <<automat->identifyToken(' ') << std::endl;
	std::cout  <<automat->identifyToken('4') << std::endl;
	std::cout  <<automat->identifyToken('5') << std::endl;
	std::cout  <<automat->identifyToken('6') << std::endl;
	std::cout  <<automat->identifyToken('a') << std::endl;
	std::cout  <<automat->identifyToken(' ') << std::endl;

}
